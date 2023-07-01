#pragma once

void init_hardware();
void detect_ds18b20();

void compressor_on(bool on);
void ready_on(bool on);

struct Temperatures
{
    float water;
    float compressor;
};

Temperatures read_temperatures();
