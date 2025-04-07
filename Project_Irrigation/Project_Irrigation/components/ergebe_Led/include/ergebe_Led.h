
//Senast fungerande version:
/*#ifndef ERGEBE_LED_H
#define ERGEBE_LED_H

#include <stdint.h>
#include <stdbool.h>

void ergebe_Led_init(void);
void ergebe_Led_set_red(bool state);
void ergebe_Led_set_blue(bool state);
void ergebe_Led_set_green(bool state);
void ergebe_Led_turn_off(void);

#endif*/

//allra senast fungerade
/*#ifndef ERGEBE_LED_H
#define ERGEBE_LED_H

#include <stdint.h>
#include <stdbool.h>

void ergebe_Led_init(void);
void ergebe_Led_set_red(bool state);
void ergebe_Led_set_blue(bool state);
void ergebe_Led_set_green(bool state);
void ergebe_Led_turn_off(void);

#endif*/

//ett nytt försök som fungerade sist med fel
/*#ifndef ERGEBE_LED_H
#define ERGEBE_LED_H

#include "driver/gpio.h"

#define RED_LED_PIN GPIO_NUM_8
#define GREEN_LED_PIN GPIO_NUM_9
#define BLUE_LED_PIN GPIO_NUM_15

typedef enum {
    LED_OFF,
    LED_RED,
    LED_GREEN,
    LED_BLUE
} led_state_t;

void ergebe_led_init(void);
void set_led_state(led_state_t state);

#endif*/

//nytt försök 2
#ifndef ERGEBE_LED_H
#define ERGEBE_LED_H

#include "driver/gpio.h"
#include <stdint.h>
#include <stdbool.h>


#define RED_LED_PIN GPIO_NUM_8
#define GREEN_LED_PIN GPIO_NUM_9
#define BLUE_LED_PIN GPIO_NUM_15

typedef enum {
    LED_OFF,
    LED_RED,
    LED_GREEN,
    LED_BLUE
} led_state_t;

void ergebe_led_init(void);
void set_led_state(led_state_t state);

#endif
