
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "driver/adc.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    adc_channel_t channel;
    uint32_t raw_value;
    uint32_t threshold;
    bool risingEdge;
    void (*onThreshold)(int channel, uint32_t value);
    adc_unit_handle_t adc1_handle;
} Potentiometer_t;

void pot_init(Potentiometer_t* pot, adc_channel_t channel);
void pot_update(Potentiometer_t* pot);
int pot_getValue(Potentiometer_t* pot);
void pot_setOnThreshold(Potentiometer_t* pot, uint32_t threshold, bool risingEdge, void (*onThreshold)(int channel, uint32_t value));

#endif



