//Senast fungerande:
/*#include "humidity_sensor.h"
#include <stdio.h>

#define HUMIDITY_FILTER_SIZE 5
#define HUMIDITY_ADC_ATTEN ADC_ATTEN_DB_12

static int humidity_sensor_pin;
static int current_humidity_value = 0;
static int humidity_threshold = 0;
static bool humidity_is_rising = true;
static HumidityThresholdCallback humidity_threshold_callback = NULL;
static int humidity_filter_values[HUMIDITY_FILTER_SIZE];
static int humidity_filter_index = 0;
static bool humidity_is_active = false;
static adc_oneshot_unit_handle_t adc_handle;

void init_humidity_sensor(int adc_pin) {
    humidity_sensor_pin = adc_pin;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    esp_err_t err = adc_oneshot_new_unit(&init_config, &adc_handle);
    if (err != ESP_OK) {
        printf("Error initializing ADC unit: %d\n", err);
        return;
    }

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = HUMIDITY_ADC_ATTEN,
        .bitwidth = ADC_BITWIDTH_12,
    };
    err = adc_oneshot_config_channel(adc_handle, humidity_sensor_pin, &channel_config);
    if (err != ESP_OK) {
        printf("Error configuring ADC channel: %d\n", err);
        return;
    }

    printf("Humidity sensor initialized on pin %d.\n", humidity_sensor_pin);
}

void update_humidity_sensor(void) {
    if (!humidity_is_active) return;

    int new_value;
    esp_err_t err = adc_oneshot_read(adc_handle, humidity_sensor_pin, &new_value);
    if (err != ESP_OK) {
        printf("Error reading ADC value: %d\n", err);
        return;
    }

    if (humidity_threshold_callback != NULL) {
        if (humidity_is_rising && current_humidity_value < humidity_threshold && new_value >= humidity_threshold) {
            humidity_threshold_callback(humidity_sensor_pin, new_value, NULL);
        }
    }

    current_humidity_value = new_value;
}

int get_humidity_value(void) {
    return current_humidity_value;
}

void set_humidity_threshold(int threshold, bool is_rising, HumidityThresholdCallback callback, void *args) {
    humidity_threshold = threshold;
    humidity_is_rising = is_rising;
    humidity_threshold_callback = callback;
}

void activate_humidity_sensor(bool state) {
    humidity_is_active = state;
}*/

//allra senaste versionen:
/*#include "humidity_sensor.h"
#include "adc_manager.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_mac.h"

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#define TAG "FUKTIGHET"

static int humidity_sensor_pin;
static const int HUMIDITY_READINGS = 5;
static const int DELAY_BETWEEN_READINGS_MS = 100;

void init_humidity_sensor(int adc_pin) {
    humidity_sensor_pin = adc_pin;

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, humidity_sensor_pin, &channel_config));
    ESP_LOGI(TAG, "Fuktighetssensor initierad på ADC-kanal %d", adc_pin);
    ESP_LOGI(TAG, "ADC-kanal %d konfigurerad för fuktighetssensor", adc_pin);
}

int read_humidity_value(void) {
    int sum = 0;
    for (int i = 0; i < HUMIDITY_READINGS; i++) {
        int value;
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, humidity_sensor_pin, &value));
        sum += value;
        vTaskDelay(pdMS_TO_TICKS(DELAY_BETWEEN_READINGS_MS));
    }
    int average = sum / HUMIDITY_READINGS;
    ESP_LOGI(TAG, "Fuktighetsavläsning: %d", average);
    return average;
}*/

//ett nytt försök som fungerade sist med fel:
/*#include "humidity_sensor.h"
#include "adc_manager.h"
#include "esp_log.h"

static const char *TAG = "HumiditySensor";

void humidity_sensor_init(void) {
    ESP_LOGI(TAG, "Humidity sensor initialized using ADC channel %d", ADC_MGR_CH_HUMIDITY);
}

int read_humidity(void) {
    return adc_manager_read(ADC_MGR_CH_HUMIDITY);
}

bool is_soil_dry(int humidity_value) {
    bool dry = humidity_value > HUMIDITY_DRY_THRESHOLD;
    ESP_LOGD(TAG, "Soil %s (value: %d, threshold: %d)", 
             dry ? "DRY" : "OK", humidity_value, HUMIDITY_DRY_THRESHOLD);
    return dry;
}*/

//nytt försök 2
/*#include "humidity_sensor.h"
#include "adc_manager.h"
#include "esp_log.h"
#include <stdbool.h>

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "HumiditySensor";

void humidity_sensor_init(void) {
    ESP_LOGI(TAG, "Humidity sensor initialized using ADC channel %d", ADC_MGR_CH_HUMIDITY);
}

int read_humidity(void) {
    return adc_manager_read(ADC_MGR_CH_HUMIDITY);
}

bool is_soil_dry(int humidity_value) {
    // Använd det definierade HUMIDITY_DRY_THRESHOLD
    bool dry = humidity_value > HUMIDITY_DRY_THRESHOLD;
    ESP_LOGI(TAG, "Soil %s (value: %d, threshold: %d)", dry ? "DRY" : "OK", humidity_value, HUMIDITY_DRY_THRESHOLD);
    return dry;
}

void humidity_sensor_shutdown(void) {
    ESP_LOGI(TAG, "Humidity sensor shutting down for deep sleep");
}*/

//några justeringar: 

#include "humidity_sensor.h"
#include "adc_manager.h"
#include "esp_log.h"
#include <stdbool.h>

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "HumiditySensor";

void humidity_sensor_init(void) {
    ESP_LOGI(TAG, "Humidity sensor initialized using ADC channel %d", ADC_MGR_CH_HUMIDITY);
}

int read_humidity(void) {
    return adc_manager_read(ADC_MGR_CH_HUMIDITY);
}

bool is_soil_dry(int humidity_value, float temperature) {
    // Temperaturberoende tröskelvärde
    int dynamic_threshold = BASE_HUMIDITY_DRY_THRESHOLD + (int)(temperature * HUMIDITY_TEMP_COEFFICIENT);
    
    bool dry = humidity_value > dynamic_threshold;
    ESP_LOGI(TAG, "Soil %s (value: %d, dynamic threshold: %d, temp: %.1f°C)", 
             dry ? "DRY" : "OK", humidity_value, dynamic_threshold, temperature);
    return dry;
}

void humidity_sensor_shutdown(void) {
    ESP_LOGI(TAG, "Humidity sensor shutting down for deep sleep");
}
