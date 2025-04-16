//ett nytt försök som fungerade med fel

/*#ifndef SWITCH_H
#define SWITCH_H

#include "driver/gpio.h"

#define SWITCH_PIN GPIO_NUM_2

void switch_init(void);
void switch_set(bool state);

#endif*/

//nytt försök 2 - ej fungerande:
/* #ifndef SWITCH_H
#define SWITCH_H

#include "driver/gpio.h"

#define SWITCH_PIN GPIO_NUM_2

void switch_init(void);
void switch_set(bool state);
void switch_shutdown(void);  // Tillagd

#endif*/

//förenklad version:
/*#ifndef SWITCH_H
#define SWITCH_H

#include <stdbool.h>
#include "driver/gpio.h"

#define RELAY_PIN GPIO_NUM_2

void switch_init(void);
void activate_pump(bool state);
void deactivate_pump(void);

#endif*/

//fungerar men inte rätt

/*#ifndef SWITCH_H
#define SWITCH_H

#include <driver/gpio.h>

void switch_init(gpio_num_t pin);
void switch_on(void);
void switch_off(void);
bool switch_is_on(void);

#endif*/

/*#ifndef SWITCH_H
#define SWITCH_H

#include <driver/gpio.h>

void switch_init(gpio_num_t pin);
void switch_on(void);
void switch_off(void);
bool switch_is_on(void);
void switch_deinit(void);

#endif*/
#ifndef SWITCH_H
#define SWITCH_H

#include <driver/gpio.h>

void switch_init(gpio_num_t pin);
void switch_on(void);
void switch_off(void);
bool switch_is_on(void);
void switch_deinit(void);

#endif

//ds-kod

/*#ifndef SWITCH_H
#define SWITCH_H

#include <stdio.h>
#include <stdbool.h>
#include <driver/gpio.h>

void switch_init(gpio_num_t pin);
void switch_on(void);
void switch_off(void);
bool switch_is_on(void);
void switch_deinit(void);
#endif*/