#include "console.h"
#include "defs.h"
#include "display.h"
#include "hw.h"

#include <string>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"

#include <driver/uart.h>

#include <TFT_eSPI.h>

static constexpr const int GFXFF = 1;

#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"

static Display* the_display = nullptr;

static int toggle_compressor_relay(int, char**)
{
    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(500/portTICK_PERIOD_MS);
        set_compressor(true);
        vTaskDelay(500/portTICK_PERIOD_MS);
        set_compressor(false);
    }
    printf("done\n");
    return 0;
}

static const char* statuses[] = {
    "Idle",
    "Fan on",
    "Cooling",
    "Flow\ntoo low",
    "Too hot,\nlow flow",
    "Too hot",
    "Water hot!",
    "Compressor\nhot!",
    "ERROR:\nBad stuff",
};

static int test_display(int, char**)
{
    printf("Running display test\n");

    Thresholds water_thresholds;
    water_thresholds.push_back(std::make_pair(WATER_WARN_TEMP, TFT_YELLOW));
    water_thresholds.push_back(std::make_pair(WATER_HOT_TEMP, TFT_RED));
    Thresholds compressor_thresholds;
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_WARN_TEMP, TFT_YELLOW));
    compressor_thresholds.push_back(std::make_pair(COMPRESSOR_HOT_TEMP, TFT_RED));
    
    the_display->show_legends();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    int index = 0;
    for (int i = 0; i < 10; ++i)
    {
        the_display->show_temperature(0, (i+3)*7.89, water_thresholds);
        the_display->show_temperature(1, (i+3)*8.90, compressor_thresholds);
        the_display->show_flow(23+i*13);
        the_display->set_status(statuses[index++]);
        if (index >= sizeof(statuses)/sizeof(statuses[0]))
            index = 0;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    return 0;
}

static int test_temp(int, char**)
{
    printf("Running temperature sensor test\n");

    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(500/portTICK_PERIOD_MS);
        const auto values = read_temperatures();
        printf("Water %3.2f   Compressor %3.2f\n",
               values.water, values.compressor);
    }
    
    return 0;
}

static int test_flow(int, char**)
{
    printf("Running flow sensor test\n");

    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(500/portTICK_PERIOD_MS);
        const auto flow = gpio_get_level(PIN_FLOW);
        printf("Flow pin %d\n", flow);
    }
    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(500/portTICK_PERIOD_MS);
        const auto flow = get_and_reset_flow_pulses();
        printf("Flow %d\n", flow);
    }
    
    return 0;
}

static int test_fan(int, char**)
{
    printf("Running fan test\n");

    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(5000/portTICK_PERIOD_MS);
        printf("On\n");
        set_fan(true);
        vTaskDelay(5000/portTICK_PERIOD_MS);
        printf("Off\n");
        set_fan(false);
    }
    printf("done\n");
    return 0;
}

static int test_buzzer(int, char**)
{
    printf("Running buzzer test\n");

    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(5000/portTICK_PERIOD_MS);
        printf("On\n");
        set_buzzer(true);
        vTaskDelay(5000/portTICK_PERIOD_MS);
        printf("Off\n");
        set_buzzer(false);
    }
    printf("done\n");
    return 0;
}

static int test_ready(int, char**)
{
    printf("Running ready relay test\n");
    for (int n = 0; n < 10; ++n)
    {
        vTaskDelay(2000/portTICK_PERIOD_MS);
        set_ready(true);
        vTaskDelay(2000/portTICK_PERIOD_MS);
        set_ready(false);
    }
    printf("done\n");
    return 0;
}
 
static int reboot(int, char**)
{
    printf("Reboot...\n");
    esp_restart();
    return 0;
}

void initialize_console()
{
    /* Disable buffering on stdin */
    setvbuf(stdin, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_port_set_rx_line_endings(0, ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_port_set_tx_line_endings(0, ESP_LINE_ENDINGS_CRLF);

    /* Configure UART. Note that REF_TICK is used so that the baud rate remains
     * correct while APB frequency is changing in light sleep mode.
     */
    uart_config_t uart_config;
    memset(&uart_config, 0, sizeof(uart_config));
    uart_config.baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.source_clk = UART_SCLK_REF_TICK;
    ESP_ERROR_CHECK(uart_param_config((uart_port_t) CONFIG_ESP_CONSOLE_UART_NUM, &uart_config));

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK(uart_driver_install((uart_port_t) CONFIG_ESP_CONSOLE_UART_NUM,
                                         256, 0, 0, NULL, 0));

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Initialize the console */
    esp_console_config_t console_config;
    memset(&console_config, 0, sizeof(console_config));
    console_config.max_cmdline_args = 8;
    console_config.max_cmdline_length = 256;
#if CONFIG_LOG_COLORS
    console_config.hint_color = atoi(LOG_COLOR_CYAN);
#endif
    ESP_ERROR_CHECK(esp_console_init(&console_config));

    /* Configure linenoise line completion library */
    /* Enable multiline editing. If not set, long commands will scroll within
     * single line.
     */
    linenoiseSetMultiLine(1);

    /* Tell linenoise where to get command completions and hints */
    linenoiseSetCompletionCallback(&esp_console_get_completion);
    linenoiseSetHintsCallback((linenoiseHintsCallback*) &esp_console_get_hint);

    /* Set command history size */
    linenoiseHistorySetMaxLen(100);
}

void run_console(Display& display)
{
    the_display = &display;
    
    initialize_console();

    esp_console_register_help_command();

    const esp_console_cmd_t toggle_compressor_relay_cmd = {
        .command = "compressor_relay",
        .help = "Toggle compressor relay",
        .hint = nullptr,
        .func = &toggle_compressor_relay,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&toggle_compressor_relay_cmd));

    const esp_console_cmd_t test_display_cmd = {
        .command = "test_display",
        .help = "Test display",
        .hint = nullptr,
        .func = &test_display,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_display_cmd));

    const esp_console_cmd_t test_temp_cmd = {
        .command = "test_temp",
        .help = "Test temperature sensors",
        .hint = nullptr,
        .func = &test_temp,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_temp_cmd));

    const esp_console_cmd_t test_flow_cmd = {
        .command = "test_flow",
        .help = "Test flowerature sensors",
        .hint = nullptr,
        .func = &test_flow,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_flow_cmd));

    const esp_console_cmd_t test_fan_cmd = {
        .command = "test_fan",
        .help = "Test fan control",
        .hint = nullptr,
        .func = &test_fan,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_fan_cmd));

    const esp_console_cmd_t test_buzzer_cmd = {
        .command = "test_buzzer",
        .help = "Test buzzer control",
        .hint = nullptr,
        .func = &test_buzzer,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_buzzer_cmd));

    const esp_console_cmd_t test_ready_cmd = {
        .command = "test_ready",
        .help = "Test ready relay",
        .hint = nullptr,
        .func = &test_ready,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&test_ready_cmd));

    const esp_console_cmd_t reboot_cmd = {
        .command = "reboot",
        .help = "Reboot",
        .hint = nullptr,
        .func = &reboot,
        .argtable = nullptr
    };
    ESP_ERROR_CHECK(esp_console_cmd_register(&reboot_cmd));
    
    const char* prompt = LOG_COLOR_I "chiller> " LOG_RESET_COLOR;
    int probe_status = linenoiseProbe();
    if (probe_status)
    {
        printf("\n"
               "Your terminal application does not support escape sequences.\n"
               "Line editing and history features are disabled.\n"
               "On Windows, try using Putty instead.\n");
        linenoiseSetDumbMode(1);
#if CONFIG_LOG_COLORS
        /* Since the terminal doesn't support escape sequences,
         * don't use color codes in the prompt.
         */
        prompt = "esp32> ";
#endif //CONFIG_LOG_COLORS
    }

    while (true)
    {
        char* line = linenoise(prompt);
        if (!line)
            continue;

        linenoiseHistoryAdd(line);

        int ret;
        esp_err_t err = esp_console_run(line, &ret);
        if (err == ESP_ERR_NOT_FOUND)
            printf("Unrecognized command\n");
        else if (err == ESP_ERR_INVALID_ARG)
            ; // command was empty
        else if (err == ESP_OK && ret != ESP_OK)
            printf("Command returned non-zero error code: 0x%x (%s)\n", ret, esp_err_to_name(err));
        else if (err != ESP_OK)
            printf("Internal error: %s\n", esp_err_to_name(err));

        linenoiseFree(line);
    }
}

// Local Variables:
// compile-command: "(cd ..; idf.py build)"
// End:
