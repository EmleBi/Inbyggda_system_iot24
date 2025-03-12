#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_task_wdt.h"

#define IDLE_CORE_0_BIT 0b01
#define IDLE_CORE_1_BIT 0b10
#define WATCHDOG_TIMEOUT 3000
#define WATCHDOG_TRIGGER true

// Knapp PIN-konfigurationer
#define BTN_INC_PIN GPIO_NUM_12

void IRAM_ATTR button_isr_handler(void* arg)
{
// knapptryck
    while (1)
    {

    }

}
void app_main(void)
{
    esp_taskwdt_config_t wdtConfig = {
        .idle_core_mask = IDLE_CORE_0_BIT | IDLE_CORE_1_BIT,
        .trigger_panic = true,
        .timeout_ms = 3000
    };
    esp_task_wdt_reconfigure(&wdtConfig);
    esp_task_wdt_add(NULL);

    // Konfiguration av knappar
    gpio_pad_select_gpio(BTN_INC_PIN);
    gpio_set_direction(BTN_INC_PIN_GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_INC_PIN_GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BTN_INC_PIN, button_isr_handler, NULL);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
