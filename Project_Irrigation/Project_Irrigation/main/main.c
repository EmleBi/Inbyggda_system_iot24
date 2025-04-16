//senast fungerande versionen:

/*#include <stdio.h>
#include <math.h> // För logaritm och exponent-beräkningar
#include "ergebe_Led.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "adc_manager.h" // Inkludera ADC-hanteraren
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// GPIO pins
#define HUMIDITY_SENSOR_ADC_PIN 4  // ADC pin for the humidity sensor
#define TEMP_SENSOR_ADC_PIN 6      // ADC pin for the temperature sensor
#define RELAY_PIN GPIO_NUM_2       // GPIO pin for the relay module
#define RED_LED_PIN GPIO_NUM_8     // GPIO pin for Red LED
#define GREEN_LED_PIN GPIO_NUM_9   // GPIO pin for Green LED
#define BLUE_LED_PIN GPIO_NUM_15   // GPIO pin for Blue LED

// Funktion för att konvertera ADC-värde till temperatur (anpassad för NTC-sensor)
float adc_to_temperature(int adc_value) {
    // Sensorparametrar (anpassa baserat på sensorns datablad)
    const float R25 = 10000.0; // NTC-sensorns resistans vid 25 °C (10 kOhm)
    const float Beta = 3950.0; // Beta-värde för sensorn
    const float T0 = 298.15;   // Absolut temperatur vid 25 °C i Kelvin
    const float PullUpResistor = 10000.0; // Pull-up-resistans (10 kOhm)

    // Omvandla ADC-värde till spänning
    float voltage = adc_value * (3.3 / 4095.0);

    // Beräkna NTC-sensorns resistans
    float resistance = (PullUpResistor * voltage) / (3.3 - voltage);

    // Steinhart-Hart-ekvationen för att beräkna temperatur
    float temperature = 1.0 / ((log(resistance / R25) / Beta) + (1.0 / T0)); // Kelvin
    temperature -= 273.15; // Omvandla från Kelvin till Celsius

    // Utskrifter för felsökning
    printf("Voltage calculated: %.3f V\n", voltage);
    printf("Resistance calculated: %.2f Ohms\n", resistance);
    printf("Temperature calculated: %.2f °C\n", temperature);

    return temperature;
}

// Funktion för att styra relä (som styr pumpen)
void control_relay(bool state) {
    gpio_set_level(RELAY_PIN, state ? 1 : 0);
    printf("Relay state: %s\n", state ? "ON (Pump Activated)" : "OFF (Pump Deactivated)");
}

// Funktion för att övervaka jordfuktighet
void monitor_humidity(void) {
    int humidity = read_humidity_value();  // Läs fuktighetssensorns värde
    printf("Humidity raw value: %d\n", humidity);

    if (humidity < 500) { // Torr jord
        printf("Soil is dry. Activating relay...\n");
        control_relay(true);              // Slå på reläet (aktiverar pump)
        ergebe_Led_set_green(true);       // Slå på grön LED
        vTaskDelay(pdMS_TO_TICKS(5000));  // Vänta 5 sekunder medan pumpen kör
        control_relay(false);             // Stäng av reläet (inaktivera pump)
        ergebe_Led_turn_off();            // Stäng av LED
    } else if (humidity < 2000) { // Tillräckligt fuktig jord
        printf("Soil is adequately moist. Relay remains OFF.\n");
        control_relay(false);             // Säkerställ att pumpen är av
    } else { // Mycket blöt jord
        printf("Soil is very wet. No watering needed. Relay remains OFF.\n");
        control_relay(false);             // Säkerställ att pumpen är av
    }
}

// Funktion för att övervaka temperatur
void monitor_temperature(void) {
    int raw_temp = read_temp_value();      // Läs temperatursensorns råvärde
    float temperature = adc_to_temperature(raw_temp);  // Konvertera till temperatur
    printf("Temperature raw value: %d, Temperature in Celsius: %.2f °C\n", raw_temp, temperature);

    if (temperature > 30) { // Hög temperatur
        printf("High temperature detected! Turning on red LED...\n");
        ergebe_Led_set_red(true);        // Slå på röd LED
        control_relay(true);             // Slå på reläet (aktiverar pump)
        printf("High temperature detected! Relay activated.\n");
    } else if (temperature < 10) { // Låg temperatur
        printf("Low temperature detected! Turning on blue LED...\n");
        ergebe_Led_set_blue(true);       // Slå på blå LED
        control_relay(false);            // Säkerställ att reläet är avstängt
    } else {
        ergebe_Led_turn_off();           // Släck LED om temperaturen är normal
        printf("Temperature is normal. LEDs are OFF.\n");
    }
}

// Huvudfunktion för programmet
void app_main(void) {
    printf("Initializing components...\n");

    // Initiera ADC Manager
    init_adc_manager();
    printf("ADC Manager initialized.\n");

    // Initiera LEDs
    ergebe_Led_init();
    printf("LEDs initialized on pins Red=%d, Green=%d, Blue=%d.\n", RED_LED_PIN, GREEN_LED_PIN, BLUE_LED_PIN);

    // Initiera relämodul
    gpio_set_direction(RELAY_PIN, GPIO_MODE_OUTPUT);  // Sätt reläpin som output
    control_relay(false);  // Säkerställ att reläet startar i avstängt läge
    printf("Relay module initialized on GPIO pin %d.\n", RELAY_PIN);

    // Initiera fuktighetssensor
    init_humidity_sensor(HUMIDITY_SENSOR_ADC_PIN);
    printf("Humidity sensor initialized on ADC pin %d.\n", HUMIDITY_SENSOR_ADC_PIN);

    // Initiera temperatursensor
    init_temp_sensor(TEMP_SENSOR_ADC_PIN);
    printf("Temperature sensor initialized on ADC pin %d.\n", TEMP_SENSOR_ADC_PIN);

    while (1) {
        printf("Starting monitoring loop...\n");

        // Övervaka jordfuktighet och temperatur
        monitor_humidity();
        monitor_temperature();

        // Om ingen av sensorerna indikerar att pumpen ska vara på, stängs den av
        if (read_humidity_value() >= 500 && adc_to_temperature(read_temp_value()) <= 30) {
            control_relay(false);  // Säkerställ att reläet förblir av
            printf("Conditions are stable. Pump remains OFF.\n");
        }

        printf("Monitoring complete. Entering deep sleep for 60 seconds...\n");

        // Aktivera djupsömn och ge wake-up-diagnostik
        esp_sleep_enable_timer_wakeup(60000000); // 60 sekunder i mikrosekunder
        printf("Deep sleep timer set. Going to sleep...\n");
        esp_deep_sleep_start();
        printf("System woke up from deep sleep!\n");
    }
}*/

/*#include <stdio.h>
#include <math.h>
#include "ergebe_Led.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "adc_manager.h"
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_mac.h"  // För MAC-relaterade funktioner

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#define TAG "MAIN"

// GPIO pins
#define HUMIDITY_SENSOR_ADC_PIN ADC_CHANNEL_4
#define TEMP_SENSOR_ADC_PIN ADC_CHANNEL_6
#define RELAY_PIN GPIO_NUM_2

// Tröskelvärden
#define DRY_SOIL_THRESHOLD 1500
#define WET_SOIL_THRESHOLD 2500
#define HIGH_TEMP_THRESHOLD 30.0
#define LOW_TEMP_THRESHOLD 10.0

// Tidskonstanter
#define PUMP_RUN_TIME_MS 10000
#define LED_INDICATE_TIME_MS 3000
#define DEEP_SLEEP_TIME_SEC 60

// NTC-parametrar
#define NTC_R25 10000.0
#define NTC_BETA 3950.0
#define NTC_R_BALANCE 10000.0
#define NTC_VCC 3.3

// Anpassad pdMS_TO_TICKS för fall där konfiguration saknas
#define pdMS_TO_TICKS(ms) ((ms) * CONFIG_FREERTOS_HZ / 1000)

float adc_to_temperature(int adc_value) {
    if (adc_value <= 0) {
        ESP_LOGE(TAG, "Ogiltigt ADC-värde: %d", adc_value);
        return -273.15;
    }
    
    float voltage = adc_value * (NTC_VCC / 4095.0);
    if (voltage <= 0.01 || voltage >= NTC_VCC - 0.01) {
        ESP_LOGE(TAG, "Spänning utanför intervall: %.3fV", voltage);
        return -273.15;
    }
    
    float resistance = (voltage * NTC_R_BALANCE) / (NTC_VCC - voltage);
    if (resistance <= 0) {
        ESP_LOGE(TAG, "Ogiltigt resistansvärde: %.2fΩ", resistance);
        return -273.15;
    }
    
    float steinhart = log(resistance / NTC_R25) / NTC_BETA;
    steinhart += 1.0 / 298.15;  // 25°C i Kelvin
    steinhart = 1.0 / steinhart;
    float temperature = steinhart - 273.15;
    
    ESP_LOGI(TAG, "ADC: %d, Spänning: %.3fV, Resistans: %.2fΩ, Temp: %.2f°C", 
           adc_value, voltage, resistance, temperature);
    return temperature;
}

void control_relay(bool state) {
    gpio_set_level(RELAY_PIN, state ? 1 : 0);
    ESP_LOGI(TAG, "Relä %s", state ? "PÅ" : "AV");
}

void handle_watering(int humidity) {
    ESP_LOGI(TAG, "Aktuell fuktighet: %d", humidity);
    
    if (humidity < DRY_SOIL_THRESHOLD) {
        ESP_LOGI(TAG, "Jord för torr - aktiverar pump");
        ergebe_Led_set_red(true);
        control_relay(true);
        vTaskDelay(pdMS_TO_TICKS(PUMP_RUN_TIME_MS));
        control_relay(false);
        ergebe_Led_set_red(false);
        
        ergebe_Led_set_green(true);
        vTaskDelay(pdMS_TO_TICKS(LED_INDICATE_TIME_MS));
        ergebe_Led_set_green(false);
    } else if (humidity > WET_SOIL_THRESHOLD) {
        ESP_LOGI(TAG, "Jorden är tillräckligt fuktig");
    } else {
        ESP_LOGI(TAG, "Fuktnivå är adekvat");
    }
}

void handle_temperature(float temperature) {
    ESP_LOGI(TAG, "Aktuell temperatur: %.2f°C", temperature);
    
    if (temperature > HIGH_TEMP_THRESHOLD) {
        ESP_LOGI(TAG, "Hög temperatur upptäckt");
        ergebe_Led_set_red(true);
        vTaskDelay(pdMS_TO_TICKS(LED_INDICATE_TIME_MS));
        ergebe_Led_set_red(false);
    } else if (temperature < LOW_TEMP_THRESHOLD) {
        ESP_LOGI(TAG, "Låg temperatur upptäckt");
        ergebe_Led_set_blue(true);
        vTaskDelay(pdMS_TO_TICKS(LED_INDICATE_TIME_MS));
        ergebe_Led_set_blue(false);
    } else {
        ESP_LOGI(TAG, "Normal temperatur");
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "Startar systeminitialisering...");
    
    // Initiera komponenter
    init_adc_manager();
    ergebe_Led_init();
    
    // Initiera reläpin
    gpio_reset_pin(RELAY_PIN);
    gpio_set_direction(RELAY_PIN, GPIO_MODE_OUTPUT);
    control_relay(false);  // Se till att pumpen är av från början
    ESP_LOGI(TAG, "Relä initialiserat på GPIO %d", RELAY_PIN);
    
    // Initiera sensorer
    init_humidity_sensor(HUMIDITY_SENSOR_ADC_PIN);
    init_temp_sensor(TEMP_SENSOR_ADC_PIN);
    ESP_LOGI(TAG, "Alla komponenter har initialiserats korrekt");
    
    ESP_LOGI(TAG, "Systeminitialisering klar");

    while (1) {
        ESP_LOGI(TAG, "Startar övervakningscykel...");
        
        // Läs fuktighet och kontrollera bevattning
        int humidity = read_humidity_value();
        handle_watering(humidity);
        
        // Läs temperatur
        int raw_temp = read_temp_value();
        float temperature = adc_to_temperature(raw_temp);
        handle_temperature(temperature);
        
        // Förbered för deep sleep
        ESP_LOGI(TAG, "Går in i deep sleep i %d sekunder...", DEEP_SLEEP_TIME_SEC);
        esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_SEC * 1000000);
        
        // Stäng av alla komponenter innan sleep
        ergebe_Led_turn_off();
        control_relay(false);
        
        // Liten fördröjning för att loggar ska hinna skrivas ut
        vTaskDelay(pdMS_TO_TICKS(100));
        
        esp_deep_sleep_start();
    }
}*/

//ett nytt försök som fungerade sist med fel
/*#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "adc_manager.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"

#define DEEP_SLEEP_TIME_US (60 * 1000000)  // 1 minut
#define LED_DISPLAY_TIME_MS 20000          // 20 sekunder
#define PUMP_MIN_RUN_TIME_MS 5000          // Minsta pumpkörningstid

static const char *TAG = "Main";

void enter_deep_sleep(void) {
    ESP_LOGI(TAG, "Preparing for deep sleep...");
    
    set_led_state(LED_OFF);
    switch_set(false);
    adc_manager_deinit();
    
    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_US);
    ESP_LOGI(TAG, "Entering deep sleep for %d seconds", DEEP_SLEEP_TIME_US / 1000000);
    esp_deep_sleep_start();
}

void app_main(void) {
    ESP_LOGI(TAG, "System startup...");
    
    adc_manager_init();
    humidity_sensor_init();
    temp_sensor_init();
    ergebe_led_init();
    switch_init();
    
    ESP_LOGI(TAG, "All components initialized");
    
    while(1) {
        int humidity = read_humidity();
        bool soil_dry = is_soil_dry(humidity);
        
        ESP_LOGI(TAG, "Soil status - Humidity: %d, %s", 
                humidity, soil_dry ? "DRY (needs water)" : "OK");
        
        if(soil_dry) {
            switch_set(true);
            set_led_state(LED_GREEN);
            vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
            
            do {
                vTaskDelay(pdMS_TO_TICKS(1000));
                humidity = read_humidity();
                soil_dry = is_soil_dry(humidity);
                ESP_LOGI(TAG, "Watering in progress - Current humidity: %d", humidity);
            } while(soil_dry);
            
            switch_set(false);
            ESP_LOGI(TAG, "Pump deactivated - watering complete");
        }
        
        float temperature = read_temperature();
        int temp_status = check_temp_status(temperature);
        
        ESP_LOGI(TAG, "Temperature: %.2f°C", temperature);
        
        if(temp_status == 1) {
            set_led_state(LED_RED);
            ESP_LOGW(TAG, "High temperature warning!");
        } 
        else if(temp_status == -1) {
            set_led_state(LED_BLUE);
            ESP_LOGW(TAG, "Low temperature warning!");
        }
        
        vTaskDelay(pdMS_TO_TICKS(LED_DISPLAY_TIME_MS));
        enter_deep_sleep();
    }
}*/

//nytt försök 2
/*#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "adc_manager.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "switch.h"
#include "deep_sleep_manager.h"

// Konfigurationer för fall där sdkconfig inte laddas
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#define DEEP_SLEEP_TIME_US (60 * 1000000) // 1 minut
#define LED_DISPLAY_TIME_MS 20000         // 20 sekunder
#define PUMP_MIN_RUN_TIME_MS 5000         // Minsta pumpkörningstid

static const char *TAG = "MAIN"; // Standarddefinition av TAG för loggning

void app_main(void) {
    ESP_LOGI(TAG, "System startup..."); // Startmeddelande med korrekt TAG

    // Initialisera komponenter
    adc_manager_init();
    humidity_sensor_init();
    temp_sensor_init();
    switch_init();
    deep_sleep_manager_init(DEEP_SLEEP_TIME_US);

    // Huvudlogik i evig loop
    while (1) {
        // Kontrollera fuktighet
        int humidity = read_humidity();
        bool soil_dry = is_soil_dry(humidity);

        ESP_LOGI(TAG, "Humidity: %d - Soil %s", humidity, soil_dry ? "DRY" : "OK");

        if (soil_dry) {
            ESP_LOGI(TAG, "Activating pump...");
            switch_set(true);
            vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
            ESP_LOGI(TAG, "Deactivating pump...");
            switch_set(false);
        }

        // Kontrollera temperatur
        float temperature = read_temperature();
        int temp_status = check_temp_status(temperature);

        if (temp_status == 1) {
            ESP_LOGW(TAG, "High temperature detected: %.2f°C", temperature);
        } else if (temp_status == -1) {
            ESP_LOGW(TAG, "Low temperature detected: %.2f°C", temperature);
        } else {
            ESP_LOGI(TAG, "Temperature normal: %.2f°C", temperature);
        }

        // Vänta och gå i viloläge
        ESP_LOGI(TAG, "Entering deep sleep mode...");
        vTaskDelay(pdMS_TO_TICKS(LED_DISPLAY_TIME_MS));
        deep_sleep_manager_enter();
    }
}*/

//några justeringar...

/*#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "adc_manager.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "switch.h"
#include "deep_sleep_manager.h"
#include "ergebe_Led.h"

// Konfigurationer
#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

#ifndef CONFIG_LOG_MAXIMUM_LEVEL
#define CONFIG_LOG_MAXIMUM_LEVEL ESP_LOG_INFO
#endif

#define DEEP_SLEEP_TIME_US (60 * 1000000) // 1 minut
#define LED_DISPLAY_TIME_MS 20000 // 20 sekunder
#define PUMP_MIN_RUN_TIME_MS 5000 // 5 sekunder
#define POST_PUMP_VERIFY_DELAY_MS 2000 // 2 sekunder
#define GREEN_LED_POST_PUMP_MS 5000 // 5 sekunder

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "System starting up...");

    // Initialisera alla komponenter
    adc_manager_init();
    humidity_sensor_init();
    temp_sensor_init();
    switch_init();
    ergebe_led_init();
    deep_sleep_manager_init(DEEP_SLEEP_TIME_US);

    ESP_LOGI(TAG, "All components initialized, entering main loop");

    while (1) {
        ESP_LOGI(TAG, "=== New control cycle started ===");

        // Läs temperatur först (används för dynamiskt fuktighetströskel)
        float temperature = read_temperature();
        int temp_status = check_temp_status(temperature);

        // Hantera temperaturstatus och LED-indikatorer
        if (temp_status == 1) { // För hög temperatur
            ESP_LOGW(TAG, "High temperature condition (%.1f°C)", temperature);
            set_led_state(LED_RED);
            
            // Ytterligare fuktighetskontroll vid hög temp
            int humidity = read_humidity();
            if (is_soil_dry(humidity, temperature)) {
                ESP_LOGI(TAG, "High temp + dry soil - activating pump");
                set_led_state(LED_GREEN);
                switch_set(true);
                vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
                switch_set(false);
                
                // Verifiera fuktighet efter pumpning
                vTaskDelay(pdMS_TO_TICKS(POST_PUMP_VERIFY_DELAY_MS));
                humidity = read_humidity();
                if (!is_soil_dry(humidity, temperature)) {
                    ESP_LOGI(TAG, "Soil moisture normalized after watering");
                    set_led_state(LED_GREEN);
                    vTaskDelay(pdMS_TO_TICKS(GREEN_LED_POST_PUMP_MS));
                }
            }
            set_led_state(LED_OFF);
        } 
        else if (temp_status == -1) { // För låg temperatur
            ESP_LOGW(TAG, "Low temperature condition (%.1f°C)", temperature);
            set_led_state(LED_BLUE);
            vTaskDelay(pdMS_TO_TICKS(LED_DISPLAY_TIME_MS));
            set_led_state(LED_OFF);
        } 
        else { // Normal temperatur
            ESP_LOGI(TAG, "Normal temperature (%.1f°C)", temperature);
            
            // Kontrollera fuktighet vid normal temp
            int humidity = read_humidity();
            if (is_soil_dry(humidity, temperature)) {
                ESP_LOGI(TAG, "Dry soil detected - activating pump");
                set_led_state(LED_GREEN);
                switch_set(true);
                vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
                switch_set(false);
                
                // Verifiera fuktighet efter pumpning
                vTaskDelay(pdMS_TO_TICKS(POST_PUMP_VERIFY_DELAY_MS));
                humidity = read_humidity();
                if (!is_soil_dry(humidity, temperature)) {
                    ESP_LOGI(TAG, "Soil moisture normalized after watering");
                    set_led_state(LED_GREEN);
                    vTaskDelay(pdMS_TO_TICKS(GREEN_LED_POST_PUMP_MS));
                    set_led_state(LED_OFF);
                }
            }
        }

        ESP_LOGI(TAG, "Control cycle completed, entering deep sleep");
        deep_sleep_manager_enter();
    }
}*/

//ej fungerande med alla detaljer tillsammans:
/*#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "adc_manager.h"
#include "humidity_sensor.h"
#include "temp_sensor.h"
#include "switch.h"
#include "deep_sleep_manager.h"
#include "ergebe_Led.h"

#define DEEP_SLEEP_TIME_US (60 * 1000000) // 1 minut
#define LED_DISPLAY_TIME_MS 20000 // 20 sekunder
#define PUMP_MIN_RUN_TIME_MS 5000 // 5 sekunder
#define POST_PUMP_VERIFY_DELAY_MS 2000 // 2 sekunder
#define GREEN_LED_POST_PUMP_MS 5000 // 5 sekunder

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "System starting up...");

    // Initialisera alla komponenter
    adc_manager_init();
    humidity_sensor_init();
    temp_sensor_init();
    switch_init();
    ergebe_led_init();
    deep_sleep_manager_init(DEEP_SLEEP_TIME_US);

    ESP_LOGI(TAG, "All components initialized, entering main loop");

    while (1) {
        ESP_LOGI(TAG, "=== New control cycle started ===");

        // Läs temperatur först (används för dynamiskt fuktighetströskel)
        float temperature = read_temperature();
        int temp_status = check_temp_status(temperature);

        // Hantera temperaturstatus och LED-indikatorer
        if (temp_status == 1) { // För hög temperatur
            ESP_LOGW(TAG, "High temperature condition (%.1f°C)", temperature);
            set_led_state(LED_RED);

            // Ytterligare fuktighetskontroll vid hög temp
            int humidity = read_humidity();
            if (is_soil_dry(humidity, temperature)) {
                ESP_LOGI(TAG, "High temp + dry soil - activating pump");
                set_led_state(LED_GREEN);
                switch_set(true);
                vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
                switch_set(false);

                // Verifiera fuktighet efter pumpning
                vTaskDelay(pdMS_TO_TICKS(POST_PUMP_VERIFY_DELAY_MS));
                humidity = read_humidity();
                if (!is_soil_dry(humidity, temperature)) {
                    ESP_LOGI(TAG, "Soil moisture normalized after watering");
                    set_led_state(LED_GREEN);
                    vTaskDelay(pdMS_TO_TICKS(GREEN_LED_POST_PUMP_MS));
                }
            }
            set_led_state(LED_OFF);
        } 
        else if (temp_status == -1) { // För låg temperatur
            ESP_LOGW(TAG, "Low temperature condition (%.1f°C)", temperature);
            set_led_state(LED_BLUE);
            vTaskDelay(pdMS_TO_TICKS(LED_DISPLAY_TIME_MS));
            set_led_state(LED_OFF);
        } 
        else { // Normal temperatur
            ESP_LOGI(TAG, "Normal temperature (%.1f°C)", temperature);
            
            // Kontrollera fuktighet vid normal temp
            int humidity = read_humidity();
            if (is_soil_dry(humidity, temperature)) {
                ESP_LOGI(TAG, "Dry soil detected - activating pump");
                set_led_state(LED_GREEN);
                switch_set(true);
                vTaskDelay(pdMS_TO_TICKS(PUMP_MIN_RUN_TIME_MS));
                switch_set(false);

                // Verifiera fuktighet efter pumpning
                vTaskDelay(pdMS_TO_TICKS(POST_PUMP_VERIFY_DELAY_MS));
                humidity = read_humidity();
                if (!is_soil_dry(humidity, temperature)) {
                    ESP_LOGI(TAG, "Soil moisture normalized after watering");
                    set_led_state(LED_GREEN);
                    vTaskDelay(pdMS_TO_TICKS(GREEN_LED_POST_PUMP_MS));
                    set_led_state(LED_OFF);
                }
            }
        }

        ESP_LOGI(TAG, "Control cycle completed, entering deep sleep");
        deep_sleep_manager_enter();
    }
}*/

//Förenklade version:
/*#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "ergebe_led.h"
#include "humidity_sensor.h"
#include "switch.h"

// Konfigurationer
#define HUMIDITY_THRESHOLD      30    // Tröskelvärde för fuktighet
#define PUMP_RUN_TIME           20000 // Bevattningstid (millisekunder)
#define POST_WATERING_DELAY     20000 // Fördröjning efter bevattning (millisekunder)
#define DEEP_SLEEP_DURATION     60000000 // Deep-sleep varaktighet (mikrosekunder)

static const char *TAG = "SmartWatering";

void prepare_for_deep_sleep() {
    turn_off_led();
    deactivate_pump();
    ESP_LOGI(TAG, "System entering deep sleep.");
    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_DURATION);
    esp_deep_sleep_start();
}

void app_main() {
    ESP_LOGI(TAG, "Starting Smart Irrigation System");

    // Initiera komponenter
    rgb_led_init();
    humidity_sensor_init();
    switch_init();

    while (1) {
        // Läs av fuktighetsnivån
        uint8_t humidity = get_humidity_level();
        ESP_LOGI(TAG, "Current soil moisture: %d%%", humidity);

        if (humidity < HUMIDITY_THRESHOLD) { // Torr jord
            ESP_LOGI(TAG, "Soil is dry. Activating pump...");
            set_led_red(); // Indikera att det är torrt
            vTaskDelay(pdMS_TO_TICKS(5000)); // Fördröjning för rött LED-ljus

            activate_pump(true);
            set_led_green(); // Indikera att bevattning pågår
            vTaskDelay(pdMS_TO_TICKS(PUMP_RUN_TIME)); // Pump körs

            deactivate_pump();
            ESP_LOGI(TAG, "Pump deactivated. Soil moisture restored.");
            vTaskDelay(pdMS_TO_TICKS(POST_WATERING_DELAY)); // Fördröjning efter bevattning
        } else {
            ESP_LOGI(TAG, "Soil moisture adequate. No watering needed.");
            set_led_blue(); // Indikera att fuktigheten är tillräcklig
            vTaskDelay(pdMS_TO_TICKS(2000)); // Blå LED lyser i 2 sekunder
        }

        // Förbered för deep-sleep
        prepare_for_deep_sleep();
    }
}*/

//fungerar men inte rätt
/*#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define MIN_SLEEP_DELAY_MS 30000  // Minst 30 sekunders väntan innan deep sleep
#define DEEP_SLEEP_TIME_US 60000000  // 60 sekunders deep sleep

// Pin-definitioner
#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

// Tidskonstanter (ms)
#define PUMP_TIME 20000     // 20 sekunders pumpning
#define RED_LED_TIME 10000  // 10 sekunders röd LED
#define POST_ACTION_DELAY 5000  // 5 sekunders fördröjning efter pumpning

void app_main(void) {
    // Initiera alla komponenter
    ESP_LOGI(MAIN_TAG, "Starting watering system...");
    
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init();

    // Huvudlogik
    if (humidity_sensor_is_dry()) {
        ESP_LOGI(MAIN_TAG, "Soil is dry - watering needed");
        
        // Visa röd LED i 10 sekunder
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME));
        
        // Starta pumpen och visa grön LED
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME));
        
        // Stäng av pumpen
        switch_off();
        
        // Visa grön LED i 5 sekunder till
        vTaskDelay(pdMS_TO_TICKS(POST_ACTION_DELAY));
    } else {
        ESP_LOGI(MAIN_TAG, "Soil moisture is sufficient");
        ergebe_Led_set(LED_BLUE);
    }
    
    // Vänta minst 30 sekunder totalt innan deep sleep
    uint32_t elapsed_time = 
        (humidity_sensor_is_dry() ? (RED_LED_TIME + PUMP_TIME + POST_ACTION_DELAY) : 0);
    
    if (elapsed_time < MIN_SLEEP_DELAY_MS) {
        uint32_t remaining_delay = MIN_SLEEP_DELAY_MS - elapsed_time;
        ESP_LOGI(MAIN_TAG, "Waiting additional %" PRIu32 " ms before deep sleep", remaining_delay);
        vTaskDelay(pdMS_TO_TICKS(remaining_delay));
    }
    
    // Förbered för deep sleep
    ergebe_Led_set(LED_OFF);
    ESP_LOGI(MAIN_TAG, "Preparing for deep sleep");
    deep_sleep_enter(DEEP_SLEEP_TIME_US);
}*/

//fungerar men inte rätt

/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US (60 * 1000000)  // 60 sekunder

// Pin-definitioner
#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

// Tidskonstanter (ms)
#define PUMP_TIME 20000      // 20 sekunder
#define RED_LED_TIME 10000   // 10 sekunder
#define POST_ACTION_DELAY 5000  // 5 sekunder
#define MIN_SLEEP_DELAY 30000   // Minst 30 sekunder aktivitet

void app_main(void) {
    // Initiera alla komponenter
    ESP_LOGI(MAIN_TAG, "Startar bevattningssystem...");
    
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init();

    // Visa blå LED när systemet är aktivt
    ergebe_Led_set(LED_BLUE);
    vTaskDelay(pdMS_TO_TICKS(2000));  // Visa status i 2 sekunder

    // Kontrollera fuktighet
    if (humidity_sensor_is_dry()) {
        ESP_LOGI(MAIN_TAG, "Jorden är torr - behöver vattnas");
        
        // 1. Visa röd LED i 10 sekunder
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME));
        
        // 2. Starta pumpen och visa grön LED
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME));
        
        // 3. Stäng av pumpen
        switch_off();
        
        // 4. Visa grön LED i 5 sekunder till
        vTaskDelay(pdMS_TO_TICKS(POST_ACTION_DELAY));
    } else {
        ESP_LOGI(MAIN_TAG, "Jorden har tillräcklig fuktighet");
        ergebe_Led_set(LED_BLUE);
    }
    
    // Förbered för deep sleep
    ergebe_Led_set(LED_OFF);
    ESP_LOGI(MAIN_TAG, "Förbereder för deep sleep");
    vTaskDelay(pdMS_TO_TICKS(1000));  // Kort fördröjning innan deep sleep
    
    // Gå in i deep sleep
    deep_sleep_enter(DEEP_SLEEP_TIME_US);
}*/

/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US (60 * 1000000)  // 60 sekunder

// Pin-definitioner
#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

// Tidskonstanter (ms)
#define PUMP_TIME 20000       // 20 sekunder
#define RED_LED_TIME 10000    // 10 sekunder
#define POST_ACTION_DELAY 5000 // 5 sekunder
#define SYSTEM_DELAY 2000     // 2 sekunder

void prepare_for_deep_sleep(void) {
    ESP_LOGI(MAIN_TAG, "Förbereder för deep sleep...");
    
    // 1. Stäng av pumpen om den är på
    if(switch_is_on()) {
        switch_off();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
    // 2. Stäng av LED:er
    ergebe_Led_set(LED_OFF);
    
    // 3. Stäng av sensorer
    humidity_sensor_deinit();
    
    // 4. Deinitiera alla komponenter
    ergebe_Led_deinit();
    switch_deinit();
    
    // 5. Kort fördröjning för att säkerställa allt stängs av
    vTaskDelay(pdMS_TO_TICKS(200));
    
    ESP_LOGI(MAIN_TAG, "Alla komponenter avstängda");
}

void app_main(void) {
    // Initiera alla komponenter
    ESP_LOGI(MAIN_TAG, "============ Systemstart ============");
    
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init();

    // Startsekvens
    ergebe_Led_set(LED_BLUE);
    ESP_LOGI(MAIN_TAG, "System initierat, kontrollerar fuktighet...");
    vTaskDelay(pdMS_TO_TICKS(SYSTEM_DELAY));

    // Huvudlogik
    if (humidity_sensor_is_dry()) {
        ESP_LOGI(MAIN_TAG, "Jorden är torr - behöver vattnas");
        
        // Visa röd LED i 10 sekunder
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME));
        
        // Aktivera pumpen i 20 sekunder
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME));
        
        // Stäng av pumpen
        switch_off();
        
        // Bekräftelse i 5 sekunder
        vTaskDelay(pdMS_TO_TICKS(POST_ACTION_DELAY));
    } else {
        ESP_LOGI(MAIN_TAG, "Jorden har tillräcklig fuktighet");
    }
    
    // Förbered och aktivera deep sleep
    prepare_for_deep_sleep();
    ESP_LOGI(MAIN_TAG, "Aktiverar deep sleep...");
    deep_sleep_enter(DEEP_SLEEP_TIME_US);
}*/

/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "esp_mac.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US ((uint64_t)(60 * 1000000))  // Explicit typkonvertering
#define PUMP_TIME_MS 20000
#define RED_LED_TIME_MS 10000
#define POST_ACTION_DELAY_MS 5000

#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

void prepare_for_deep_sleep(void) {
    if (switch_is_on()) switch_off();
    ergebe_Led_set(LED_OFF);
    humidity_sensor_deinit();
    ergebe_Led_deinit();
    switch_deinit();
}

void test_deep_sleep(void) {  // Debug funktion
    ESP_LOGI(MAIN_TAG, "Testing deep sleep...");
    deep_sleep_init((uint64_t)(30 * 1000000));  // Test med 30 sekunder
    deep_sleep_enter();                         // Försök aktivera
}

void app_main(void) {
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init(DEEP_SLEEP_TIME_US);  // Initiera deep sleep

    ergebe_Led_set(LED_BLUE);
    vTaskDelay(pdMS_TO_TICKS(1000));

    if (humidity_sensor_is_dry()) {
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME_MS));
        
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME_MS));
        
        switch_off();
        vTaskDelay(pdMS_TO_TICKS(POST_ACTION_DELAY_MS));
    } else {
        ergebe_Led_set(LED_BLUE);
    }

    prepare_for_deep_sleep();
    deep_sleep_enter();
}*/

//kod med extra GPIO-pins för deep-sleep:
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "esp_mac.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US ((uint64_t)(60 * 1000000))  // 60 seconds
#define PUMP_TIME_MS 20000
#define RED_LED_TIME_MS 10000
#define POST_ACTION_DELAY_MS 10000

#define RED_PIN GPIO_NUM_9
#define GREEN_PIN GPIO_NUM_15
#define BLUE_PIN GPIO_NUM_8
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

RTC_DATA_ATTR static int wakeup_count = 0;

// Prepare components for deep sleep
void prepare_for_deep_sleep(void) {
    if (switch_is_on()) switch_off();  // Turn off the pump if it's on
    ergebe_Led_set(LED_OFF);           // Turn off LEDs
    humidity_sensor_deinit();          // Deinitialize humidity sensor
    ergebe_Led_deinit();               // Deinitialize LEDs
    switch_deinit();                   // Deinitialize the relay

    gpio_set_pull_mode(RED_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GREEN_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BLUE_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(RELAY_PIN, GPIO_PULLDOWN_ONLY);
    gpio_reset_pin(HUMIDITY_ADC_CHANNEL);  // Disconnect ADC GPIO

    ESP_LOGI(MAIN_TAG, "All components have been shut down and are ready for deep sleep.");
}

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "System is starting, wakeup count: %d", wakeup_count);

    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    // deep_sleep_init(DEEP_SLEEP_TIME_US);

    // Read humidity value
    int humidity = humidity_sensor_read();
    ESP_LOGI(MAIN_TAG, "Humidity value: %d%%", humidity);

    if (humidity < HUMIDITY_THRESHOLD) {
        ESP_LOGI(MAIN_TAG, "Soil is dry. Activating red LED.");
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME_MS));

        ESP_LOGI(MAIN_TAG, "Starting pump.");
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME_MS));

        ESP_LOGI(MAIN_TAG, "Stopping pump.");
        switch_off();
        ergebe_Led_set(LED_BLUE);
    } else {
        ESP_LOGI(MAIN_TAG, "Soil moisture is sufficient. Activating blue LED.");
        ergebe_Led_set(LED_BLUE);
    }

    // prepare_for_deep_sleep();
    // ESP_LOGI(MAIN_TAG, "Entering deep sleep...");
    // wakeup_count++;
    // deep_sleep_enter();
}

/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "esp_mac.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US ((uint64_t)(60 * 1000000))  // 60 seconds
#define PUMP_TIME_MS 20000
#define RED_LED_TIME_MS 20000
#define POST_ACTION_DELAY_MS 5000

#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

RTC_DATA_ATTR static int wakeup_count = 0;

// Förbered alla komponenter för djupsömn
void prepare_for_deep_sleep(void) {
    if (switch_is_on()) switch_off();  // Stäng av pumpen om den är på
    ergebe_Led_set(LED_OFF);           // Stäng av LED
    humidity_sensor_deinit();          // Deinitiera fuktighetssensorn
    ergebe_Led_deinit();               // Deinitiera LED
    switch_deinit();                   // Deinitiera reläet

    // Sätt GPIO i lågenergiläge
    gpio_set_pull_mode(RED_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GREEN_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(BLUE_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(RELAY_PIN, GPIO_PULLDOWN_ONLY);
    gpio_reset_pin(HUMIDITY_ADC_CHANNEL);  // Koppla bort ADC GPIO

    ESP_LOGI(MAIN_TAG, "All components have been shut down and are ready for deep sleep.");
}

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "System is starting, wakeup count: %d", wakeup_count);

    // Initialisera komponenter
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init(DEEP_SLEEP_TIME_US);

    // Läs fuktighetssensorn
    int humidity = humidity_sensor_read();
    ESP_LOGI(MAIN_TAG, "Humidity value: %d%%", humidity);

    if (humidity < HUMIDITY_THRESHOLD) {
        ESP_LOGI(MAIN_TAG, "Soil is dry. Activating red LED.");
        ergebe_Led_set(LED_RED);  // Aktivera röda LED
        
        // Logga för att bekräfta LED-status
        ESP_LOGI(MAIN_TAG, "Red LED should now be active.");

        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME_MS));  // Vänta medan röd LED lyser

        ESP_LOGI(MAIN_TAG, "Starting pump.");
        switch_on();
        ergebe_Led_set(LED_GREEN);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME_MS));

        ESP_LOGI(MAIN_TAG, "Stopping pump.");
        switch_off();
        ergebe_Led_set(LED_BLUE);
    } else {
        ESP_LOGI(MAIN_TAG, "Soil moisture is sufficient. Activating blue LED.");
        ergebe_Led_set(LED_BLUE);
    }

    prepare_for_deep_sleep();
    ESP_LOGI(MAIN_TAG, "Entering deep sleep...");
    wakeup_count++;
    deep_sleep_enter();
}*/


//ds-kod

/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"  // Uppdaterad include-sökväg
// #include "esp_mac.h"  // Endast inkludera om MAC-adressbehandling behövs

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US ((uint64_t)(60 * 1000000))
#define PUMP_TIME_MS 20000
#define RED_LED_TIME_MS 5000
#define POST_ACTION_DELAY_MS 5000

// Pin definitions
#define RED_PIN GPIO_NUM_8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

RTC_DATA_ATTR static int wakeup_count = 0;

void prepare_for_deep_sleep(void) {
    ESP_LOGI(MAIN_TAG, "Preparing for deep sleep...");
    
    if (switch_is_on()) {
        ESP_LOGI(MAIN_TAG, "Turning off pump before sleep");
        switch_off();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    ergebe_Led_set(LED_OFF);
    humidity_sensor_deinit();
    ergebe_Led_deinit();
    switch_deinit();
    
    const gpio_num_t used_pins[] = {RED_PIN, GREEN_PIN, BLUE_PIN, RELAY_PIN};
    for (int i = 0; i < sizeof(used_pins)/sizeof(used_pins[0]); i++) {
        gpio_reset_pin(used_pins[i]);
        gpio_sleep_set_pull_mode(used_pins[i], GPIO_PULLDOWN_ONLY);
    }
    
    ESP_LOGI(MAIN_TAG, "All components prepared for deep sleep");
}

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "System starting, wakeup count: %d", wakeup_count);
    
    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init(DEEP_SLEEP_TIME_US);
    
    int humidity = humidity_sensor_read();
    ESP_LOGI(MAIN_TAG, "Current soil moisture: %d%%", humidity);
    
    if (humidity_sensor_is_dry()) {
        ESP_LOGI(MAIN_TAG, "Soil is dry - activating watering sequence");
        
        ergebe_Led_set(LED_RED);
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME_MS));
        
        ergebe_Led_set(LED_GREEN);
        switch_on();
        ESP_LOGI(MAIN_TAG, "Pump activated for %d ms", PUMP_TIME_MS);
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME_MS));
        
        switch_off();
        ESP_LOGI(MAIN_TAG, "Pump deactivated");
        
        ergebe_Led_set(LED_BLUE);
    } else {
        ESP_LOGI(MAIN_TAG, "Soil moisture is sufficient - no watering needed");
        ergebe_Led_set(LED_BLUE);
    }
    
    vTaskDelay(pdMS_TO_TICKS(POST_ACTION_DELAY_MS));
    
    prepare_for_deep_sleep();
    wakeup_count++;
    ESP_LOGI(MAIN_TAG, "Entering deep sleep...");
    deep_sleep_enter();
}*/

//nytt försök med ext1 -funkton:
/*#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_mac.h"

#include "humidity_sensor.h"
#include "ergebe_Led.h"
#include "switch.h"
#include "deep_sleep_manager.h"

#define MAIN_TAG "Main"
#define DEEP_SLEEP_TIME_US ((uint64_t)(60 * 1000000))  // 60 seconds
#define PUMP_TIME_MS 20000
#define RED_LED_TIME_MS 10000

#define RED_PIN GPIO_NUM_12  // Använd GPIO12 istället för GPIO8
#define GREEN_PIN GPIO_NUM_9
#define BLUE_PIN GPIO_NUM_15
#define RELAY_PIN GPIO_NUM_2
#define HUMIDITY_ADC_CHANNEL ADC_CHANNEL_4

RTC_DATA_ATTR static int wakeup_count = 0;

void setup_ext1_wakeup(void) {
    // Konfigurera GPIO-mask för EXT1 wakeup (användends RED_PIN, GREEN_PIN och BLUE_PIN)
    uint64_t ext1_wakeup_pins = (1ULL << RED_PIN) | (1ULL << GREEN_PIN) | (1ULL << BLUE_PIN);
    esp_sleep_enable_ext1_wakeup(ext1_wakeup_pins, ESP_EXT1_WAKEUP_ANY_LOW);  // Väcker systemet när någon är LOW
    ESP_LOGI(MAIN_TAG, "EXT1 wakeup configured for GPIO pins: RED=%d, GREEN=%d, BLUE=%d", RED_PIN, GREEN_PIN, BLUE_PIN);
}

void prepare_for_deep_sleep(void) {
    if (switch_is_on()) switch_off();  // Stäng av pumpen om den är på
    ergebe_Led_set(LED_OFF);           // Stäng av LED
    humidity_sensor_deinit();          // Deinitiera fuktighetssensorn
    ergebe_Led_deinit();               // Deinitiera LED
    switch_deinit();                   // Deinitiera reläet

    // Sätt GPIO i lågenergiläge med pull-up
    gpio_set_pull_mode(RED_PIN, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GREEN_PIN, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(BLUE_PIN, GPIO_PULLUP_ONLY);

    // Isolera RTC GPIO
    rtc_gpio_isolate(RED_PIN);
    rtc_gpio_isolate(GREEN_PIN);
    rtc_gpio_isolate(BLUE_PIN);
    rtc_gpio_isolate(RELAY_PIN);

    ESP_LOGI(MAIN_TAG, "All components have been shut down and are ready for deep sleep.");
}

void app_main(void) {
    ESP_LOGI(MAIN_TAG, "System is starting, wakeup count: %d", wakeup_count);

    ergebe_Led_init(RED_PIN, GREEN_PIN, BLUE_PIN);
    switch_init(RELAY_PIN);
    humidity_sensor_init(HUMIDITY_ADC_CHANNEL);
    deep_sleep_init(DEEP_SLEEP_TIME_US);

    // Konfigurera EXT1 wakeup
    setup_ext1_wakeup();

    // Läs fuktighetssensorn
    int humidity = humidity_sensor_read();
    ESP_LOGI(MAIN_TAG, "Humidity value: %d%%", humidity);

    if (humidity < HUMIDITY_THRESHOLD) {
        ESP_LOGI(MAIN_TAG, "Soil is dry. Activating red LED.");
        ergebe_Led_set(LED_RED);  // Tänd röd lampa
        vTaskDelay(pdMS_TO_TICKS(RED_LED_TIME_MS));  // Vänta i 10 sekunder

        ESP_LOGI(MAIN_TAG, "Starting pump and activating green LED.");
        switch_on();  // Starta pumpen
        ergebe_Led_set(LED_GREEN);  // Tänd grön lampa
        vTaskDelay(pdMS_TO_TICKS(PUMP_TIME_MS));

        ESP_LOGI(MAIN_TAG, "Stopping pump.");
        switch_off();  // Stäng av pumpen
        ergebe_Led_set(LED_BLUE);  // Tänd blå lampa efter att pumpen stängs av
    } else {
        ESP_LOGI(MAIN_TAG, "Soil moisture is sufficient. Activating blue LED.");
        ergebe_Led_set(LED_BLUE);  // Tänd blå lampa direkt om fukten är tillräcklig
    }

    prepare_for_deep_sleep();
    ESP_LOGI(MAIN_TAG, "Entering deep sleep...");
    wakeup_count++;
    deep_sleep_enter();
}*/
