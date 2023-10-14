#include "buzzer.h"

#include "hw.h"

static constexpr util::duration INTERVAL = std::chrono::milliseconds(1500);

void Buzzer::start()
{
    if (active)
        return;
    active = true;
    last_change = util::now();
    on = true;
}

void Buzzer::stop()
{
    if (!active)
        return;
    active = false;
    on = false;
}

void Buzzer::update()
{
    set_buzzer(on);
    if (!active)
        return;
    const auto elapsed = util::now() - last_change;
    if (elapsed < INTERVAL)
        return;
    last_change = util::now();
    on = !on;
}

// Local Variables:
// compile-command: "cd .. && idf.py build"
// End:
