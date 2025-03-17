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

//nedan ANALOG LED

#include "AnalogLed.h"

AnalogLED_t my_led;

void app_main(void) {
    analog_led_init(&my_led, ANALOG_LED_PIN);
    analog_set_led(&my_led, 1023, 1); // Ljusstyrka (0-1023), sinus avstängd (0), på (1)
    analog_sin_wave(&my_led, 400);    // Sinusvågen: slå på med period i millisekunder

    analog_set_led(&my_led, 50, 0); // Ljusstyrka (0-1023), sinus avstängd (0), på (1)
    while (1) {
        analog_led_update(&my_led);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}




//nedan POTENTIOMETER version 1 och 2 (förbättrad)

/*#include <stdio.h>
#include "Potentiometer/include/Potentiometer.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"

  
#define ADC_PIN ADC_CHANNEL_4
  
  
  
void app_main() {
    adc_sensor_t sensor;
    adc_init(&sensor, ADC_PIN);
    adc_set_on_threshold(&sensor, 2000, 2, threshold_handler);
      
  
    while (1) {
        adc_update(&sensor);
        vTaskDelay(pdMS_TO_TICKS(500)); 
    }
}*/

/*#include <stdio.h>
#include "Potentiometer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ADC_PIN ADC_CHANNEL_4
#define POTENTIOMETER_PIN ADC_CHANNEL_5 // Potentiometer för att ändra tröskelvärde

bool rising_edge; // Global boolean för stigande flank

void threshold_handler(int pin, int value, bool rising_edge) {
    if (rising_edge) {
        printf("Rising Edge nåddes på ADC pin %d! Värde: %d\n", pin, value);
    } else {
        printf("Falling Edge nåddes på ADC pin %d! Värde: %d\n", pin, value);
    }
}

void app_main() {
    adc_sensor_t sensor;
    adc_sensor_t potentiometer;

    // Initialisera ADC för både sensorn och potentiometern
    adc_sensor_init(&sensor, ADC_PIN);
    adc_sensor_init(&potentiometer, POTENTIOMETER_PIN);

    // Här kan vi ställa in rising_edge till true (rising) eller false (falling)
    adc_sensor_set_on_threshold(&sensor, true, threshold_handler); // Exempel: stigande flank

    while (1) {
        // Läs potentiometerns värde för att uppdatera tröskelvärdet
        int potentiometer_value = adc_sensor_get_value(&potentiometer);

        // Uppdatera sensorn och passera potentiometerns värde
        adc_sensor_update(&sensor, potentiometer_value);

        // Visa den aktuella statusen för rising_edge
        if (sensor.risingEdge) {
            printf("Rising Edge är aktiv (true)\n");
        } else {
            printf("Falling Edge är aktiv (false)\n");
        }

        vTaskDelay(pdMS_TO_TICKS(500)); // Fördröjning
    }
}*/

