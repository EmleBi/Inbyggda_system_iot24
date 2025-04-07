//ett nytt försök som fungerade sist med fel
/*#include "switch.h"
#include "esp_log.h"

static const char *TAG = "Switch";

void switch_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SWITCH_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(SWITCH_PIN, 0);
    ESP_LOGI(TAG, "Switch initialized on pin %d", SWITCH_PIN);
}

void switch_set(bool state) {
    gpio_set_level(SWITCH_PIN, state ? 1 : 0);
    ESP_LOGD(TAG, "Switch set to %s", state ? "ON" : "OFF");
}*/

//nytt försök 2
#include "switch.h"
#include "esp_log.h"
#include "esp_mac.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "Switch";

void switch_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SWITCH_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    gpio_set_level(SWITCH_PIN, 0);
    ESP_LOGI(TAG, "Switch initialized on pin %d", SWITCH_PIN);
}

void switch_set(bool state) {
    gpio_set_level(SWITCH_PIN, state ? 1 : 0);
    ESP_LOGD(TAG, "Switch set to %s", state ? "ON" : "OFF");
}
