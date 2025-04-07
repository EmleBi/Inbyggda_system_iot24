

idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "."
                       REQUIRES adc_manager deep_sleep_manager ergebe_Led humidity_sensor switch temp_sensor)
                       
