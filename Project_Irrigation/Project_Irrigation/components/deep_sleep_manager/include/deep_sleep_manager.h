#ifndef DEEP_SLEEP_MANAGER_H
#define DEEP_SLEEP_MANAGER_H

#include <stdint.h>

void deep_sleep_manager_init(uint64_t sleep_time_us);
void deep_sleep_manager_enter(void);

#endif
