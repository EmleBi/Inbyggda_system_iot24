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
/*#include "AnalogLed.h"

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
}*/

//nedan POTENTIOMETER version 1 och 2 (förbättrad)

*#include <stdio.h>
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
}


//Potentiometer - increment, decrement
/*#include <stdio.h>
#include "Potentiometer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ADC_PIN ADC_CHANNEL_4

void threshold_handler(int pin, int value, bool rising_edge) {
    if (rising_edge) {
        printf("Rising Edge nåddes på ADC pin %d! Värde: %d\n", pin, value);
    } else {
        printf("Falling Edge nåddes på ADC pin %d! Värde: %d\n", pin, value);
    }
}


void app_main() {
    adc_sensor_t sensor;
    adc_init(&sensor, ADC_PIN);

    // Sätt threshold till 2000 och registrera callback
    adc_set_on_threshold(&sensor, 2000, threshold_handler, true, true);

    while (1) {
        adc_update(&sensor);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}*/

//med get-funktion


/*#include "potentiometer.h"

#define ADC_PIN 4 // Specificera vilken ADC pin som används

// Callback-funktion för tröskelhändelser
void threshold_handler(int adc_pin, int value, bool rising_edge) {
    if (rising_edge) {
        printf("Rising Edge nåddes på ADC pin %d! Värde: %d\n", adc_pin, value);
    } else {
        printf("Falling Edge nåddes på ADC pin %d! Värde: %d\n", adc_pin, value);
    }
}

void app_main() {
    adc_sensor_t sensor;

    // Initiera ADC-sensorn
    adc_init(&sensor, ADC_PIN);

    // Sätt tröskelvärde till 1500 och registrera callback för rising och falling edge
    adc_set_on_threshold(&sensor, 1500, threshold_handler, true, true);

    // Loopa för att kontinuerligt läsa av sensorn
    while (1) {
        adc_update(&sensor); // Uppdatera sensorn och kontrollera eventuella tröskelövergångar
        vTaskDelay(pdMS_TO_TICKS(500)); // Fördröjning på 500 ms
    }
}*/
