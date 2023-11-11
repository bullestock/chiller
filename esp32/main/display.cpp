#include "display.h"

#include "defs.h"

static constexpr const auto small_font = &FreeSans12pt7b;
static constexpr const auto medium_font = &FreeSansBold18pt7b;
static constexpr const auto large_font = &FreeSansBold24pt7b;
static constexpr const int GFXFF = 1;
static constexpr const int LEGEND_HEIGHT = 22;

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
    
    tft.setFreeFont(medium_font);
    tft.setTextColor(TFT_GREEN);
    const std::string text = std::string("Chiller V ") + std::string(VERSION);
    add_line(text);
}

void Display::clear()
{
    tft.fillScreen(TFT_BLACK);
    cur_line = 0;
}

void Display::add_line(const std::string& text)
{
    auto w = tft.textWidth(text.c_str(), GFXFF);
    const auto x = TFT_HEIGHT/2 - w/2;
    tft.drawString(text.c_str(), x, cur_line*medium_textheight, GFXFF);
    ++cur_line;
}

/// Get upper left corner pixel coordinates of a quadrant
static std::pair<int, int> get_quadrant_ul(int quadrant)
{
    return std::make_pair(quadrant & 1 ? TFT_HEIGHT/2 : 0,
                          quadrant > 1 ? TFT_WIDTH/2 : 0);
}

void Display::show_legends()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_CYAN);
    show_legend(0, "Water");
    show_legend(1, "Compressor");
    show_legend(2, "Flow");
}

void Display::show_legend(int quadrant, const std::string& legend)
{
    tft.setFreeFont(small_font);
    const auto ul = get_quadrant_ul(quadrant);
    const auto w = tft.textWidth(legend.c_str(), GFXFF);
    const int x = ul.first + (TFT_HEIGHT/2 - w)/2;
    const int y = ul.second;
    tft.drawString(legend.c_str(), x, y, GFXFF);
}

static std::vector<std::string> split(const std::string& s)
{
    std::vector<std::string> v;
    std::string::size_type curpos = 0;
    while (curpos < s.size())
    {
        const auto end = s.find('\n', curpos);
        if (end == std::string::npos)
        {
            // Last line
            v.push_back(s.substr(curpos));
            return v;
        }
        const auto line = s.substr(curpos, end - curpos);
        v.push_back(line);
        curpos = end + 1;
    }
    return v;
}

void Display::set_status(const std::string& status, uint16_t colour)
{
    if (status == last_status)
        return;
    last_status = status;

    const auto lines = split(status);
    tft.setTextColor(colour);
    tft.setFreeFont(medium_font);
    tft.fillRect(TFT_HEIGHT/2, TFT_WIDTH/2, TFT_HEIGHT/2, TFT_WIDTH/2, TFT_BLACK);
    auto y = TFT_WIDTH/2 + TFT_WIDTH/4 - lines.size()/2*medium_textheight;
    for (const auto& line : lines)
    {
        const auto w = tft.textWidth(line.c_str(), GFXFF);
        const auto x = TFT_HEIGHT/2 + TFT_HEIGHT/4 - w/2;
        tft.drawString(line.c_str(), x, y, GFXFF);
        y += medium_textheight;
    }
}

void Display::show_fatal_error(const std::string& error)
{
    const auto lines = split(error);
    tft.setTextColor(TFT_RED);
    tft.setFreeFont(large_font);
    tft.fillScreen(TFT_BLACK);

    auto y = TFT_WIDTH/2 - lines.size()/2*large_textheight;
    for (const auto& line : lines)
    {
        const auto w = tft.textWidth(line.c_str(), GFXFF);
        const auto x = TFT_HEIGHT/2 - w/2;
        tft.drawString(line.c_str(), x, y, GFXFF);
        y += large_textheight;
    }
}

void Display::set_colour(float value,
                         const Thresholds& thresholds,
                         bool invert)
{
#ifdef DEBUG
    printf("set_colour: %f\n", value);
#endif
    uint16_t colour = TFT_WHITE;
    if (invert)
        for (auto it = thresholds.rbegin(); it != thresholds.rend(); ++it)
        {
            printf("invert: th %f\n", it->first);
            if (value <= it->first)
            {
                colour = it->second;
                printf("using %d\n", colour);
            }
        }
    else
        for (const auto& t : thresholds)
        {
#ifdef DEBUG
            printf("th %f\n", t.first);
#endif
            if (value >= t.first)
            {
                colour = t.second;
#ifdef DEBUG
                printf("using %d\n", colour);
#endif
            }
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
    const auto ul = get_quadrant_ul(quadrant);
    char int_buf[20];
    const int int_val = static_cast<int>(value);
    sprintf(int_buf, "%*d", nof_int_digits, int_val);
    int w = tft.textWidth(int_buf, 8);
    const int int_w = w;
    char dec_buf[20];
    dec_buf[0] = 0;
    if (nof_dec_digits)
    {
        const int decimal_digits = std::round((value - int_val)*std::pow(10, nof_dec_digits));
        sprintf(dec_buf, ".%0*d", nof_dec_digits, decimal_digits);
        w += tft.textWidth(dec_buf, 6);
    }
    // Check for changes
    const auto new_value = std::string(int_buf) + std::string(".") + std::string(dec_buf);
    if (new_value == last_value[quadrant])
        return;
    last_value[quadrant] = new_value;

    set_colour(value, thresholds, invert);
    tft.fillRect(ul.first, ul.second + LEGEND_HEIGHT, TFT_HEIGHT/2, TFT_WIDTH/2 - LEGEND_HEIGHT, TFT_BLACK);

    const int x = ul.first + (TFT_HEIGHT/2 - w)/2;
    const int y = ul.second + TFT_WIDTH/8;
    tft.drawString(int_buf, x, y, 8);
    if (nof_dec_digits)
        tft.drawString(dec_buf, x + int_w, y + 38, 6);
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
