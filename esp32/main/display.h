#pragma once

#include <string>
#include <vector>

#include <TFT_eSPI.h>

using Thresholds = std::vector<std::pair<float, uint16_t>>;

class Display
{
public:
    Display(TFT_eSPI& tft);

    void show_legends();

    void set_status(const std::string& status, uint16_t colour = TFT_WHITE);

    void show_temperature(int quadrant, float temp,
                          const Thresholds& thresholds);

    void show_flow(int liters_per_hour);

private:
    void set_colour(float value,
                    const Thresholds& thresholds,
                    bool invert);

    void show_value(int quadrant, float value,
                    int nof_int_digits, int nof_dec_digits,
                    const Thresholds& thresholds, bool invert = false);

    static constexpr const int NOF_QUADRANTS = 4;

    TFT_eSPI& tft;
    int small_textheight = 0;
    int medium_textheight = 0;
    int large_textheight = 0;
    std::string last_status;
    std::string last_value[NOF_QUADRANTS];
};
