/*#ifndef ADC_MANAGER_H
#define ADC_MANAGER_H

#include "esp_adc/adc_oneshot.h"

extern adc_oneshot_unit_handle_t adc_handle; // Global ADC-hanterare

void init_adc_manager(void);

#endif*/

//ett nytt försök som fungerade sist med fel

/*#ifndef ADC_MANAGER_H
#define ADC_MANAGER_H

#include "esp_adc/adc_oneshot.h"

typedef enum {
    ADC_MGR_CH_HUMIDITY = ADC_CHANNEL_4,   // GPIO4
    ADC_MGR_CH_TEMPERATURE = ADC_CHANNEL_6  // GPIO6
} adc_manager_channel_t;

void adc_manager_init(void);
int adc_manager_read(adc_manager_channel_t channel);
void adc_manager_deinit(void);

#endif*/

//nytt försök 2
#ifndef ADC_MANAGER_H
#define ADC_MANAGER_H

#include "esp_adc/adc_oneshot.h"

typedef enum {
    ADC_MGR_CH_HUMIDITY = ADC_CHANNEL_4,
    ADC_MGR_CH_TEMPERATURE = ADC_CHANNEL_6
} adc_manager_channel_t;

void adc_manager_init(void);
int adc_manager_read(adc_manager_channel_t channel);
void adc_manager_deinit(void);
void adc_manager_shutdown(void);

#endif
