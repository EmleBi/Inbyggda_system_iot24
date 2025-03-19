idf_component_register(SRCS "Config.c"
                    INCLUDE_DIRS "include"
                    REQUIRES nvs_flash
                    REQUIRES driver esp_timer esp_adc)
