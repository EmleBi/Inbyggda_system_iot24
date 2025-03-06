/*#include <stdio.h>
#include "driver/gpio.h"
//#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "led.h"

void app_main(void)
{
   // Button_t btn;
    //LED_t led;
   // init(&btn, 2);

   // button_setOnPressed(&btn, myButtonCallback);
    
    //led_init(&led,2);
    //setLed(&led,0);
    //setLed(&led,1);
    //blink(&led, 500, 3000);
    //setLed(&led,1);

    while (1)
    {
       // button_update(&btn);
       //update(&led);
       vTaskDelay(pdMS_TO_TICKS(10));

  }
}*/


/*VÄL-FUNGERANDE KOD TILL ANALOG-LED HÄR NEDAN:*/
/*#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <stdio.h>
#include "AnalogLed.h"

void app_main(void) {
    AnalogLed_t led;
    analog_led_init(2, &led);

    while (1) {
        // För att blinka: setAnalogLed(true, 1.00, 1.0, &led);
        // För att släcka: setAnalogLed(false, 0.0, 0.0, &led);
        // För att lysa jämt: setAnalogLed(true, 1.00, 0.0, &led);
        
        setAnalogLed(true, 1.00, 1.0, &led); // Justering
        update_analog(&led);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}*/

#include "driver/gpio.h"
#include "driver/adc.h"
#include <stdio.h>
#include "Potentiometer\include\Potentiometer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

Potentiometer_t pot1;

void pot1_onThreshold(int channel, uint32_t value) {
    printf("Potentiometer threshold crossed on channel %d with value: %d\n", channel, value);
}

void app_main(void) {
    pot_init(&pot1, ADC_CHANNEL_0); 
    pot_setOnThreshold(&pot1, 2048, true, pot1_onThreshold); // Exempelvärden för threshold och risingEdge

    while (true) {
        pot_update(&pot1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
