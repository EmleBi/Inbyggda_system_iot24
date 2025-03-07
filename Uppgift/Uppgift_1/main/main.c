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


/*VÄL-FUNGERANDE KOD / ANALOG-LED / NEDAN:*/
/*#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <stdio.h>
#include "AnalogLed.h"

void app_main(void) {
    AnalogLed_t led;
    analog_led_init(2, 200, 0.0, &led); // Initialisera med ett fast värde, t.ex. 200, och frekvens
    setAnalogLed(true, 255, 1.0, &led);

    while (1) {
        // För att få LED-lampan att lysa jämt:
        //setAnalogLed(true, 255, 1.0, &led); // Sätt duty cycle till 255 och frekvens till 0.0

        // För att släcka LED-lampan:
        // setAnalogLed(false, 0, 0.0, &led); // Sätt LED-lampan till av och duty cycle till 0

        // För att få LED-lampan att blinka i sinusvågor:
        // setAnalogLed(true, 200, 1.0, &led); // Sätt duty cycle till 200 och frekvens till 1.0

        update_analog(&led);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}*/

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>
#include <stdio.h>
#include "AnalogLed.h"

#define SIN_GPIO 2

void app_main(void) {
    AnalogLed led_A;
    printf("Init AnalogLed\n");
    analogLed_init(&led_A, SIN_GPIO);
    analogLed_setBrightness(&led_A, 200); // justering av ljusstyrkan
    analogLed_setSinWave(&led_A, 4000); // Sinus vågor 4 sekunder 2 upp - 2 ner 
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10)); // uppdateringens intervall
        analogLed_update(&led_A);
    }
}



/*nedan1: Potentiometer som jag har påbörjat*/
/*#include "driver/gpio.h"
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
}*/
