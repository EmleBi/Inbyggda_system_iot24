
//Senast fungerande versionen:

/*#include "ergebe_Led.h"
#include "driver/gpio.h"

#define RED_LED_PIN GPIO_NUM_8
#define GREEN_LED_PIN GPIO_NUM_9
#define BLUE_LED_PIN GPIO_NUM_15

void ergebe_Led_init(void) {
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLUE_LED_PIN, GPIO_MODE_OUTPUT);
    ergebe_Led_turn_off();
}

void ergebe_Led_set_red(bool state) {
    gpio_set_level(RED_LED_PIN, state);
}

void ergebe_Led_set_green(bool state) {
    gpio_set_level(GREEN_LED_PIN, state);
}

void ergebe_Led_set_blue(bool state) {
    gpio_set_level(BLUE_LED_PIN, state);
}

void ergebe_Led_turn_off(void) {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
}*/

//allra senasta versionen som fungerade
/*#include "ergebe_Led.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_mac.h"

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#define TAG "LED"

#define RED_LED_PIN GPIO_NUM_8
#define GREEN_LED_PIN GPIO_NUM_9
#define BLUE_LED_PIN GPIO_NUM_15

void ergebe_Led_init(void) {
    gpio_reset_pin(RED_LED_PIN);
    gpio_reset_pin(GREEN_LED_PIN);
    gpio_reset_pin(BLUE_LED_PIN);
    
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLUE_LED_PIN, GPIO_MODE_OUTPUT);
    ergebe_Led_turn_off();
    ESP_LOGI(TAG, "LEDer initierade");
}

void ergebe_Led_set_red(bool state) {
    gpio_set_level(RED_LED_PIN, state);
    ESP_LOGI(TAG, "Röd LED %s", state ? "PÅ" : "AV");
}

void ergebe_Led_set_green(bool state) {
    gpio_set_level(GREEN_LED_PIN, state);
    ESP_LOGI(TAG, "Grön LED %s", state ? "PÅ" : "AV");
}

void ergebe_Led_set_blue(bool state) {
    gpio_set_level(BLUE_LED_PIN, state);
    ESP_LOGI(TAG, "Blå LED %s", state ? "PÅ" : "AV");
}

void ergebe_Led_turn_off(void) {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    ESP_LOGI(TAG, "Alla LEDer av");
}*/

//ett nytt försök som fungerade sist med fel:
/*#include "ergebe_Led.h"
#include "esp_log.h"

static const char *TAG = "LED";

void ergebe_led_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << RED_LED_PIN) | (1ULL << GREEN_LED_PIN) | (1ULL << BLUE_LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    
    ESP_LOGI(TAG, "LEDs initialized");
}

void set_led_state(led_state_t state) {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    
    switch(state) {
        case LED_RED:
            gpio_set_level(RED_LED_PIN, 1);
            break;
        case LED_GREEN:
            gpio_set_level(GREEN_LED_PIN, 1);
            break;
        case LED_BLUE:
            gpio_set_level(BLUE_LED_PIN, 1);
            break;
        case LED_OFF:
        default:
            break;
    }
    
    ESP_LOGD(TAG, "LED state set to %d", state);
}*/

//nytt försök 2
#include "ergebe_Led.h"
#include "esp_log.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "LED";

void ergebe_led_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << RED_LED_PIN) | (1ULL << GREEN_LED_PIN) | (1ULL << BLUE_LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
    
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    
    ESP_LOGI(TAG, "LEDs initialized");
}

void set_led_state(led_state_t state) {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
    
    switch(state) {
        case LED_RED:
            gpio_set_level(RED_LED_PIN, 1);
            break;
        case LED_GREEN:
            gpio_set_level(GREEN_LED_PIN, 1);
            break;
        case LED_BLUE:
            gpio_set_level(BLUE_LED_PIN, 1);
            break;
        case LED_OFF:
        default:
            break;
    }
    
    ESP_LOGD(TAG, "LED state set to %d", state);
}
