#pragma once

void init_hardware();
void detect_ds18b20(class Display& display);

void set_compressor(bool on);
void set_ready(bool on);
void set_buzzer(bool on);
void set_fan(bool on);

int get_and_reset_flow_pulses();

struct Temperatures
{
    float water;
    float compressor;
};

Temperatures read_temperatures();

bool read_current(int &current);

/// true if level OK
bool read_level();
