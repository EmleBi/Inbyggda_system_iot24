#ifndef POTENTIOMETER_H

#define POTENTIOMETER_H
#define EDGE_RISING  0  //rising edge
#define EDGE_FALLING 1  // falling edge
#define EDGE_BOTH 2

#include <stdio.h>
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include "esp_log.h"

typedef void (*threshold_callback_t)(int adc_pin, int value,int edge_type);

typedef struct {
    int adc_pin;
    int threshold;
    int edge_type;
    int previous_value;
    bool threshold_crossed;
    threshold_callback_t on_threshold;
    adc_oneshot_unit_handle_t adc_handle;
} adc_sensor_t;

void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
int adc_get_value(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, int edge_type, threshold_callback_t callback);
void threshold_handler(int pin, int value,int edge_type);
#endif



