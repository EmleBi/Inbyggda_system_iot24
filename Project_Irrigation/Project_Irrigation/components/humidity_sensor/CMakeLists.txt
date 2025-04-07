idf_component_register(SRCS "humidity_sensor.c"
                       INCLUDE_DIRS "include"
                       REQUIRES driver esp_timer esp_adc adc_manager)