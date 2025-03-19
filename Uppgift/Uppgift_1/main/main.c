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

/*#include "AnalogLed.h"

void app_main(void) {
    AnalogLed led;
    analogLed_init(&led, 2); //pin 2
    
    analogLed_setBlinking(&led, 4000); // blinkning i sinusvågor är på
    analogLed_setBrightness(&led, 255); // justering av ljuset

    while (1) {
        analogLed_update(&led); 
        vTaskDelay(pdMS_TO_TICKS(10)); // uppdatering period
    }
}*/

/*#include "AnalogLed.h"

void app_main(void) {
    AnalogLed led;
    
    analogLed_init(&led, 2); // pin 2

    set_led_blink_mode(&led, 1, 0); // blink_on till 1 och blink_off till 0 för blinkning
    setAnalogLed(&led, 255); // justering av ljuset


    while (1) {
        analogLed_update(&led);
        vTaskDelay(pdMS_TO_TICKS(10)); // uppdatering period
    }
}*/

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




/*nedan1: Potentiometer som jag har påbörjat*/
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
