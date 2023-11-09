#include <stdio.h>
#include <string>
#include <vector>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "buzzer.h"
#include "console.h"
#include "defs.h"
#include "display.h"
#include "hw.h"
#include "nvs.h"
#include "util.h"

#include <TFT_eSPI.h>

static float temp_readings[2][TEMP_AVERAGES];

float add_temp_reading(int index, float temp)
{
#ifdef SIMULATE
    return temp;
#else
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
#endif
}


extern "C"
void app_main()
{
    printf("Chiller v %s\n", VERSION);

    init_hardware();

    TFT_eSPI tft;
    Display display(tft);

    display.add_line("Initializing NVS");
    init_nvs();

    display.add_line("Wait for console");
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
        run_console(display);        // never returns

    printf("\nStarting application\n");
    
    detect_ds18b20(display);
    display.show_legends();

    unsigned int liters_per_hour = 0;
    bool compressor_on = false;
    bool signal_ok = false;
    int nof_consecutive_errors = 0;
    int nof_consecutive_clears = 0;
    bool first = true;
    bool initializing = true;
    unsigned long last_flow_time = 0;
    Thresholds water_thresholds;
    water_thresholds.push_back(std::make_pair(WATER_WARN_TEMP, TFT_YELLOW));
    water_thresholds.push_back(std::make_pair(WATER_HOT_TEMP, TFT_RED));
    Thresholds compressor_thresholds;
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_WARN_TEMP, TFT_YELLOW));
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_HOT_TEMP, TFT_RED));

    Buzzer buzzer;
    
    while (1)
    {
        //
        //-- Read and display temperatures
        //

        const auto temps = read_temperatures();
        if (std::isnan(temps.water))
            fatal_error(display, "Water\ntemperature\nsensor\nmalfunction");
        if (std::isnan(temps.compressor))
            fatal_error(display, "Compressor\ntemperature\nsensor\nmalfunction");

        auto temp = add_temp_reading(0, temps.water);
        display.show_temperature(0, temp, water_thresholds);
        temp = add_temp_reading(1, temps.compressor);
        display.show_temperature(1, temp, compressor_thresholds);
    
        //
        //-- Display flow (once every second)
        //
        
#ifdef SIMULATE
        liters_per_hour = 123;
#else
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
#endif
        
        display.show_flow(liters_per_hour);

        //
        //-- Do checks
        //

        const auto low_flow = (liters_per_hour < MIN_FLOW);

        if (temps.water < LOW_TEMP)
        {
            // Cool enough
            compressor_on = false;
        }
        else if (temps.water > HIGH_TEMP)
        {
            // Too warm
            compressor_on = true;
        }
        set_compressor(compressor_on);
        bool fan_on = false;
        if (compressor_on)
            fan_on = true;
        // Keep fan on while compressor is hot
        else if (temps.compressor > COMPRESSOR_FAN_HIGH_TEMP)
            fan_on = true;
        else if (temps.compressor < COMPRESSOR_FAN_LOW_TEMP)
            fan_on = false;
        set_fan(fan_on);
        const auto is_hot = (temps.water > WATER_HOT_TEMP) ||
            (temps.compressor > COMPRESSOR_HOT_TEMP);

        const bool level_ok = read_level();

        const bool current_clear_state = !is_hot && !low_flow && level_ok;
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
            state = "Flow\ntoo low";
            state_colour = TFT_RED;
        }
        if (is_hot)
        {
            state = "Too hot";
            state_colour = TFT_RED;
        }
        if (!level_ok)
        {
            state = "Refill\nneeded";
            state_colour = TFT_RED;
        }
        // Do not signal 'OK' before we have the required number of OK samples, but do not beep on startup
        if (!signal_ok && !initializing)
            buzzer.start();
        else
            buzzer.stop();

        display.set_status(state, state_colour);
        buzzer.update();
        vTaskDelay(10);
    }
}

// Local Variables:
// compile-command: "cd .. && idf.py build"
// End:
