/*#include "deep_sleep_manager.h"
#include "ergebe_Led.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "adc_manager.h"
#include "switch.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp_mac.h"


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
    ergebe_led_shutdown();
    humidity_sensor_shutdown();
    temp_sensor_shutdown();
    adc_manager_shutdown();
    switch_shutdown();

    // Konfigurera timer för att väcka systemet
    esp_sleep_enable_timer_wakeup(deep_sleep_duration_us);

    ESP_LOGI(TAG, "Entering deep sleep for %llu seconds", deep_sleep_duration_us / 1000000);
    esp_deep_sleep_start();
}*/

//ej fungerande:
/*#include "deep_sleep_manager.h"
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

    // Stäng av alla komponenter
    ergebe_led_shutdown();
    humidity_sensor_shutdown();
    temp_sensor_shutdown();
    switch_shutdown();
    adc_manager_shutdown();

    // Säkerställ att alla GPIO-pinnar är avstängda
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    gpio_set_level(SWITCH_PIN, 0);

    // Konfigurera timer för att väcka systemet
    esp_sleep_enable_timer_wakeup(60 * 1000000); // 1 minut
    ESP_LOGI(TAG, "Entering deep sleep for 60 seconds...");
    esp_deep_sleep_start();
}*/

// deep_sleep_manager.c
/*#include "deep_sleep_manager.h"
#include "esp_log.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "DeepSleep";

void deep_sleep_init() {
    // Konfigurera kraftdomäner för deep-sleep
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);  // Behåll RTC-periferien påslagen under sömn
    esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_OFF);       // Stäng av XTAL-domän för att spara energi
    ESP_LOGI(TAG, "Deep sleep power domains configured.");
}

void enter_deep_sleep(uint64_t sleep_time_us) {
    ESP_LOGI(TAG, "Entering deep sleep for %lld microseconds", sleep_time_us);

    // Ställ in timer för att väcka systemet
    esp_sleep_enable_timer_wakeup(sleep_time_us);

    // Starta deep sleep
    esp_deep_sleep_start();
    // Funktionen returnerar aldrig eftersom systemet stängs av
}

esp_sleep_wakeup_cause_t get_wakeup_reason() {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    ESP_LOGI(TAG, "Wakeup reason: %d", cause);
    return cause;
}*/

/*#include "deep_sleep_manager.h"
#include <esp_log.h>

static const char* TAG = "DeepSleep";

void deep_sleep_init(void) {
    esp_sleep_enable_timer_wakeup(60 * 1000000);  // Vakna efter 60 sekunder
    ESP_LOGI(TAG, "Deep sleep initialized");
}

void deep_sleep_enter(uint64_t sleep_time_us) {
    ESP_LOGI(TAG, "Entering deep sleep for %lld seconds", sleep_time_us / 1000000);
    esp_deep_sleep(sleep_time_us);
}*/

/*#include "deep_sleep_manager.h"
#include <esp_log.h>

static const char* TAG = "DeepSleep";

void deep_sleep_init(uint64_t sleep_time_us) {
    esp_sleep_enable_timer_wakeup(sleep_time_us);  // Konfigurera timer för deep sleep
    ESP_LOGI(TAG, "Deep sleep initialized. Timer set for %lld seconds", sleep_time_us / 1000000);
}

void deep_sleep_enter(void) {
    ESP_LOGI(TAG, "Entering deep sleep...");
    esp_deep_sleep_start();
}*/

//kod med extra GPIO-pins
/*#include "deep_sleep_manager.h"
#include <esp_log.h>
#include "driver/rtc_io.h"

static const char* TAG = "DeepSleep";

void deep_sleep_init(uint64_t sleep_time_us) {
    esp_sleep_enable_timer_wakeup(sleep_time_us);  // Konfigurera timer för deep sleep
    ESP_LOGI(TAG, "Deep sleep initialized. Timer set for %lld seconds", sleep_time_us / 1000000);
}

void register_ext1_wakeup(uint64_t gpio_pins, int wakeup_mode) {
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(gpio_pins, wakeup_mode));
    ESP_LOGI(TAG, "EXT1 wakeup registered for GPIO pins: 0x%llx, mode: %d", gpio_pins, wakeup_mode);
}

void deep_sleep_enter(void) {
    ESP_LOGI(TAG, "Entering deep sleep...");
    esp_deep_sleep_start();
}*/

#include "deep_sleep_manager.h"
#include <esp_log.h>
#include "driver/rtc_io.h"

static const char* TAG = "DeepSleep";

void deep_sleep_init(uint64_t sleep_time_us) {
    esp_sleep_enable_timer_wakeup(sleep_time_us);  // Konfigurera timer för deep sleep
    ESP_LOGI(TAG, "Deep sleep initialized. Timer set for %lld seconds", sleep_time_us / 1000000);
}

void register_ext1_wakeup(uint64_t gpio_pins, int wakeup_mode) {
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(gpio_pins, wakeup_mode));
    ESP_LOGI(TAG, "EXT1 wakeup registered for GPIO pins: 0x%llx, mode: %d", gpio_pins, wakeup_mode);
}

void deep_sleep_enter(void) {
    ESP_LOGI(TAG, "Entering deep sleep...");
    esp_deep_sleep_start();
}

//ds-kod
/*#include "deep_sleep_manager.h"
#include <esp_log.h>
#include "driver/rtc_io.h"

static const char* TAG = "DeepSleep";

void deep_sleep_init(uint64_t sleep_time_us) {
    esp_sleep_enable_timer_wakeup(sleep_time_us);
    ESP_LOGI(TAG, "Deep sleep initialized. Timer set for %lld seconds", sleep_time_us / 1000000);
}

void register_ext1_wakeup(uint64_t gpio_pins, int wakeup_mode) {
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup(gpio_pins, wakeup_mode));
    ESP_LOGI(TAG, "EXT1 wakeup registered for GPIO pins: 0x%llx, mode: %d", gpio_pins, wakeup_mode);
}

void deep_sleep_enter(void) {
    ESP_LOGI(TAG, "Entering deep sleep...");
    esp_deep_sleep_start();
}*/