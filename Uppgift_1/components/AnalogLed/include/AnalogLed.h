/*#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/ledc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>

#define ANALOG_LED_PIN 2
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_FREQUENCY 5000

typedef struct {
    int pin;
    int value;
    int is_sin_wave;
    int period;
    uint64_t last_update;
} AnalogLED_t;

void analog_led_init(AnalogLED_t *led, int pin);
void analog_led_update(AnalogLED_t *led);
void analog_set_led(AnalogLED_t *led, int enable, int value);
void analog_sin_wave(AnalogLED_t *led, int period);

#endif*/

#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/ledc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>

#define ANALOG_LED_PIN 2
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_FREQUENCY 5000

typedef struct {
    int pin;
    int value;
    int is_sin_wave;
    int period;
    uint64_t last_update;
} AnalogLED_t;

void analog_led_init(AnalogLED_t *led, int pin);
void analog_led_update(AnalogLED_t *led);
void analog_set_led(AnalogLED_t *led, int value, int enable);
void analog_sin_wave(AnalogLED_t *led, int period);

#endif




