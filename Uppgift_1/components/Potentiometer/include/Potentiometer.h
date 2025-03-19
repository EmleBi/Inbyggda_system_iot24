/*#ifndef POTENTIOMETER_H

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
#endif*/

//Mattias la in bool callback_on_increment och ...decrement
/*#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdio.h>
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include "esp_log.h"

typedef void (*adc_sensor_threshold_callback_t)(int adc_pin, int value, bool rising_edge);

typedef struct {
    int adc_pin;
    int threshold;
    int last_value;  // Föregående värde
    bool callback_on_increment;
    bool callback_on_decrament;
    adc_oneshot_unit_handle_t adc_handle;
    adc_sensor_threshold_callback_t callback;
} adc_sensor_t;

void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback, 
    bool increment, bool decrement);

#endif*/

//Potentiometer med get-funktion

/*#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdio.h>
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include "esp_log.h"

// Callback-typ för att hantera tröskelhändelser
typedef void (*adc_sensor_threshold_callback_t)(int adc_pin, int value, bool rising_edge);

typedef struct {
    int adc_pin;
    int threshold;
    int last_value;  // Föregående värde
    bool callback_on_increment;  // Aktivera callback för "rising edge"
    bool callback_on_decrament;  // Aktivera callback för "falling edge"
    adc_oneshot_unit_handle_t adc_handle;
    adc_sensor_threshold_callback_t callback;  // Callback-funktion
} adc_sensor_t;

void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback, 
    bool increment, bool decrement);
int getValue(adc_sensor_t *sensor);

#endif*/

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdio.h>
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include "esp_log.h"
#include "esp_timer.h"  // Timer för debounce

#define DEBOUNCE_SAMPLES 5 // Antal historiska värden för debounce

// Callback-typ för att hantera tröskelhändelser
typedef void (*adc_sensor_threshold_callback_t)(int adc_pin, int value, bool rising_edge);

typedef struct {
    int adc_pin;
    int threshold;
    int last_value;  // Föregående värde
    int last_filtered_value;  // Senast filtrerade värde
    bool callback_on_increment;  // Aktivera callback för "rising edge"
    bool callback_on_decrament;  // Aktivera callback för "falling edge"
    adc_oneshot_unit_handle_t adc_handle;
    adc_sensor_threshold_callback_t callback;  // Callback-funktion
    int64_t last_trigger_time;  // Tidsstämpel för debounce
    int value_history[DEBOUNCE_SAMPLES];  // Historiska värden för medelvärdesfilter
    int history_index;  // Index för historiska värden
} adc_sensor_t;

void adc_init(adc_sensor_t *sensor, int adc_pin);
void adc_update(adc_sensor_t *sensor);
void adc_set_on_threshold(adc_sensor_t *sensor, int threshold, adc_sensor_threshold_callback_t callback, 
    bool increment, bool decrement);
int getValue(adc_sensor_t *sensor);

#endif
