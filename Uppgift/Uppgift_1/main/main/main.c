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

/*#include "AnalogLed.h"

AnalogLED_t my_led;

void app_main(void) {
    analog_led_init(&my_led, ANALOG_LED_PIN);

    analog_set_led(&my_led, 512); // Halv ljusstyrka (0-1023)
    analog_sin_wave(&my_led, 4000, 1023); // 1 sekund period, full amplitud
    // Slå på sinusvågorna
    analog_sin_on(&my_led);

    while (1) {
        analog_led_update(&my_led);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}*/


/*nedan1: Potentiometer som fungerar bra*/
#include <stdio.h>
#include "Potentiometer.h"

void app_main(void) {
    MeasurementDevice sensor; // Skapa en instans av enheten.
   
    init(sensor, ADC_CHANNEL_4); // Initiera sensorn med kanal.
    setOnThreshold(sensor, 2000, true, threshold_callback, NULL); // Ange tröskelvärde och callback.
    activateDevice(sensor, true); // Aktivera enheten.

    while (1) {
        update(sensor); // Uppdatera sensorns status.
        printf("Nuvarande värde: %d\n", getValue(sensor)); // Skriv ut det aktuella värdet.
        vTaskDelay(pdMS_TO_TICKS(100)); // Vänta i 100 ms innan nästa iteration.
    }
}
