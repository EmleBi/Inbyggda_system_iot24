idf_component_register(SRCS "deep_sleep_manager.c"
                    INCLUDE_DIRS "include"
                    REQUIRES ergebe_Led humidity_sensor temp_sensor adc_manager switch)

