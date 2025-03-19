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
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(device->adc_instance, device->adc_pin, &channel_config));

    ESP_LOGI(TAG, "ADC initierad på pin: %d", device->adc_pin);
}

void updateMeasurementDevice(MeasurementDevice *device) {
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

void activateDevice(MeasurementDevice *device, bool state) {
    device->is_active = state;
}

void threshold_callback(int adc_pin, int value, void *args) {
    printf("Threshold reached on pin %d with value %d\n", adc_pin, value);
}
