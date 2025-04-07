//Senast fungerande version:

/*#include "temp_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"

static int temp_sensor_pin;
static int current_temp_value = 0;
static int temp_threshold = 0;
static bool temp_is_rising = true;
static TempThresholdCallback temp_threshold_callback = NULL;
static bool temp_is_active = false;
static adc_oneshot_unit_handle_t adc_handle;

void init_temp_sensor(int adc_pin) {
    temp_sensor_pin = adc_pin;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, temp_sensor_pin, &channel_config));
}

void update_temp_sensor(void) {
    if (!temp_is_active) return;

    int new_value;
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, temp_sensor_pin, &new_value));

    if (temp_threshold_callback != NULL) {
        if (temp_is_rising && current_temp_value < temp_threshold && new_value >= temp_threshold) {
            temp_threshold_callback(temp_sensor_pin, new_value, NULL);
        } else if (!temp_is_rising && current_temp_value > temp_threshold && new_value <= temp_threshold) {
            temp_threshold_callback(temp_sensor_pin, new_value, NULL);
        }
    }

    current_temp_value = new_value;
}

int get_temp_value(void) {
    return current_temp_value;
}

void set_temp_threshold(int threshold, bool is_rising, TempThresholdCallback callback, void *args) {
    temp_threshold = threshold;
    temp_is_rising = is_rising;
    temp_threshold_callback = callback;
}

void activate_temp_sensor(bool state) {
    temp_is_active = state;
}*/

//allra senaste version
/*#include "temp_sensor.h"
#include "adc_manager.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_mac.h"

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#define TAG "TEMPERATUR"

static int temp_sensor_pin;
static const int TEMP_READINGS = 5;
static const int DELAY_BETWEEN_READINGS_MS = 100;

void init_temp_sensor(int adc_pin) {
    temp_sensor_pin = adc_pin;
    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, temp_sensor_pin, &channel_config));
    ESP_LOGI(TAG, "Temperatursensor initierad på ADC-kanal %d", adc_pin);
    ESP_LOGI(TAG, "ADC-kanal %d konfigurerad för temperatursensor", adc_pin); 
}

int read_temp_value(void) {
    int sum = 0;
    for (int i = 0; i < TEMP_READINGS; i++) {
        int value;
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, temp_sensor_pin, &value));
        sum += value;
        vTaskDelay(pdMS_TO_TICKS(DELAY_BETWEEN_READINGS_MS));
    }
    int average = sum / TEMP_READINGS;
    ESP_LOGI(TAG, "Rå temperaturavläsning: %d", average);
    return average;
}*/

//ett nytt försök som fungera sist med fel
/*#include "temp_sensor.h"
#include "esp_log.h"
#include <math.h>

static const char *TAG = "TempSensor";

#define NTC_BETA 3950.0f
#define NTC_R25 10000.0f
#define NTC_R_REF 10000.0f
#define VOLTAGE_REF 3.3f
#define ADC_MAX 4095

void temp_sensor_init(void) {
    ESP_LOGI(TAG, "Temperature sensor initialized using ADC channel %d", ADC_MGR_CH_TEMPERATURE);
}

float read_temperature(void) {
    int raw_value = adc_manager_read(ADC_MGR_CH_TEMPERATURE);
    if (raw_value < 0) return NAN;
    
    float voltage = raw_value * (VOLTAGE_REF / ADC_MAX);
    float resistance = NTC_R_REF * (VOLTAGE_REF - voltage) / voltage;
    
    float steinhart = log(resistance / NTC_R25) / NTC_BETA;
    steinhart += 1.0f / (25.0f + 273.15f);
    float temperature_k = 1.0f / steinhart;
    float temperature_c = temperature_k - 273.15f;
    
    ESP_LOGD(TAG, "Raw: %d, V: %.3f, R: %.1f Ω, Temp: %.2f°C", 
             raw_value, voltage, resistance, temperature_c);
    return temperature_c;
}

int check_temp_status(float temperature) {
    if (isnan(temperature)) {
        ESP_LOGW(TAG, "Invalid temperature reading");
        return 0;
    }

    if (temperature > HIGH_TEMP_THRESHOLD) {
        ESP_LOGW(TAG, "High temperature: %.2f > %d", temperature, HIGH_TEMP_THRESHOLD);
        return 1;
    }
    if (temperature < LOW_TEMP_THRESHOLD) {
        ESP_LOGW(TAG, "Low temperature: %.2f < %d", temperature, LOW_TEMP_THRESHOLD);
        return -1;
    }
    return 0;
}*/

//nytt försök 2
#include "temp_sensor.h"
#include "esp_log.h"
#include <math.h>
#include "esp_mac.h"
#include "adc_manager.h"
#include <stdbool.h>

#define HIGH_TEMP_THRESHOLD 30  // Exempel på högt temperaturtröskelvärde (celsius)
#define LOW_TEMP_THRESHOLD 10   // Exempel på lågt temperaturtröskelvärde (celsius)

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "TempSensor";

#define NTC_BETA 3950.0f
#define NTC_R25 10000.0f
#define NTC_R_REF 10000.0f
#define VOLTAGE_REF 3.3f
#define ADC_MAX 4095

void temp_sensor_init(void) {
    ESP_LOGI(TAG, "Temperature sensor initialized using ADC channel %d", ADC_MGR_CH_TEMPERATURE);
}

float read_temperature(void) {
    int raw_value = adc_manager_read(ADC_MGR_CH_TEMPERATURE);
    if (raw_value < 0) return NAN;

    float voltage = raw_value * (VOLTAGE_REF / ADC_MAX);
    float resistance = NTC_R_REF * (VOLTAGE_REF - voltage) / voltage;

    float steinhart = log(resistance / NTC_R25) / NTC_BETA;
    steinhart += 1.0f / (25.0f + 273.15f);
    float temperature_k = 1.0f / steinhart;
    float temperature_c = temperature_k - 273.15f;

    ESP_LOGI(TAG, "Temperature: %.2f°C (Raw: %d)", temperature_c, raw_value);
    return temperature_c;
}

int check_temp_status(float temperature) {
    if (temperature > HIGH_TEMP_THRESHOLD) {
        ESP_LOGW(TAG, "High temperature detected: %.2f°C", temperature);
        return 1;
    } else if (temperature < LOW_TEMP_THRESHOLD) {
        ESP_LOGW(TAG, "Low temperature detected: %.2f°C", temperature);
        return -1;
    }
    return 0;
}

void temp_sensor_shutdown(void) {
    ESP_LOGI(TAG, "Temperature sensor shutting down for deep sleep");
}
