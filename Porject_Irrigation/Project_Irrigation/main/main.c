#include <stdio.h>
#include "humidity_sensor.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void) {
    printf("Startar fuktighetssensor...\n");

    init_humidity_sensor();

    while (1) {
        // Läs av fuktighetsvärdet
        float humidity = read_humidity();

        // Skriv ut fuktighetsvärdet
        printf("Fuktighet: %.2f%%\n", humidity);

        // Vänta 1 sekund
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
