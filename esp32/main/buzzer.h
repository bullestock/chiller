#pragma once

#include "util.h"

class Buzzer
{
public:
    Buzzer() = default;

    void start();

    void stop();

    void update();
    
private:
    bool active = false;
    bool on = false;
    util::time_point last_change = util::invalid_time_point();
};
