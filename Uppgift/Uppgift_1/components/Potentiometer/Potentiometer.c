/*#include "Potentiometer.h"
#include "esp_log.h"

#define ADC_WIDTH ADC_WIDTH_BIT_12
#define ADC_ATTEN ADC_ATTEN_DB_0

void pot_init(Potentiometer_t* pot, adc_channel_t channel) {
    pot->channel = channel;
    pot->raw_value = 0;
    pot->threshold = 0;
    pot->risingEdge = true;
    pot->onThreshold = NULL;
    
    adc_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_0,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_new_unit(&init_config1, &pot->adc1_handle);
}

void pot_update(Potentiometer_t* pot) {
    int new_value;
    adc_read(pot->adc1_handle, pot->channel, &new_value);

    if (new_value != pot->raw_value) {
        bool threshold_crossed = false;
        if (pot->risingEdge && new_value >= pot->threshold && pot->raw_value < pot->threshold) {
            threshold_crossed = true;
        } else if (!pot->risingEdge && new_value <= pot->threshold && pot->raw_value > pot->threshold) {
            threshold_crossed = true;
        }
        pot->raw_value = new_value;
        if (threshold_crossed && pot->onThreshold) {
            pot->onThreshold(pot->channel, new_value);
        }
    }
}

int pot_getValue(Potentiometer_t* pot) {
    return pot->raw_value;
}

void pot_setOnThreshold(Potentiometer_t* pot, uint32_t threshold, bool risingEdge, void (*onThreshold)(int channel, uint32_t value)) {
    pot->threshold = threshold;
    pot->risingEdge = risingEdge;
    pot->onThreshold = onThreshold;
}*/

#include "Potentiometer.h"
#include "esp_log.h"

#define TAG "POTENTIOMETER"

void init(MeasurementDevice *device, int adc_pin) {
    device->adc_pin = adc_pin; 
    device->current_value = 0; 
    device->previous_value = 0; 
    device->threshold = 0; 
    device->is_rising = true; 
    device->threshold_callback = NULL;
    device->filter_index = 0;
    device->is_active = false; 
    device->callback_args = NULL;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &device->adc_instance));

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_11, 
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(device->adc_instance, device->adc_pin, &channel_config));

    ESP_LOGI(TAG, "ADC initierad på pin: %d", device->adc_pin);
}

void update(MeasurementDevice *device) {
    if (!device->is_active) {
        return; 
    }

    int new_value;

    ESP_ERROR_CHECK(adc_oneshot_read(device->adc_instance, device->adc_pin, &new_value));

    if (device->filter_index >= FILTER_SIZE) {
        device->filter_index = 0;
    }
    device->filter_values[device->filter_index] = new_value;
    device->filter_index++;

    if (device->threshold_callback != NULL) {
        if (device->is_rising && device->previous_value < device->threshold && new_value >= device->threshold) {
            device->threshold_callback(device->adc_pin, new_value, device->callback_args); 
        } else if (!device->is_rising && device->previous_value > device->threshold && new_value <= device->threshold) {
            device->threshold_callback(device->adc_pin, new_value, device->callback_args); 
        }
    }

    device->previous_value = new_value;
    device->current_value = new_value;

    vTaskDelay(pdMS_TO_TICKS(10));
}

int getValue(MeasurementDevice *device) {
    return device->previous_value;
}

void setOnThreshold(MeasurementDevice *device, int threshold, bool is_rising, ThresholdCallback callback, void *args) {
    device->threshold = threshold;
    device->is_rising = is_rising;
    device->threshold_callback = callback;
    device->callback_args = args;
}

void threshold_callback(int adc_pin, int value, void *args) {
    printf("Threshold reached on pin %d with value %d\n", adc_pin, value);
}
