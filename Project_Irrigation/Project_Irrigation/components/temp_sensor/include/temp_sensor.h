//Senast fungerande version:

/*#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"

typedef void (*TempThresholdCallback)(int adc_pin, int value, void *args);

void init_temp_sensor(int adc_pin);
void update_temp_sensor(void);
int get_temp_value(void);
void set_temp_threshold(int threshold, bool is_rising, TempThresholdCallback callback, void *args);
void activate_temp_sensor(bool state);

#endif*/

//allra senaste versionen efter Vanessa
/*#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"

void init_temp_sensor(int adc_pin);
int read_temp_value(void);

#endif*/

//ett nytt försök som fungerade sist med fel:
/*#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include "adc_manager.h"

#define HIGH_TEMP_THRESHOLD 30  // 30°C
#define LOW_TEMP_THRESHOLD 10   // 10°C

void temp_sensor_init(void);
float read_temperature(void);
int check_temp_status(float temperature);

#endif*/

//nytt försök 2:
/*#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#define TEMP_SENSOR_ADC_PIN ADC_CHANNEL_6
#define HIGH_TEMP_THRESHOLD 30  // Exempel på högt temperaturtröskelvärde
#define LOW_TEMP_THRESHOLD 10   // Exempel på lågt temperaturtröskelvärde

void temp_sensor_init(void);
float read_temperature(void);
int check_temp_status(float temperature);
void temp_sensor_shutdown(void);

#endif*/

