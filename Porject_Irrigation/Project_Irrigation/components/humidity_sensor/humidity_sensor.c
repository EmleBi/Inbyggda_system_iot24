#include "humidity_sensor.h"
#include <stdio.h>
#include <driver/adc.h>
#include "esp_adc_cal.h"

#define HUMIDITY_SENSOR_CHANNEL ADC_CHANNEL_6
#define DEFAULT_VREF 1100 // Default referensspänning i millivolt

static esp_adc_cal_characteristics_t *adc_chars;

void init_humidity_sensor(void) {
    // Konfigurera ADC-kanalen
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(HUMIDITY_SENSOR_CHANNEL, ADC_ATTEN_DB_11);

    // Kalibrera ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);

    printf("Fuktighetssensor initialiserad.\n");
}

float read_humidity(void) {
    // Läs ADC-värdet
    int raw_value = adc1_get_raw(HUMIDITY_SENSOR_CHANNEL);
    
    // Konvertera råvärde till spänning (millivolt)
    uint32_t voltage = esp_adc_cal_raw_to_voltage(raw_value, adc_chars);

    // Beräkna fuktighet baserat på spänning (exempelberäkning)
    float humidity = (voltage / 1000.0) * 100.0; // Antag att 0-1V motsvarar 0-100% fuktighet
    
    return humidity;
}
