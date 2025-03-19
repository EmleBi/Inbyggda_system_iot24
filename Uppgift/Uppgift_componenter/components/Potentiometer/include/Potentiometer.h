#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef void (*ThresholdCallback)(int adc_pin, int value, void *args);

#define FILTER_SIZE 5

typedef struct {
    int adc_pin;
    int current_value;
    int previous_value;
    int threshold;
    bool is_rising;
    ThresholdCallback threshold_callback;
    int filter_values[FILTER_SIZE];
    int filter_index;
    bool is_active;
    adc_oneshot_unit_handle_t adc_instance;
    void *callback_args;
} MeasurementDevice;

void init(MeasurementDevice *device, int adc_pin);
void updateMeasurementDevice(MeasurementDevice *device); 
int getValue(MeasurementDevice *device);
void setOnThreshold(MeasurementDevice *device, int threshold, bool is_rising, ThresholdCallback callback, void *args);
void activateDevice(MeasurementDevice *device, bool state);
void threshold_callback(int adc_pin, int value, void *args);

#endif
