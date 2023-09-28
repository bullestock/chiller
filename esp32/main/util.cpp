#include "util.h"
#include "display.h"
#include "hw.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void fatal_error(Display& display, const std::string& error)
{
    printf("FATAL: %s\n", error.c_str());
    const auto msg = "ERROR:\n" + error;
    display.show_fatal_error(msg);
    set_ready(false);
    
    while (1)
    {
        set_buzzer(1);
        vTaskDelay(40/portTICK_PERIOD_MS);
        set_buzzer(0);
        vTaskDelay(80/portTICK_PERIOD_MS);
        set_buzzer(1);
        vTaskDelay(160/portTICK_PERIOD_MS);
        set_buzzer(0);
        vTaskDelay(320/portTICK_PERIOD_MS);
    }
}
