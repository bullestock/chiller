#pragma once

#include <driver/gpio.h>
#include <esp_adc/adc_oneshot.h>

constexpr const char* VERSION = "0.1";

// Pin definitions
constexpr const auto PIN_DISP_DC = (gpio_num_t) 2;
constexpr const auto PIN_DISP_RESET = (gpio_num_t) 4;
constexpr const auto PIN_DISP_CS = (gpio_num_t) 5;
constexpr const auto PIN_DISP_SCK = (gpio_num_t) 18;
constexpr const auto PIN_DISP_SDO = (gpio_num_t) 19;
constexpr const auto PIN_DISP_SDI = (gpio_num_t) 23;
constexpr const auto PIN_EXT_1 = (gpio_num_t) 27;
constexpr const auto PIN_EXT_2 = (gpio_num_t) 26;
constexpr const auto PIN_LEVEL = (gpio_num_t) 16;
constexpr const auto PIN_TEMP = (gpio_num_t) 15;
constexpr const auto PIN_RELAY_COMP = (gpio_num_t) 16;
constexpr const auto PIN_RELAY_RDY = (gpio_num_t) 21;
constexpr const auto PIN_FAN = (gpio_num_t) 26;
constexpr const auto PIN_FLOW = (gpio_num_t) 35;

constexpr const char* TAG = "CHLR";

// High/low temperature for thermostat (degrees)
constexpr const int LOW_TEMP = 20;
constexpr const int HIGH_TEMP = 25;

// Warn above this temperature
constexpr const int WATER_WARN_TEMP = 30;
constexpr const int COMPRESSOR_WARN_TEMP = 60;

// Halt operation above this temperature
constexpr const int WATER_HOT_TEMP = 35;
constexpr const int COMPRESSOR_HOT_TEMP = 70;

// High/low temperature for fan control
constexpr const int COMPRESSOR_FAN_LOW_TEMP = 28;
constexpr const int COMPRESSOR_FAN_HIGH_TEMP = 30;

// Halt operation if sensor reports less than this temperature
constexpr const int MIN_ACCEPTABLE_TEMP = 10;
// Halt operation if sensor reports more than this temperature
constexpr const int MAX_ACCEPTABLE_TEMP = 100;
// Sensor reports temperature in hundredths of degrees Celsius
constexpr const int TEMP_SCALE_FACTOR = 100;

// Minimum flow (l/h)
constexpr const int MIN_FLOW = 50;

// Number of temperature sensor readings to average
constexpr const int TEMP_AVERAGES = 5;

// Number of consecutive errors to trigger fault condition
constexpr const int CONSECUTIVE_ERRORS = 5;
