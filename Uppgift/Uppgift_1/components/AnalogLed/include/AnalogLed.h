/*#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int pin;
    int timer_channel;
    TickType_t last_update;
    double period;
    double duty_cycle;
    double target_duty_cycle;
    double amplitude;
    double frequency;
    bool led_on; //LED:ens läge
} AnalogLed_t;

void analog_led_init(AnalogLed_t *led, int pin, int timer_channel, double period);
void update_analog(AnalogLed_t *led);
void setAnalogLed(AnalogLed_t *led, bool led_on, double duty_cycle, double frequency);
void sin_wave(AnalogLed_t *led, double period);

#endif*/

#ifndef ANALOGLED_H
#define ANALOGLED_H

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int pin;
    int timer_channel;
    TickType_t last_update;
    double period;
    double duty_cycle;
    double target_duty_cycle;
    double amplitude;
    double frequency;
    bool led_on; // Ny flagga för LED-läget
} AnalogLed_t;

void analog_led_init(int pin, AnalogLed_t *led);
void update_analog(AnalogLed_t *led);
void setAnalogLed(bool led_on, double duty_cycle, double frequency, AnalogLed_t *led); 
void sin_wave(double period, AnalogLed_t *led);

#endif


