
//Senast fungerande version:
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"

typedef void (*HumidityThresholdCallback)(int adc_pin, int value, void *args);

void init_humidity_sensor(int adc_pin);
void update_humidity_sensor(void);
int get_humidity_value(void);
void set_humidity_threshold(int threshold, bool is_rising, HumidityThresholdCallback callback, void *args);
void activate_humidity_sensor(bool state);

#endif*/

//allra senaste version:
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"
#include "adc_manager.h"

void init_humidity_sensor(int adc_pin);
int read_humidity_value(void);

#endif*/

//ett nytt försök som fungerade sist med fel:
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "adc_manager.h"

#define HUMIDITY_DRY_THRESHOLD 2000

void humidity_sensor_init(void);
int read_humidity(void);
bool is_soil_dry(int humidity_value);

#endif*/

//nytt försök 2
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include "adc_manager.h"

#define HUMIDITY_DRY_THRESHOLD 2000  // Justera tröskelvärdet enligt projektets krav

void humidity_sensor_init(void);
int read_humidity(void);
bool is_soil_dry(int humidity_value);
void humidity_sensor_shutdown(void);

#endif*/

//några justeringar... temperaturberoende tröskel

//ej fungerande
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_adc/adc_oneshot.h"
#include "adc_manager.h"

#define HUMIDITY_SENSOR_ADC_PIN ADC_CHANNEL_4
#define BASE_HUMIDITY_DRY_THRESHOLD 2000
#define HUMIDITY_TEMP_COEFFICIENT 20 // Justeringsfaktor för temperaturpåverkan

void humidity_sensor_init(void);
int read_humidity(void);
bool is_soil_dry(int humidity_value, float temperature);
void humidity_sensor_shutdown(void);

#endif*/

//förenklad version:

// humidity_sensor.h
/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <stdint.h>
#include "esp_adc/adc_oneshot.h"

#define HUMIDITY_SENSOR_ADC_PIN ADC_CHANNEL_4

void humidity_sensor_init(void);
uint8_t get_humidity_level(void);

#endif*/

//fungerar men inte rätt

/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>

#define HUMIDITY_THRESHOLD 30  // Under detta värde anses jorden vara torr

void humidity_sensor_init(adc_channel_t channel);
int humidity_sensor_read(void);
bool humidity_sensor_is_dry(void);

#endif*/

/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>

#define HUMIDITY_THRESHOLD 30

void humidity_sensor_init(adc_channel_t channel);
int humidity_sensor_read(void);
bool humidity_sensor_is_dry(void);
void humidity_sensor_deinit(void);

#endif*/

#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>

#define HUMIDITY_THRESHOLD 30

void humidity_sensor_init(adc_channel_t channel);
int humidity_sensor_read(void);
bool humidity_sensor_is_dry(void);
void humidity_sensor_deinit(void);

#endif

//ds-kod

/*#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H
#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>

#define HUMIDITY_THRESHOLD 30

void humidity_sensor_init(adc_channel_t channel);
int humidity_sensor_read(void);
bool humidity_sensor_is_dry(void);
void humidity_sensor_deinit(void);
#endif*/