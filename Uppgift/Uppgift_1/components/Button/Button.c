#include "driver/gpio.h"
#include <stdio.h>
#include "Button.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_DEBOUNCE_PERIOD 10000

void my_btn_init(MyButton_t* btn, uint8_t pin) {
    btn->pin = pin;
    btn->lastState = true;
    btn->currentState = true;  
    btn->pressed = false;
    btn->lastDebounceTime = 0;
    btn->onPressed = NULL;

    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}

void my_btn_update(MyButton_t* btn) {
    uint64_t currentTime = esp_timer_get_time();
    bool pinValue = gpio_get_level(btn->pin);
    if (pinValue != btn->lastState) {
        btn->lastDebounceTime = currentTime;
    }

    if ((currentTime - btn->lastDebounceTime) > BUTTON_DEBOUNCE_PERIOD) {
        if (pinValue != btn->currentState) {
            btn->currentState = pinValue;
            if (!btn->currentState) {  
                btn->pressed = true;
                if (btn->onPressed) {
                    btn->onPressed(btn->pin);
                }
            } else {
                btn->pressed = false;
            }
        }
    }

    btn->lastState = pinValue;
}

bool my_btn_isPressed(MyButton_t* btn) {
    return btn->pressed;
}

void my_btn_setOnPressed(MyButton_t* btn, void (*onPressed)(int pin)) {
    btn->onPressed = onPressed;
}
