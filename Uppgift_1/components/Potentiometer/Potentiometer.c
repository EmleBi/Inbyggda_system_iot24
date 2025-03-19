/*#include "Potentiometer.h"

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
}*/

//med increment, decrement
/*#include "Potentiometer.h"

static const char *TAG = "ADC_SENSOR";

void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;
    sensor->threshold = 0;
    sensor->last_value = -1;  // Initiera med ett odefinierat värde
    sensor->callback = NULL;
    sensor->callback_on_increment = false;
    sensor->callback_on_decrament = false;

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

    ESP_LOGI(TAG, "ADC-sensor initierad på pin %d", adc_pin);
}

void adc_update(adc_sensor_t *sensor) {
    int value;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &value);

    if (sensor->callback) {
        if (sensor->callback_on_increment && sensor->last_value < sensor->threshold && value >= sensor->threshold) {
            // Rising edge nåddes
            sensor->callback(sensor->adc_pin, value, true);
        } 
        if (sensor->callback_on_decrament && sensor->last_value >= sensor->threshold && value < sensor->threshold) {
            // Falling edge nåddes
            sensor->callback(sensor->adc_pin, value, false);
        }
    }

    // Uppdatera senaste lästa värdet
    sensor->last_value = value;
}

void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback,
    bool increment, bool decrement) {
    sensor->threshold = threshold;
    sensor->callback = callback;
    sensor->callback_on_increment = increment;
    sensor->callback_on_decrament = decrement;

    ESP_LOGI(TAG, "Threshold satt till %d, Increment: %d, Decrement: %d", threshold, increment, decrement);
}*/

//med get-funktion senast fungerande:

/*#include "potentiometer.h"

void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;
    sensor->last_value = -1; // Sätt ett initialt ogiltigt värde för att undvika oönskade callback-utlösningar

    adc_oneshot_unit_init_cfg_t config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };
    adc_oneshot_new_unit(&config, &sensor->adc_handle);

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_11
    };
    adc_oneshot_config_channel(sensor->adc_handle, adc_pin, &channel_config);
}

void adc_update(adc_sensor_t *sensor) {
    int current_value = 0;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &current_value);

    if (sensor->callback) {
        // Undvik callback vid första läsningen (ogiltigt initialtillstånd)
        if (sensor->last_value == -1) {
            sensor->last_value = current_value; // Initiera med det första värdet
            return;
        }

        // Kontrollera om rising edge nås
        if (sensor->callback_on_increment &&
            current_value >= sensor->threshold && 
            sensor->last_value < sensor->threshold) {
            sensor->callback(sensor->adc_pin, sensor->threshold, true); // Rising edge vid exakt tröskelvärde
        }

        // Kontrollera om falling edge nås
        if (sensor->callback_on_decrament &&
            current_value < sensor->threshold && 
            sensor->last_value >= sensor->threshold) {
            sensor->callback(sensor->adc_pin, sensor->threshold, false); // Falling edge vid exakt tröskelvärde
        }
    }

    // Uppdatera senaste värdet
    sensor->last_value = current_value;
}

void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback, 
                          bool increment, bool decrement) {
    sensor->threshold = threshold;
    sensor->callback = callback;
    sensor->callback_on_increment = increment;
    sensor->callback_on_decrament = decrement;
}

int getValue(adc_sensor_t *sensor) {
    return sensor->last_value;
}*/

//Potentiometer med hysteresis

#include "potentiometer.h"

#define HYSTERESIS 50              // Tolerans runt tröskeln
#define DEBOUNCE_DELAY_MS 300      // Förläng debounce-tid

// Medelvärdesfilter över flera läsningar
static int compute_moving_average(int *values, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += values[i];
    }
    return sum / size;
}

void adc_init(adc_sensor_t *sensor, int adc_pin) {
    sensor->adc_pin = adc_pin;
    sensor->last_value = -1;  // Ogiltigt initialvärde
    sensor->last_filtered_value = 0;  // Initiera filtrerat värde
    sensor->last_trigger_time = 0;  // Initiera debounce-tidsstämpel

    // Initiera historikbuffer
    for (int i = 0; i < DEBOUNCE_SAMPLES; i++) {
        sensor->value_history[i] = 0;
    }
    sensor->history_index = 0;

    adc_oneshot_unit_init_cfg_t config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };
    adc_oneshot_new_unit(&config, &sensor->adc_handle);

    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_11
    };
    adc_oneshot_config_channel(sensor->adc_handle, adc_pin, &channel_config);
}

void adc_update(adc_sensor_t *sensor) {
    int raw_value = 0;
    adc_oneshot_read(sensor->adc_handle, sensor->adc_pin, &raw_value);

    // Uppdatera historikbuffer
    sensor->value_history[sensor->history_index] = raw_value;
    sensor->history_index = (sensor->history_index + 1) % DEBOUNCE_SAMPLES;

    // Beräkna det glidande medelvärdet
    int filtered_value = compute_moving_average(sensor->value_history, DEBOUNCE_SAMPLES);

    // Kontrollera om signalen är stabil
    if (sensor->callback) {
        // Rising edge
        if (sensor->callback_on_increment &&
            filtered_value >= sensor->threshold + HYSTERESIS &&
            sensor->last_filtered_value < sensor->threshold - HYSTERESIS) {
            sensor->callback(sensor->adc_pin, filtered_value, true);
        }

        // Falling edge
        if (sensor->callback_on_decrament &&
            filtered_value <= sensor->threshold - HYSTERESIS &&
            sensor->last_filtered_value > sensor->threshold + HYSTERESIS) {
            sensor->callback(sensor->adc_pin, filtered_value, false);
        }
    }

    // Uppdatera senaste filtrerade värdet
    sensor->last_filtered_value = filtered_value;
}

void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback, 
                          bool increment, bool decrement) {
    sensor->threshold = threshold;
    sensor->callback = callback;
    sensor->callback_on_increment = increment;
    sensor->callback_on_decrament = decrement;
}

int getValue(adc_sensor_t *sensor) {
    return sensor->last_filtered_value;
}
