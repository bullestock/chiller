#include "display.h"

#include "defs.h"

static constexpr const auto small_font = &FreeSans12pt7b;
static constexpr const auto medium_font = &FreeSansBold18pt7b;
static constexpr const auto large_font = &FreeSansBold24pt7b;
static constexpr const int GFXFF = 1;

Display::Display(TFT_eSPI& tft)
    : tft(tft)
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    tft.setFreeFont(small_font);
    small_textheight = tft.fontHeight(GFXFF) + 1;
    tft.setFreeFont(medium_font);
    medium_textheight = tft.fontHeight(GFXFF) + 1;
    tft.setFreeFont(large_font);
    large_textheight = tft.fontHeight(GFXFF) + 1;
    
    tft.setFreeFont(large_font);
    tft.setTextColor(TFT_WHITE);
    std::string text = "Chiller";
    auto w = tft.textWidth(text.c_str(), GFXFF);
    auto x = TFT_HEIGHT/2 - w/2;
    tft.drawString(text.c_str(), x, large_textheight*1, GFXFF);
    text = std::string("V ") + std::string(VERSION);
    w = tft.textWidth(text.c_str(), GFXFF);
    x = TFT_HEIGHT/2 - w/2;
    tft.drawString(text.c_str(), x, large_textheight*3, GFXFF);
}

void Display::show_legends()
{
    tft.fillScreen(TFT_BLACK);
    tft.setFreeFont(small_font);
    tft.setTextColor(TFT_CYAN);
    tft.drawString("Water", 85, 0, GFXFF);
    tft.drawString("Compressor", 295, 0, GFXFF);
    tft.drawString("Flow", 90, TFT_WIDTH/2, GFXFF);
}

void Display::set_status(const std::string& status, uint16_t colour)
{
    if (status != last_status)
    {
        tft.fillRect(TFT_HEIGHT/2, TFT_WIDTH/2, TFT_HEIGHT/2, TFT_WIDTH/2, TFT_BLACK);
        last_status = status;
    }
    tft.setTextColor(colour);
    tft.setFreeFont(large_font);
    const auto w = tft.textWidth(status.c_str(), GFXFF);
    const auto x = TFT_HEIGHT/2 + TFT_HEIGHT/4 - w/2;
    const auto y = TFT_HEIGHT/2 - 20;
    tft.drawString(status.c_str(), x, y, GFXFF);
}

void Display::set_colour(float value,
                         const Thresholds& thresholds,
                         bool invert)
{
    uint16_t colour = TFT_WHITE;
    if (invert)
        for (auto it = thresholds.rbegin(); it != thresholds.rend(); ++it)
        {
            if (value <= it->first)
                colour = it->second;
        }
    else
        for (const auto& t : thresholds)
        {
            if (value >= t.first)
                colour = t.second;
        }
    tft.setTextColor(colour);
}

// +---+---+
// | 0 | 1 |
// +---+---+
// | 2 | 3 |
// +---+---+
void Display::show_value(int quadrant, float value,
                         int nof_int_digits, int nof_dec_digits,
                         const Thresholds& thresholds, bool invert)
{
    char buf[20];
    const int int_val = static_cast<int>(value);
    sprintf(buf, "%*d", nof_int_digits, int_val);
    const std::string svalue(buf);
    if (svalue != last_value[quadrant])
    {
        const int x = quadrant & 1 ? TFT_HEIGHT/2 : 0;
        const int y = quadrant > 1 ? TFT_WIDTH/2 : 0;
        tft.fillRect(x, y, TFT_HEIGHT/2, TFT_WIDTH/2, TFT_BLACK);
        last_value[quadrant] = svalue;
    }
    set_colour(value, thresholds, invert);
    // TODO: Use text width
    const int x = (quadrant & 1 ? TFT_HEIGHT/2 : 0) + TFT_HEIGHT/4 - 100;
    const int y = (quadrant > 1 ? TFT_WIDTH/2 : 0) + TFT_WIDTH/8;
    tft.drawString(buf, x, y, 8);
    if (nof_dec_digits)
    {
        const int decimal_digits = std::round((value - int_val)*std::pow(10, nof_dec_digits));
        sprintf(buf, ".%0*d", nof_dec_digits, decimal_digits);
        tft.drawString(buf, x + 102, y + 38, 6);
    }
}

void Display::show_temperature(int quadrant, float temp,
                               const Thresholds& thresholds)
{
    show_value(quadrant, temp, 2, 1, thresholds);
}

void Display::show_flow(int liters_per_hour)
{
    static Thresholds thresholds;
    if (thresholds.empty())
    {
        thresholds.push_back(std::make_pair(MIN_FLOW, TFT_RED));
    }
    show_value(2, liters_per_hour, 3, 0, thresholds, true);
}

// Local Variables:
// compile-command: "cd .. && idf.py build"
// End:
