#include <stdio.h>
#include <string>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "console.h"
#include "defs.h"
#include "hw.h"

#include <TFT_eSPI.h>

void fatal_error(const std::string& error)
{
    //!!
    printf("FATAL: %s\n", error.c_str());
    vTaskDelay(1000/portTICK_PERIOD_MS);
    esp_restart();
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

    while (1)
    {
        //
        //-- Read and display temperatures
        //

        const auto temps = read_temperatures();
        if (std::isnan(temps.water))
            fatal_error("Water temperature sensor malfunction");
        if (std::isnan(temps.compressor))
            fatal_error("Water temperature sensor malfunction");

        auto temp = add_temp_reading(0, temps.water);
        // display
        temp = add_temp_reading(1, temps.compressor);
        // display
    
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

        char buf[20];
        sprintf(buf, "%3d", liters_per_hour);
        //lcd.print(buf);

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

        const bool currentClearState = !is_hot && !low_flow;
        if (currentClearState)
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
        if (fan_on)
            state = "Fan on";
        if (compressor_on)
            state = "Cooling";
        if (low_flow)
            state = "Flow too low";
        if (is_hot)
        {
            if (low_flow)
                state = "Too hot, low flow";
            else
                state = "Too hot";
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
        }
        else if (temps.compressor >= COMPRESSOR_WARN_TEMP*TEMP_SCALE_FACTOR)
        {
            printf("Error: compressor hot\n");
            set_buzzer(beep_state);
            beep_state = !beep_state;
            state = "Water hot!";
        }
        else
            set_buzzer(0);

        while (state.length() < 20)
            state += " ";
        //lcd.print(state);
        vTaskDelay(10);
    }
}
