/*#include "Potentiometer.h"
#include "esp_log.h"

#define ADC_WIDTH ADC_WIDTH_BIT_12
#define ADC_ATTEN ADC_ATTEN_DB_0

void pot_init(Potentiometer_t* pot, adc_channel_t channel) {
    pot->channel = channel;
    pot->raw_value = 0;
    pot->threshold = 0;
    pot->risingEdge = true;
    pot->onThreshold = NULL;
    
    adc_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_0,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_new_unit(&init_config1, &pot->adc1_handle);
}

void pot_update(Potentiometer_t* pot) {
    int new_value;
    adc_read(pot->adc1_handle, pot->channel, &new_value);

    if (new_value != pot->raw_value) {
        bool threshold_crossed = false;
        if (pot->risingEdge && new_value >= pot->threshold && pot->raw_value < pot->threshold) {
            threshold_crossed = true;
        } else if (!pot->risingEdge && new_value <= pot->threshold && pot->raw_value > pot->threshold) {
            threshold_crossed = true;
        }
        pot->raw_value = new_value;
        if (threshold_crossed && pot->onThreshold) {
            pot->onThreshold(pot->channel, new_value);
        }
    }
}

int pot_getValue(Potentiometer_t* pot) {
    return pot->raw_value;
}

void pot_setOnThreshold(Potentiometer_t* pot, uint32_t threshold, bool risingEdge, void (*onThreshold)(int channel, uint32_t value)) {
    pot->threshold = threshold;
    pot->risingEdge = risingEdge;
    pot->onThreshold = onThreshold;
}*/
