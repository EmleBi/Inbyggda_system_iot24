#include <stdio.h>
#include "driver/gpio.h"
#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"

/*void app_main(void)
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




//nedan1: Potentiometer som fungerar som det ska
#include <stdio.h>
#include "Potentiometer.h"

void app_main(void) {
    MeasurementDevice sensor;

    init(&sensor, ADC_CHANNEL_4); 
    setOnThreshold(&sensor, 2000, false, threshold_callback, NULL); //tröskelvärde och callback.
    activateDevice(&sensor, true); // Aktiveras enheten.

    while (1) {
        updateMeasurementDevice(&sensor); // Uppdatera sensorns status.
        printf("Nuvarande värde: %d\n", getValue(&sensor)); // Skriv ut det aktuella värdet.
        vTaskDelay(pdMS_TO_TICKS(100)); // Vänta i 100 ms innan nästa iteration.
    }
}

//Nedan kod till NVS configuration

/*#include <stdio.h>
#include "Config.h"

void app_main() {
    Config config;

    // Initiera konfigurationen (initialisering av NVS)
    initConfiguration(&config);

    // Visa initiala värden från NVS
    printf("NVS initialized and values loaded into RAM.\n");
    printf("Device Name: %s\n", getDeviceName(&config));
    printf("Serial Number: %s\n", getSerialNumber(&config));

    // Uppdatera värden
    setDeviceName(&config, "ESP32_DevKit");
    setSerialNumber(&config, "1234567890");

    // Visa uppdaterade värden
    printf("Updated Device Name: %s\n", getDeviceName(&config));
    printf("Updated Serial Number: %s\n", getSerialNumber(&config));
}*/
