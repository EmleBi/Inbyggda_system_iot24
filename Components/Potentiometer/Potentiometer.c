#include "Potentiometer.h"

static const char *TAG = "ADC_SENSOR";

void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;
    sensor->threshold = 2000;  
    sensor->on_threshold = NULL;
    sensor->edge_type = EDGE_BOTH; 

    adc_oneshot_unit_init_cfg_t adc_config = {
        .unit_id = ADC_UNIT_1,
        .clk_src = ADC_DIGI_CLK_SRC_DEFAULT
    };
    adc_oneshot_new_unit(&adc_config, &sensor->adc_handle);

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12
    };
    adc_oneshot_config_channel(sensor->adc_handle, sensor->adc_pin, &channel_config);

    ESP_LOGI(TAG, "ADC initialized on pin %d", adc_pin);
}

void adc_update(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);

    if (sensor->previous_value == -1) { 
        sensor->previous_value = value;
        return;
    }

    if (sensor->on_threshold) {
        if (value > sensor->threshold && !sensor->threshold_crossed) {
            sensor->on_threshold(sensor->adc_pin, value, EDGE_RISING);
            sensor->threshold_crossed = true;  
        } 
        else if (value < sensor->threshold && sensor->threshold_crossed) { 
            sensor->on_threshold(sensor->adc_pin, value, EDGE_FALLING);
            sensor->threshold_crossed = false;  
        }
    }

    sensor->previous_value = value; 
}
int adc_get_value(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);
    return value;
}

void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback) {
    sensor->threshold = threshold;
    sensor->edge_type = edge_type;
    sensor->on_threshold = callback;
}

void threshold_handler(int pin, int value, int edge_type) {
    if (edge_type == EDGE_RISING) {
        printf("Rising Edge Reached on ADC pin %d! Value: %d\n", pin, value);
    } else if (edge_type == EDGE_FALLING) {
        printf("Falling Edge Reached on ADC pin %d! Value: %d\n", pin, value);
    }
}

