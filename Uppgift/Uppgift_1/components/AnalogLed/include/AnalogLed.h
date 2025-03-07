/*#ifndef ANALOGLED_H
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
    int duty_cycle; // Använd ett fast värde som t.ex. 200
    int target_duty_cycle;
    double amplitude;
    double frequency;
    bool led_on; // LED-läget
} AnalogLed_t;

void analog_led_init(int pin, int duty_cycle, double frequency, AnalogLed_t *led);
void update_analog(AnalogLed_t *led);
void setAnalogLed(bool led_on, int duty_cycle, double frequency, AnalogLed_t *led);
void sin_wave(double period, AnalogLed_t *led);

#endif // ANALOGLED_H */


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
    int duty_cycle = 255; // Använd ett fast värde som t.ex. 200
    int target_duty_cycle;
    double amplitude;
    double frequency;
    bool led_on; // LED-läget
    //int behavior; // Lägg till en variabel för att hålla lampans beteende
} AnalogLed_t;

void analog_led_init(int pin, int duty_cycle, double frequency, AnalogLed_t *led);
void update_analog(AnalogLed_t *led);
void setAnalogLed(bool led_on, int duty_cycle, double frequency, int behavior, AnalogLed_t *led);
void sin_wave(double period, AnalogLed_t *led);

#endif // ANALOGLED_H


