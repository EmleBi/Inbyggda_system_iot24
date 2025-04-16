//ej fungerande
/*#ifndef DEEP_SLEEP_MANAGER_H
#define DEEP_SLEEP_MANAGER_H

#include <stdint.h>

void deep_sleep_manager_init(uint64_t sleep_time_us);
void deep_sleep_manager_enter(void);

#endif*/
// deep_sleep_manager.h
/*#ifndef DEEP_SLEEP_MANAGER_H
#define DEEP_SLEEP_MANAGER_H

#include <esp_sleep.h>

void deep_sleep_init(uint64_t sleep_time_us);
void deep_sleep_enter(void);

#endif*/

//kod med extra GPIO-pins...
#ifndef DEEP_SLEEP_MANAGER_H
#define DEEP_SLEEP_MANAGER_H

#include <esp_sleep.h>

void deep_sleep_init(uint64_t sleep_time_us);
void deep_sleep_enter(void);
void register_ext1_wakeup(uint64_t gpio_pins, int wakeup_mode);

#endif

//ds-kod
/*#ifndef DEEP_SLEEP_MANAGER_H
#define DEEP_SLEEP_MANAGER_H
#include <esp_sleep.h>

void deep_sleep_init(uint64_t sleep_time_us);
void deep_sleep_enter(void);
void register_ext1_wakeup(uint64_t gpio_pins, int wakeup_mode);
#endif*/


