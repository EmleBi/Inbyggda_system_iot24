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
/*#include "switch.h"
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
*/

// ej fungerande version:

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
}

void switch_shutdown(void) {
    gpio_set_level(SWITCH_PIN, 0); // Stäng av GPIO för relä
    ESP_LOGI(TAG, "Switch GPIO shut down");
}*/

//förenklad version:
/*#include "switch.h"
#include "driver/gpio.h"

// Definiera RELAY_PIN direkt i denna fil
#define RELAY_PIN GPIO_NUM_2

void switch_init(void) {
    gpio_set_direction(RELAY_PIN, GPIO_MODE_OUTPUT);
}

void activate_pump(uint8_t state) {
    gpio_set_level(RELAY_PIN, state); // Relä styr pumpens ström
    printf("Pump status: %s\n", state ? "På" : "Av");
}*/

/*#include "switch.h"
#include "driver/gpio.h"

void switch_init() {
    gpio_reset_pin(RELAY_PIN);
    gpio_set_direction(RELAY_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(RELAY_PIN, 0);
}

void activate_pump(bool state) {
    gpio_set_level(RELAY_PIN, state);
}

void deactivate_pump() {
    gpio_set_level(RELAY_PIN, 0);
}*/

//Fungerar men inte rätt

/*#include "switch.h"
#include <esp_log.h>

static const char* TAG = "Switch";
static gpio_num_t relay_pin;
static bool is_on = false;

void switch_init(gpio_num_t pin) {
    relay_pin = pin;
    gpio_reset_pin(relay_pin);
    gpio_set_direction(relay_pin, GPIO_MODE_OUTPUT);
    switch_off();
}

void switch_on(void) {
    gpio_set_level(relay_pin, 1);
    is_on = true;
    ESP_LOGI(TAG, "Pump: ON");
}

void switch_off(void) {
    gpio_set_level(relay_pin, 0);
    is_on = false;
    ESP_LOGI(TAG, "Pump: OFF");
}

bool switch_is_on(void) {
    return is_on;
}*/


/*#include "switch.h"
#include <esp_log.h>

static const char* TAG = "Switch";
static gpio_num_t relay_pin;
static bool is_on = false;

void switch_init(gpio_num_t pin) {
    relay_pin = pin;
    gpio_reset_pin(relay_pin);
    gpio_set_direction(relay_pin, GPIO_MODE_OUTPUT);
    switch_off();
}

void switch_on(void) {
    gpio_set_level(relay_pin, 0);  // LOW aktiverar reläet
    is_on = true;
    ESP_LOGI(TAG, "Pump: PÅ (Relä aktivt)");
}

void switch_off(void) {
    gpio_set_level(relay_pin, 1);  // HIGH stänger av reläet
    is_on = false;
    ESP_LOGI(TAG, "Pump: AV (Relä inaktivt)");
}

bool switch_is_on(void) {
    return is_on;
}

void switch_deinit(void) {
    switch_off();
    gpio_reset_pin(relay_pin);
}*/

/*#include "switch.h"
#include <esp_log.h>

static const char* TAG = "PumpSwitch";
static gpio_num_t relay_pin;
static bool is_on = false;

void switch_init(gpio_num_t pin) {
    relay_pin = pin;
    gpio_reset_pin(relay_pin);
    gpio_set_direction(relay_pin, GPIO_MODE_OUTPUT);
    switch_off();  // Stäng av reläet som standard
    ESP_LOGI(TAG, "Relä initierad på GPIO%d", pin);
}

void switch_on(void) {
    gpio_set_level(relay_pin, 0);  // LOW aktiverar reläet
    is_on = true;
    ESP_LOGI(TAG, "Relä: PÅ (GPIO%d)", relay_pin);
}

void switch_off(void) {
    gpio_set_level(relay_pin, 1);  // HIGH stänger av reläet
    is_on = false;
    ESP_LOGI(TAG, "Relä: AV (GPIO%d)", relay_pin);
}

bool switch_is_on(void) {
    return is_on;
}

void switch_deinit(void) {
    switch_off();
    gpio_reset_pin(relay_pin);
    ESP_LOGI(TAG, "Relä: Deinitialiserad (GPIO%d)", relay_pin);
}*/

//kod med extra gpio-pins ext1 för deep-sleep

#include "switch.h"
#include <esp_log.h>

static const char* TAG = "PumpSwitch";
static gpio_num_t relay_pin;
static bool is_on = false;

// Initiera reläet
void switch_init(gpio_num_t pin) {
    relay_pin = pin;
    gpio_reset_pin(relay_pin);
    gpio_set_direction(relay_pin, GPIO_MODE_OUTPUT);
    switch_off();  // Turn off relay by default
    ESP_LOGI(TAG, "Relay initialized at GPIO%d", pin);
}

// Aktivera reläet
void switch_on(void) {
    gpio_set_level(relay_pin, 1);  // LOW activates relay
    is_on = true;
    ESP_LOGI(TAG, "Relay: ON (GPIO%d)", relay_pin);
}

// Stäng av reläet
void switch_off(void) {
    gpio_set_level(relay_pin, 0);  // HIGH deactivates relay
    is_on = false;
    ESP_LOGI(TAG, "Relay: OFF (GPIO%d)", relay_pin);
}

// Kontrollera om reläet är aktivt
bool switch_is_on(void) {
    return is_on;
}

// Deinitiera reläet
void switch_deinit(void) {
    switch_off();
    gpio_reset_pin(relay_pin);
    ESP_LOGI(TAG, "Relay: Deinitialized (GPIO%d)", relay_pin);
}

//ds-kod
/*#include "switch.h"
#include <esp_log.h>

static const char* TAG = "PumpSwitch";
static gpio_num_t relay_pin;
static bool is_on = false;

void switch_init(gpio_num_t pin) {
    relay_pin = pin;
    gpio_reset_pin(relay_pin);
    gpio_set_direction(relay_pin, GPIO_MODE_OUTPUT);
    switch_off(); // Turn off relay by default
    ESP_LOGI(TAG, "Relay initialized at GPIO%d", pin);
}

void switch_on(void) {
    gpio_set_level(relay_pin, 1); // HIGH activates pump (inverterad logik)
    is_on = true;
    ESP_LOGI(TAG, "Relay: ON (GPIO%d) - Pump is ACTIVE", relay_pin);
}

void switch_off(void) {
    gpio_set_level(relay_pin, 0); // LOW deactivates pump (inverterad logik)
    is_on = false;
    ESP_LOGI(TAG, "Relay: OFF (GPIO%d) - Pump is INACTIVE", relay_pin);
}

bool switch_is_on(void) {
    return is_on;
}

void switch_deinit(void) {
    switch_off();
    gpio_reset_pin(relay_pin);
    ESP_LOGI(TAG, "Relay: Deinitialized (GPIO%d)", relay_pin);
}*/


