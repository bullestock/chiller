#include "hw.h"
#include "defs.h"
#include "display.h"
#include "nvs.h"
#include "util.h"

#include <limits>
#include <vector>

#include "esp_log.h"
#include <driver/adc.h>
#include <driver/pcnt.h>
#include "owb.h"
#include "owb_rmt.h"
#include "ds18b20.h"

const int NUM_DS18B20_DEVICES = 2;
const int MAX_ATTEMPTS = 5;
const auto RESOLUTION = DS18B20_RESOLUTION_12_BIT;

#include <freertos/FreeRTOS.h>
#include <driver/ledc.h>

static OneWireBus* owb = nullptr;
static owb_rmt_driver_info rmt_driver_info;
static int num_ds18b20_devices = 0;
static DS18B20_Info* ds18b20_devices[NUM_DS18B20_DEVICES] = {0};
static adc_oneshot_unit_handle_t adc1_handle;
static bool highest_index_is_water = true;

void init_hardware()
{
    // Inputs
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    // bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1ULL << PIN_DISP_SDI) |
       (1ULL << PIN_EXT_1) |
       (1ULL << PIN_EXT_2) |
       (1ULL << PIN_LEVEL) |
       (1ULL << PIN_TEMP) |
       (1ULL << PIN_FLOW);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    // Outputs
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1ULL << PIN_DISP_DC) |
       (1ULL << PIN_DISP_RESET) |
       (1ULL << PIN_DISP_CS) |
       (1ULL << PIN_DISP_SDO) |
       (1ULL << PIN_RELAY_COMP) |
       (1ULL << PIN_RELAY_RDY) |
       (1ULL << PIN_BUZZER) |
       (1ULL << PIN_FAN);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    set_compressor(false);
    set_ready(false);

    // Set up pulse counter for flow sensor
    
    pcnt_config_t pcnt_config;
    pcnt_config.pulse_gpio_num = PIN_FLOW;
    pcnt_config.ctrl_gpio_num = -1;
    pcnt_config.channel = PCNT_CHANNEL_0;
    pcnt_config.unit = PCNT_UNIT_0;
    pcnt_config.pos_mode = PCNT_COUNT_INC;
    pcnt_config.neg_mode = PCNT_COUNT_DIS;
    pcnt_config.lctrl_mode = PCNT_MODE_KEEP;
    pcnt_config.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config.counter_h_lim = 0;
    pcnt_config.counter_l_lim = 0;

    ESP_ERROR_CHECK(pcnt_unit_config(&pcnt_config));
    
    pcnt_counter_pause(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_set_filter_value(PCNT_UNIT_0, 100);
    pcnt_filter_enable(PCNT_UNIT_0);
    pcnt_counter_resume(PCNT_UNIT_0);

    // Set up ADC for current sensor
    
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 1, 0)
        .clk_src = static_cast<adc_oneshot_clk_src_t>(0),
#endif
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle,
                                               static_cast<adc_channel_t>(3), // SensVN
                                               &config));

    // Set up LEDC PWM for fan
    
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 20000,  // Set output frequency at 20 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .gpio_num       = PIN_FAN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0,
        .flags = {
            .output_invert  = 1,
        },
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    highest_index_is_water = get_highest_index_is_water();
}

void detect_ds18b20(Display& display)
{
    int attempt = 0;
    OneWireBus_ROMCode device_rom_codes[NUM_DS18B20_DEVICES];
    while (attempt < MAX_ATTEMPTS)
    {
        display.add_line("Detecting sensors");

        owb = owb_rmt_initialize(&rmt_driver_info, PIN_TEMP,
                             RMT_CHANNEL_1, RMT_CHANNEL_0);
        owb_use_crc(owb, true);

        num_ds18b20_devices = 0;
        OneWireBus_SearchState search_state = {0};
        bool found = false;
        owb_search_first(owb, &search_state, &found);
        while (found)
        {
            char rom_code_s[17];
            owb_string_from_rom_code(search_state.rom_code,
                                     rom_code_s, sizeof(rom_code_s));
            printf("DS18B20 #%d: %s\n", num_ds18b20_devices, rom_code_s);
            device_rom_codes[num_ds18b20_devices] = search_state.rom_code;
            ++num_ds18b20_devices;
            display.add_line("Found temp sensor");
            if (num_ds18b20_devices > NUM_DS18B20_DEVICES)
                fatal_error(display, "Too many\nDS18B20 devices");
            owb_search_next(owb, &search_state, &found);
        }
        printf("Found %d DS18B20 device%s\n", num_ds18b20_devices, num_ds18b20_devices == 1 ? "" : "s");
        if (num_ds18b20_devices == NUM_DS18B20_DEVICES)
            break;
        ++attempt;

        rmt_driver_info.bus.driver->uninitialize(owb);

        display.clear();
        const auto retry_msg = std::string("Retrying (") +
            std::string(1, '0' + attempt) +
            std::string("/") +
            std::string(1, '0' + MAX_ATTEMPTS) +
            std::string(")");
        display.add_line(retry_msg);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
#ifndef SIMULATE
    if (num_ds18b20_devices != NUM_DS18B20_DEVICES)
        fatal_error(display, "DS18B20 device(s)\nmissing");
#endif
    for (int i = 0; i < num_ds18b20_devices; ++i)
    {
        DS18B20_Info* ds18b20_info = ds18b20_malloc();
        ds18b20_devices[i] = ds18b20_info;

        ds18b20_init(ds18b20_info, owb, device_rom_codes[i]);
        ds18b20_use_crc(ds18b20_info, true);
        ds18b20_set_resolution(ds18b20_info, RESOLUTION);
    }
    display.add_line("HW init done");
}

void set_compressor(bool on)
{
    ESP_ERROR_CHECK(gpio_set_level(PIN_RELAY_COMP, on));
}

void set_ready(bool on)
{
    ESP_ERROR_CHECK(gpio_set_level(PIN_RELAY_RDY, on));
}

void set_buzzer(bool on)
{
    ESP_ERROR_CHECK(gpio_set_level(PIN_BUZZER, on));
}

void set_fan(bool on)
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, on ? get_fan_pwm() : 0));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
}

int get_and_reset_flow_pulses()
{
    int16_t temp_count;
    pcnt_get_counter_value(PCNT_UNIT_0, &temp_count);
    pcnt_counter_clear(PCNT_UNIT_0);
    return temp_count;
}

Temperatures read_temperatures()
{
    Temperatures values;
#ifdef SIMULATE
    values.water = 18.2;
    values.compressor = 42.7;
    return values;
#endif
    if (num_ds18b20_devices > 0)
    {
        ds18b20_convert_all(owb);

        // All devices use the same resolution,
        // so use the first device to determine the delay
        ds18b20_wait_for_conversion(ds18b20_devices[0]);

        float readings[NUM_DS18B20_DEVICES];
        DS18B20_ERROR errors[NUM_DS18B20_DEVICES];

        for (int i = 0; i < num_ds18b20_devices; ++i)
            errors[i] = ds18b20_read_temp(ds18b20_devices[i], &readings[i]);

        uint8_t highest_serial_number[6];
        int highest_serial_number_index = 0;
        memset(highest_serial_number, 0, sizeof(highest_serial_number));
        for (int i = 0; i < num_ds18b20_devices; ++i)
        {
            if (memcmp(ds18b20_devices[i]->rom_code.fields.serial_number,
                       highest_serial_number, sizeof(highest_serial_number)) > 0)
            {
                memcpy(highest_serial_number,
                       ds18b20_devices[i]->rom_code.fields.serial_number,
                       sizeof(highest_serial_number));
                highest_serial_number_index = i;
            }
            if (errors[i] != DS18B20_OK)
                readings[i] = std::numeric_limits<float>::quiet_NaN();
        }
        int water_index = highest_serial_number_index;
        int compressor_index = NUM_DS18B20_DEVICES - 1 - highest_serial_number_index;
        if (!highest_index_is_water)
            std::swap(water_index, compressor_index);
        values.water = readings[water_index];
        values.compressor = readings[compressor_index];
    }
    return values;
}

bool read_level()
{
    return !gpio_get_level(PIN_LEVEL);
}

bool read_current(int &current)
{
    return adc_oneshot_read(adc1_handle,
                            static_cast<adc_channel_t>(3), // SensVN
                            &current) == ESP_OK;
}

// Local Variables:
// compile-command: "cd .. && idf.py build"
// End:
