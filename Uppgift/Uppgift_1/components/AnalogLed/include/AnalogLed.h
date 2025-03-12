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

// Struct definition för AnalogLed
typedef struct {
    uint8_t pin;
    uint8_t brightness;
    uint8_t blink_on;
    uint8_t blink_off;
    uint8_t is_blinking;
    uint32_t period;
} AnalogLed;

void analogLed_init(AnalogLed* led, uint8_t pin);
void analogLed_update(AnalogLed* led);
void analogLed_setBrightness(AnalogLed* led, uint8_t value);
void analogLed_setBlinking(AnalogLed* led, uint8_t is_blinking);

#endif*/


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

// Struct definition för AnalogLed
typedef struct {
    uint8_t pin;
    uint8_t brightness;
    uint8_t blink_on;
    uint8_t blink_off;
    uint8_t is_blinking;
    uint32_t period;
    uint8_t mode_changed; // Indikerar om läget har ändrats
} AnalogLed;

void analogLed_init(AnalogLed* led, uint8_t pin);
void analogLed_update(AnalogLed* led);
void setAnalogLed(AnalogLed* led, uint8_t value);
void analogLed_setBlinking(AnalogLed* led, uint32_t period);
void set_led_blink_mode(AnalogLed* led, uint8_t blink_on, uint8_t blink_off);

#endif // ANALOGLED_H*/

#ifndef ANALOG_LED_H
#define ANALOG_LED_H

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define ANALOG_LED_PIN  2

typedef struct {
    int pin;
    int value;
    int is_sin_wave;
    int period;
    int amplitude;
    uint64_t last_update;
} AnalogLED_t;

void analog_led_init(AnalogLED_t *led, int pin);
void analog_led_update(AnalogLED_t *led);
void analog_set_led(AnalogLED_t *led, int value);
void analog_sin_wave(AnalogLED_t *led, int period, int amplitude);
void analog_sin_on(AnalogLED_t *led);
void analog_sin_off(AnalogLED_t *led);

#endif 


