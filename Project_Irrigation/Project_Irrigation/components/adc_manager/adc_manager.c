/*#include <stdio.h>
#include "adc_manager.h"

adc_oneshot_unit_handle_t adc_handle; // Global ADC-hanterare

void init_adc_manager(void) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));
}*/

//ett nytt försök som fungerade sist med fel
/*#include "adc_manager.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "ADC_Manager";
static adc_oneshot_unit_handle_t adc_handle = NULL;

void adc_manager_init(void) {
    if (adc_handle != NULL) {
        ESP_LOGE(TAG, "ADC already initialized");
        return;
    }

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_MGR_CH_HUMIDITY, &channel_config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_MGR_CH_TEMPERATURE, &channel_config));

    ESP_LOGI(TAG, "ADC Manager initialized");
}

int adc_manager_read(adc_manager_channel_t channel) {
    if (adc_handle == NULL) {
        ESP_LOGE(TAG, "ADC not initialized");
        return -1;
    }

    if (channel != ADC_MGR_CH_HUMIDITY && channel != ADC_MGR_CH_TEMPERATURE) {
        ESP_LOGE(TAG, "Invalid ADC channel: %d", channel);
        return -1;
    }

    int raw_value = 0;
    esp_err_t ret = adc_oneshot_read(adc_handle, (adc_channel_t)channel, &raw_value);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read ADC channel %d: %s", channel, esp_err_to_name(ret));
        return -1;
    }

    return raw_value;
}

void adc_manager_deinit(void) {
    if (adc_handle != NULL) {
        adc_oneshot_del_unit(adc_handle);
        adc_handle = NULL;
        ESP_LOGI(TAG, "ADC Manager deinitialized");
    }
}*/

//nytt försök 2
#include <stdio.h>
#include "adc_manager.h"
#include "esp_log.h"
#include "esp_err.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

static const char *TAG = "ADC_Manager";
static adc_oneshot_unit_handle_t adc_handle = NULL;

void adc_manager_init(void) {
    if (adc_handle != NULL) {
        ESP_LOGE(TAG, "ADC already initialized");
        return;
    }

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_MGR_CH_HUMIDITY, &channel_config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_MGR_CH_TEMPERATURE, &channel_config));

    ESP_LOGI(TAG, "ADC Manager initialized");
}

int adc_manager_read(adc_manager_channel_t channel) {
    if (adc_handle == NULL) {
        ESP_LOGE(TAG, "ADC not initialized");
        return -1;
    }

    int raw_value = 0;
    esp_err_t ret = adc_oneshot_read(adc_handle, (adc_channel_t)channel, &raw_value);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read ADC channel %d: %s", channel, esp_err_to_name(ret));
        return -1;
    }

    return raw_value;
}

void adc_manager_deinit(void) {
    if (adc_handle != NULL) {
        adc_oneshot_del_unit(adc_handle);
        adc_handle = NULL;
        ESP_LOGI(TAG, "ADC Manager deinitialized");
    }
}

void adc_manager_shutdown(void) {
    adc_manager_deinit();
    ESP_LOGI(TAG, "ADC Manager shutdown for deep sleep");
}

