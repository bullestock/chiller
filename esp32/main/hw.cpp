#include "hw.h"
#include "defs.h"

#include <freertos/FreeRTOS.h>
#include <driver/ledc.h>

static adc_oneshot_unit_handle_t adc1_handle;

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
       (1ULL << PIN_TEMP);
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
       (1ULL << PIN_RELAY_RDY);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    ESP_ERROR_CHECK(gpio_config(&io_conf));

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
                                               CHAN_CUR_SENSE,
                                               &config));
    
    compressor_on(false);
    ready_on(false);
}

void compressor_on(bool on)
{
    ESP_ERROR_CHECK(gpio_set_level(PIN_RELAY_COMP, on));
}

void ready_on(bool on)
{
    ESP_ERROR_CHECK(gpio_set_level(PIN_RELAY_RDY, on));
}
