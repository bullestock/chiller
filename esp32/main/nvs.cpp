#include "nvs.h"

#include "defs.h"

#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "nvs_flash.h"

static bool highest_index_is_water = false;
static int fan_pwm = 512;

void set_highest_index_is_water(bool value)
{
    nvs_handle my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_u8(my_handle, HIGHEST_INDEX_IS_WATER_KEY, value));
    highest_index_is_water = value;
    nvs_close(my_handle);
}

bool get_highest_index_is_water()
{
    return highest_index_is_water;
}

int get_fan_pwm()
{
    return fan_pwm;
}

void set_fan_pwm(int pwm)
{
    nvs_handle my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    ESP_ERROR_CHECK(nvs_set_u16(my_handle, FAN_PWM_KEY, pwm));
    fan_pwm = pwm;
    nvs_close(my_handle);
}    

void init_nvs()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    nvs_handle my_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &my_handle));
    uint8_t value = 0;
    if (nvs_get_u8(my_handle, HIGHEST_INDEX_IS_WATER_KEY, &value) == ESP_OK)
        highest_index_is_water = static_cast<bool>(value);
    nvs_close(my_handle);
}
