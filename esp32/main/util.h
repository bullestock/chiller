#pragma once

#include <chrono>
#include <string>

void fatal_error(class Display& display, const std::string& error);

namespace util
{

using duration = std::chrono::system_clock::duration;
using time_point = std::chrono::system_clock::time_point;

static inline time_point now()
{
    return std::chrono::system_clock::now();
}

constexpr time_point invalid_time_point()
{
    return time_point();
}

constexpr duration invalid_duration()
{
    return duration::min();
}

constexpr bool is_valid(const time_point& ts)
{
    return ts != invalid_time_point();
}

constexpr bool is_valid(const duration& dur)
{
    return dur != invalid_duration();
}

} // end namespace
