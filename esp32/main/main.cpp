#include <stdio.h>
#include <string>
#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "console.h"
#include "defs.h"
#include "hw.h"

#include <TFT_eSPI.h>

using Thresholds = std::vector<std::pair<float, uint16_t>>;

void set_status(TFT_eSPI& tft, const std::string& status, uint16_t colour = TFT_WHITE)
{
    tft.fillRect(TFT_WIDTH/2, TFT_HEIGHT/2, TFT_WIDTH/2, TFT_HEIGHT/2, TFT_BLACK);
    tft.setTextColor(colour);
    tft.drawString(status.c_str(),
                   TFT_WIDTH/2 + 5, TFT_HEIGHT/2 + 5,
                   2);
}

void fatal_error(TFT_eSPI& tft, const std::string& error)
{
    printf("FATAL: %s\n", error.c_str());
    const auto msg = "ERROR:\n" + error;
    set_status(tft, msg, TFT_RED);
    set_ready(false);
    
    while (1)
    {
        set_buzzer(1);
        vTaskDelay(40/portTICK_PERIOD_MS);
        set_buzzer(0);
        vTaskDelay(80/portTICK_PERIOD_MS);
        set_buzzer(1);
        vTaskDelay(160/portTICK_PERIOD_MS);
        set_buzzer(0);
        vTaskDelay(320/portTICK_PERIOD_MS);
    }
}

void set_colour(TFT_eSPI& tft, float value,
                const Thresholds& thresholds,
                bool invert)
{
    uint16_t colour = TFT_WHITE;
    if (invert)
        for (auto it = thresholds.rbegin(); it != thresholds.rend(); ++it)
        {
            if (value <= it->first)
                colour = it->second;
        }
    else
        for (const auto& t : thresholds)
        {
            if (value >= t.first)
                colour = t.second;
        }
    tft.setTextColor(colour);
}

// +---+---+
// | 0 | 1 |
// +---+---+
// | 2 | 3 |
// +---+---+
void show_value(TFT_eSPI& tft, int quadrant, float value, int nof_decimals,
                const Thresholds& thresholds, bool invert = false)
{
    char buf[20];
    const int int_val = static_cast<int>(value);
    sprintf(buf, "%3d", int_val);
    set_colour(tft, value, thresholds, invert);
    const int x = (quadrant & 1 ? 480/2 : 0) + 480/4 - 100;
    const int y = (quadrant > 1 ? 320/2 : 0) + 320/4;
    tft.drawString(buf, x, y, 5);
    if (nof_decimals)
    {
        const int decimal_digits = std::round((value - int_val)*std::pow(10, nof_decimals));
        sprintf(buf, "%0*d", nof_decimals, decimal_digits);
        tft.drawString(buf, x + 50, y, 4);
    }
}

void show_temperature(TFT_eSPI& tft, int quadrant, float temp,
                      const Thresholds& thresholds)
{
    show_value(tft, quadrant, temp, 1, thresholds);
}

void show_flow(TFT_eSPI& tft, int liters_per_hour)
{
    static Thresholds thresholds;
    if (thresholds.empty())
    {
        thresholds.push_back(std::make_pair(MIN_FLOW, TFT_RED));
    }
    show_value(tft, 3, liters_per_hour, 0, thresholds, true);
}

static int temp_readings[2][TEMP_AVERAGES];

int add_temp_reading(int index, int temp)
{
    int sum = 0;
    for (int i = 1; i < TEMP_AVERAGES; ++i)
    {
        const auto t = temp_readings[index][i];
        sum += t;
        temp_readings[index][i-1] = t;
    }
    temp_readings[index][TEMP_AVERAGES-1] = temp;
    sum += temp;
    return sum/TEMP_AVERAGES;
}


extern "C"
void app_main()
{
    init_hardware();

    printf("Chiller v %s\n", VERSION);

    printf("\n\nPress a key to enter console\n");
    bool debug = false;
    for (int i = 0; i < 20; ++i)
    {
        if (getchar() != EOF)
        {
            debug = true;
            break;
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    if (debug)
        run_console();        // never returns

    TFT_eSPI tft;
    tft.init();
    tft.fillScreen(0xF81F);
    
    printf("\nStarting application\n");

    unsigned int liters_per_hour = 0;
    bool compressor_on = false;
    bool signal_ok = false;
    int nof_consecutive_errors = 0;
    int nof_consecutive_clears = 0;
    bool beep_state = false;
    bool first = true;
    bool initializing = true;
    unsigned long last_flow_time = 0;
    Thresholds water_thresholds;
    water_thresholds.push_back(std::make_pair(WATER_WARN_TEMP, TFT_YELLOW));
    water_thresholds.push_back(std::make_pair(WATER_HOT_TEMP, TFT_RED));
    Thresholds compressor_thresholds;
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_WARN_TEMP, TFT_YELLOW));
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_HOT_TEMP, TFT_RED));

    while (1)
    {
        //
        //-- Read and display temperatures
        //

        const auto temps = read_temperatures();
        if (std::isnan(temps.water))
            fatal_error(tft, "Water temperature sensor malfunction");
        if (std::isnan(temps.compressor))
            fatal_error(tft, "Water temperature sensor malfunction");

        auto temp = add_temp_reading(0, temps.water);
        show_temperature(tft, 0, temp, water_thresholds);
        temp = add_temp_reading(1, temps.compressor);
        show_temperature(tft, 1, temp, compressor_thresholds);
    
        //
        //-- Display flow (once every second)
        //
        
        const unsigned long currentTime = millis();
        if (first || (currentTime >= (last_flow_time + 1000)))
        {
            const unsigned long deltaTime = currentTime - last_flow_time;
            last_flow_time = currentTime;
            // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
            const auto flow_pulses = get_and_reset_flow_pulses();
            liters_per_hour = (flow_pulses*60000.0/deltaTime / 7.5);
            printf("Flow: %d\n", liters_per_hour);
            first = false;
        }

        show_flow(tft, liters_per_hour);

        //
        //-- Do checks
        //

        const auto low_flow = (liters_per_hour < MIN_FLOW);

        if (temps.water < LOW_TEMP*TEMP_SCALE_FACTOR)
        {
            // Cool enough
            compressor_on = false;
        }
        else if (temps.water > HIGH_TEMP*TEMP_SCALE_FACTOR)
        {
            // Too warm
            compressor_on = true;
        }
        set_compressor(compressor_on);
        bool fan_on = false;
        if (compressor_on)
            fan_on = true;
        // Keep fan on while compressor is hot
        else if (temps.compressor > COMPRESSOR_FAN_HIGH_TEMP*TEMP_SCALE_FACTOR)
            fan_on = true;
        else if (temps.compressor < COMPRESSOR_FAN_LOW_TEMP*TEMP_SCALE_FACTOR)
            fan_on = false;
        set_fan(fan_on);
        const auto is_hot = (temps.water > WATER_HOT_TEMP*TEMP_SCALE_FACTOR) ||
            (temps.compressor > COMPRESSOR_HOT_TEMP*TEMP_SCALE_FACTOR);

        const bool current_clear_state = !is_hot && !low_flow;
        if (current_clear_state)
        {
            // We are currently OK
            ++nof_consecutive_clears;
            if (nof_consecutive_clears >= CONSECUTIVE_ERRORS)
            {
                // Clear error status
                nof_consecutive_errors = 0;
                nof_consecutive_clears = 0;
                signal_ok = true;
                initializing = false;
                printf("Initialization done\n");
            }
        }
        else
        {
            // We are currently in error state
            ++nof_consecutive_errors;
            if (nof_consecutive_errors >= CONSECUTIVE_ERRORS)
            {
                // Set error status
                nof_consecutive_clears = 0;
                signal_ok = false;
            }
        }

        // Low flow is very bad
        if (low_flow)
            signal_ok = false;

        // TODO: Level sensor

        // Signal status to Lasersaur
        set_ready(signal_ok);

        std::string state = "Idle";
        uint16_t state_colour = TFT_WHITE;
        if (fan_on)
            state = "Fan on";
        if (compressor_on)
        {
            state = "Cooling";
            state_colour = TFT_BLUE;
        }
        if (low_flow)
        {
            state = "Flow too low";
            state_colour = TFT_RED;
        }
        if (is_hot)
        {
            if (low_flow)
                state = "Too hot,\nlow flow";
            else
                state = "Too hot";
            state_colour = TFT_RED;
        }
        printf("signal_ok %d initializing %d\n", signal_ok, initializing);
        // Do not signal 'OK' before we have the required number of OK samples, but do not beep on startup
        if (!signal_ok && !initializing)
        {
            set_buzzer(1);
        }
        else if (temps.water >= WATER_WARN_TEMP*TEMP_SCALE_FACTOR)
        {
            printf("Error: water hot\n");
            set_buzzer(beep_state);
            beep_state = !beep_state;
            state = "Water hot!";
            state_colour = TFT_RED;
        }
        else if (temps.compressor >= COMPRESSOR_WARN_TEMP*TEMP_SCALE_FACTOR)
        {
            printf("Error: compressor hot\n");
            set_buzzer(beep_state);
            beep_state = !beep_state;
            state = "Compressor hot!";
            state_colour = TFT_RED;
        }
        else
            set_buzzer(0);

        set_status(tft, state, state_colour);
        vTaskDelay(10);
    }
}
