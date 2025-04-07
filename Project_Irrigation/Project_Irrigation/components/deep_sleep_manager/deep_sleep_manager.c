#include "deep_sleep_manager.h"
#include "ergebe_Led.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "adc_manager.h"
#include "switch.h"
#include "esp_sleep.h"
#include "esp_log.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "DeepSleepManager";
static uint64_t deep_sleep_duration_us = 0;

void deep_sleep_manager_init(uint64_t sleep_time_us) {
    deep_sleep_duration_us = sleep_time_us;
    ESP_LOGI(TAG, "Deep Sleep Manager initialized with duration: %llu seconds", sleep_time_us / 1000000);
}

void deep_sleep_manager_enter(void) {
    ESP_LOGI(TAG, "Preparing to enter deep sleep...");

    // Shutdown alla komponenter
    // ergebe_led_shutdown();
    humidity_sensor_shutdown();
    temp_sensor_shutdown();
    adc_manager_shutdown();
    // switch_shutdown();

    // Konfigurera timer för att väcka systemet
    esp_sleep_enable_timer_wakeup(deep_sleep_duration_us);

    ESP_LOGI(TAG, "Entering deep sleep for %llu seconds", deep_sleep_duration_us / 1000000);
    esp_deep_sleep_start();
}
