
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
/*#include "ergebe_Led.h"
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
}*/

//nytt försök 2 - ej fungerande: 
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
}

void ergebe_led_shutdown(void) {
    gpio_set_level(RED_LED_PIN, 0);   // Stäng av Röd LED
    gpio_set_level(GREEN_LED_PIN, 0); // Stäng av Grön LED
    gpio_set_level(BLUE_LED_PIN, 0);  // Stäng av Blå LED
    ESP_LOGI(TAG, "RGB LEDs shut down");
}*/

//förenklad version: 
// ergebe_led.c
/*#include "ergebe_led.h"
#include "driver/gpio.h"

void rgb_led_init() {
    gpio_reset_pin(RED_LED_PIN);
    gpio_reset_pin(GREEN_LED_PIN);
    gpio_reset_pin(BLUE_LED_PIN);
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLUE_LED_PIN, GPIO_MODE_OUTPUT);
    turn_off_led();
}

void set_led_red() {
    gpio_set_level(RED_LED_PIN, 1);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
}

void set_led_green() {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 1);
    gpio_set_level(BLUE_LED_PIN, 0);
}

void set_led_blue() {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 1);
}

void turn_off_led() {
    gpio_set_level(RED_LED_PIN, 0);
    gpio_set_level(GREEN_LED_PIN, 0);
    gpio_set_level(BLUE_LED_PIN, 0);
}*/

//fungerar men inte rätt
/*#include "ergebe_Led.h"
#include <esp_log.h>

static const char* TAG = "ergebe_Led";
static gpio_num_t red_pin, green_pin, blue_pin;

void ergebe_Led_init(gpio_num_t r_pin, gpio_num_t g_pin, gpio_num_t b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;

    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);

    gpio_set_direction(red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(blue_pin, GPIO_MODE_OUTPUT);

    ergebe_Led_set(LED_OFF);
}

void ergebe_Led_set(led_color_t color) {
    // Stäng av alla LED:er först
    gpio_set_level(red_pin, 0);
    gpio_set_level(green_pin, 0);
    gpio_set_level(blue_pin, 0);

    // Tänd den valda färgen
    switch(color) {
        case LED_RED:
            gpio_set_level(red_pin, 1);
            ESP_LOGI(TAG, "LED color: RED");
            break;
        case LED_GREEN:
            gpio_set_level(green_pin, 1);
            ESP_LOGI(TAG, "LED color: GREEN");
            break;
        case LED_BLUE:
            gpio_set_level(blue_pin, 1);
            ESP_LOGI(TAG, "LED color: BLUE");
            break;
        default:
            ESP_LOGI(TAG, "LED color: OFF");
            break;
    }
}*/

/*#include "ergebe_Led.h"
#include <esp_log.h>

static const char* TAG = "ergebe_Led";
static gpio_num_t red_pin, green_pin, blue_pin;

void ergebe_Led_init(gpio_num_t r_pin, gpio_num_t g_pin, gpio_num_t b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;

    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);

    gpio_set_direction(red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(blue_pin, GPIO_MODE_OUTPUT);

    ergebe_Led_set(LED_OFF);
}

void ergebe_Led_set(led_color_t color) {
    gpio_set_level(red_pin, 0);
    gpio_set_level(green_pin, 0);
    gpio_set_level(blue_pin, 0);

    switch(color) {
        case LED_RED:
            gpio_set_level(red_pin, 1);
            ESP_LOGI(TAG, "LED: RÖD - Jordens fuktighet för låg");
            break;
        case LED_GREEN:
            gpio_set_level(green_pin, 1);
            ESP_LOGI(TAG, "LED: GRÖN - Bevattning pågår");
            break;
        case LED_BLUE:
            gpio_set_level(blue_pin, 1);
            ESP_LOGI(TAG, "LED: BLÅ - System aktivt, fuktighet OK");
            break;
        default:
            ESP_LOGI(TAG, "LED: AV");
            break;
    }
}

void ergebe_Led_deinit(void) {
    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);
}*/

/*#include "ergebe_Led.h"
#include <esp_log.h>

static const char* TAG = "LED";
static gpio_num_t red_pin, green_pin, blue_pin;

void ergebe_Led_init(gpio_num_t r_pin, gpio_num_t g_pin, gpio_num_t b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;

    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);

    gpio_set_direction(red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(blue_pin, GPIO_MODE_OUTPUT);

    ergebe_Led_set(LED_OFF);
}

void ergebe_Led_set(led_color_t color) {
    gpio_set_level(red_pin, 0);
    gpio_set_level(green_pin, 0);
    gpio_set_level(blue_pin, 0);

    switch(color) {
        case LED_RED:
            gpio_set_level(red_pin, 1);
            ESP_LOGI(TAG, "LED: Röd - Torr jord");
            break;
        case LED_GREEN:
            gpio_set_level(green_pin, 1);
            ESP_LOGI(TAG, "LED: Grön - Bevattning pågår");
            break;
        case LED_BLUE:
            gpio_set_level(blue_pin, 1);
            ESP_LOGI(TAG, "LED: Blå - System aktivt, fuktighet OK");
            break;
        default:
            ESP_LOGI(TAG, "LED: Avstängd");
            break;
    }
}

void ergebe_Led_deinit(void) {
    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);
}*/

//kod med extra ext1 gpio-pins för deep-sleep
#include "ergebe_Led.h"
#include <esp_log.h>

static const char* TAG = "LED";
static gpio_num_t red_pin, green_pin, blue_pin;

// Initialize RGB LEDs
void ergebe_Led_init(gpio_num_t r_pin, gpio_num_t g_pin, gpio_num_t b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;

    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);

    gpio_set_direction(red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(blue_pin, GPIO_MODE_OUTPUT);

    ergebe_Led_set(LED_OFF);
    ESP_LOGI(TAG, "LED initialized on GPIO%d, %d, %d", r_pin, g_pin, b_pin);
}

// Set LED color
void ergebe_Led_set(led_color_t color) {
    gpio_set_level(red_pin, 0);  // Stäng av röd LED
    gpio_set_level(green_pin, 0);  // Stäng av grön LED
    gpio_set_level(blue_pin, 0);  // Stäng av blå LED

    switch (color) {
        case LED_RED:
            gpio_set_level(red_pin, 1);  // Aktivera röd LED
            ESP_LOGI(TAG, "LED: RED is now active on GPIO%d", red_pin);
            break;
        case LED_GREEN:
            gpio_set_level(green_pin, 1);  // Aktivera grön LED
            ESP_LOGI(TAG, "LED: GREEN - Pump active (GPIO%d)", green_pin);
            break;
        case LED_BLUE:
            gpio_set_level(blue_pin, 1);  // Aktivera blå LED
            ESP_LOGI(TAG, "LED: BLUE - System active, moisture OK (GPIO%d)", blue_pin);
            break;
        default:
            ESP_LOGI(TAG, "LED: OFF (GPIO%d, %d, %d)", red_pin, green_pin, blue_pin);
            break;
    }
}

// Deinitialize RGB LEDs
void ergebe_Led_deinit(void) {
    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);
    ESP_LOGI(TAG, "LED: All RGB pins deinitialized (GPIO%d, %d, %d)", red_pin, green_pin, blue_pin);
}

//ds-kod

/*#include "ergebe_Led.h"
#include <esp_log.h>

static const char* TAG = "LED";
static gpio_num_t red_pin, green_pin, blue_pin;

void ergebe_Led_init(gpio_num_t r_pin, gpio_num_t g_pin, gpio_num_t b_pin) {
    red_pin = r_pin;
    green_pin = g_pin;
    blue_pin = b_pin;
    
    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);
    
    gpio_set_direction(red_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(green_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(blue_pin, GPIO_MODE_OUTPUT);
    
    ergebe_Led_set(LED_OFF);
    ESP_LOGI(TAG, "LED initialized on GPIO%d, %d, %d", r_pin, g_pin, b_pin);
}

void ergebe_Led_set(led_color_t color) {
    gpio_set_level(red_pin, 0);
    gpio_set_level(green_pin, 0);
    gpio_set_level(blue_pin, 0);

    switch (color) {
        case LED_RED:
            gpio_set_level(red_pin, 1);
            ESP_LOGI(TAG, "LED: RED - Soil moisture too low (GPIO%d)", red_pin);
            break;
        case LED_GREEN:
            gpio_set_level(green_pin, 1);
            ESP_LOGI(TAG, "LED: GREEN - Pump active (GPIO%d)", green_pin);
            break;
        case LED_BLUE:
            gpio_set_level(blue_pin, 1);
            ESP_LOGI(TAG, "LED: BLUE - System active, moisture OK (GPIO%d)", blue_pin);
            break;
        default:
            ESP_LOGI(TAG, "LED: OFF (GPIO%d, %d, %d)", red_pin, green_pin, blue_pin);
            break;
    }
}

void ergebe_Led_deinit(void) {
    gpio_reset_pin(red_pin);
    gpio_reset_pin(green_pin);
    gpio_reset_pin(blue_pin);
    ESP_LOGI(TAG, "LED: All RGB pins deinitialized (GPIO%d, %d, %d)", red_pin, green_pin, blue_pin);
}*/