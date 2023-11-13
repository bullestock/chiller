#pragma once

#include "defs.h"

void init_nvs();

bool get_highest_index_is_water();

void set_highest_index_is_water(bool value);

int get_fan_pwm();

void set_fan_pwm(int pwm);
