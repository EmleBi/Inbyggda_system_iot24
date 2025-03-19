#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t pin;
    bool lastState;
    bool currentState;
    bool pressed;
    uint64_t lastDebounceTime;
    void (*onPressed)(int pin);
} MyButton_t;

void my_btn_init(MyButton_t* btn, uint8_t pin);
void my_btn_update(MyButton_t* btn); 
bool my_btn_isPressed(MyButton_t* btn);
void my_btn_setOnPressed(MyButton_t* btn, void (*onPressed)(int pin));

#endif 
