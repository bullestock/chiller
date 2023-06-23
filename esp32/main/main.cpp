#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "console.h"
#include "defs.h"
#include "hw.h"

extern "C"
void app_main()
{
    init_hardware();

    printf("Chiller v %s\n", VERSION);

    printf("\n\nPress a key to enter console\n");
    bool debug = false;
    for (int i = 0; i < 20; ++i)
    {
        if (getchar() != EOF)
        {
            debug = true;
            break;
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    if (debug)
        run_console();        // never returns

    printf("\nStarting application\n");
    //xTaskCreate(led_task, "led_task", 4*1024, NULL, 5, NULL);

    printf("Vibing...\n");
    while (1)
        vTaskDelay(1);
}
