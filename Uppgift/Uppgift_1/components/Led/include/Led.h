#ifndef LED_H
#define LED_H

#include <stdint.h>

#define LED_PIN  2

typedef struct {
    int pin;
    int value;
    int blink_on;
    int blink_off;
    int is_blinking;
    uint64_t last_toggle;
} LED_t;

void led_init (LED_t *led,int pin);
void update (LED_t *led);
void setLed ( LED_t *led,int value);

void blink(LED_t *led,int miliseocnds_on, int milliseconds_off);

#endif // LED_H
