#include "hw.h"
#include "defs.h"
#include "util.h"

#include <limits>
#include <vector>

#include "esp_log.h"
#include <driver/pcnt.h>
#include "owb.h"
#include "owb_rmt.h"
#include "ds18b20.h"

const int NUM_DS18B20_DEVICES = 2;
const auto RESOLUTION = DS18B20_RESOLUTION_12_BIT;
//#define SAMPLE_PERIOD        (1000)   // milliseconds

#include <freertos/FreeRTOS.h>
#include <driver/ledc.h>

OneWireBus* owb = nullptr;
owb_rmt_driver_info rmt_driver_info;
int num_ds18b20_devices = 0;
DS18B20_Info* ds18b20_devices[NUM_DS18B20_DEVICES] = {0};

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
    
    detect_ds18b20();
}

void detect_ds18b20()
{
    owb = owb_rmt_initialize(&rmt_driver_info, PIN_TEMP,
                             RMT_CHANNEL_1, RMT_CHANNEL_0);
    owb_use_crc(owb, true);

    OneWireBus_ROMCode device_rom_codes[NUM_DS18B20_DEVICES];
    OneWireBus_SearchState search_state = {0};
    bool found = false;
    owb_search_first(owb, &search_state, &found);
    while (found)
    {
        char rom_code_s[17];
        owb_string_from_rom_code(search_state.rom_code,
                                 rom_code_s, sizeof(rom_code_s));
        printf("DS18B20 #%d : %s\n", num_ds18b20_devices, rom_code_s);
        device_rom_codes[num_ds18b20_devices] = search_state.rom_code;
        ++num_ds18b20_devices;
        if (num_ds18b20_devices > NUM_DS18B20_DEVICES)
            fatal_error("Too many DS18B20 devices");
        owb_search_next(owb, &search_state, &found);
    }
    printf("Found %d DS18B20 device%s\n", num_ds18b20_devices, num_ds18b20_devices == 1 ? "" : "s");
#if 0
    if (num_ds18b20_devices != NUM_DS18B20_DEVICES)
        fatal_error("DS18B20 device(s) missing");
#endif
    for (int i = 0; i < num_ds18b20_devices; ++i)
    {
        DS18B20_Info* ds18b20_info = ds18b20_malloc();
        ds18b20_devices[i] = ds18b20_info;

        ds18b20_init(ds18b20_info, owb, device_rom_codes[i]);
        ds18b20_use_crc(ds18b20_info, true);
        ds18b20_set_resolution(ds18b20_info, RESOLUTION);
    }
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
    ESP_ERROR_CHECK(gpio_set_level(PIN_FAN, on));
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

        for (int i = 0; i < num_ds18b20_devices; ++i)
            if (errors[i] != DS18B20_OK)
                readings[i] = std::numeric_limits<float>::quiet_NaN();
        // TODO
        values.water = readings[0];
        values.compressor = readings[1];
    }
    return values;
}
