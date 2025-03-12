 #include "led.h"
 #include "driver/gpio.h"
 #include "freertos/FreeRTOS.h"
 #include "freertos/task.h"
 #include "esp_timer.h"
        
        
void led_init(LED_t *led, int pin) {
    led->pin = pin;
    led->value = 0;
    led->is_blinking = 0;
    led->last_toggle = esp_timer_get_time() / 1000;
            
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, 0);
}
        
void update( LED_t*led) {
     if (led->is_blinking) {
        uint64_t now = esp_timer_get_time() / 1000;
        uint64_t elapsed = now - led->last_toggle;
                
        if (led->value && elapsed >= led->blink_on) {
            led->value = 0;
            led->last_toggle = now;
        } else if (!led->value && elapsed >= led->blink_off) {
            led->value = 1;
            led->last_toggle = now;           
        }  
    }
    gpio_set_level(led->pin, led->value);
}
       
void setLed(LED_t *led, int value) {
    led->is_blinking = 0;
    led->value = value;
}
        
void blink(LED_t *led, int milliseconds_on, int milliseconds_off) {
    led->is_blinking = 1;
    led->blink_on = milliseconds_on;
    led->blink_off = milliseconds_off;
    led->last_toggle = esp_timer_get_time() / 1000;
}
