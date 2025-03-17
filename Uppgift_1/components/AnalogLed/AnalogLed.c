/*#include "AnalogLed.h"

void analog_led_init(AnalogLED_t *led, int pin) {
    led->pin = pin;
    led->value = 0;
    led->is_sin_wave = 0;
    led->period = 0;
    led->last_update = 0;

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL,
        .duty = 0,
        .gpio_num = pin,
        .speed_mode = LEDC_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER
    };
    ledc_channel_config(&ledc_channel);
}

void analog_led_update(AnalogLED_t *led) {
    uint64_t current_time = esp_timer_get_time();
    int led_value = led->value;
    if (led->is_sin_wave) {
        double time_in_period = (current_time % (led->period * 1000)) / 1000.0;
        double angle = (2.0 * M_PI * time_in_period) / led->period;
        led_value = (int)(led->value * (0.5 + 0.5 * sin(angle)));
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led_value);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void analog_set_led(AnalogLED_t *led, int value, int enable) {
    led->value = value;

    if (!led->is_sin_wave) {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led->value);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }else {
        led->is_sin_wave = 0;
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led->value);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}

void analog_sin_wave(AnalogLED_t *led, int period) {
    led->period = period;
    if (period) {
        led->is_sin_wave = 1;
    } 
}*/
#include "AnalogLed.h"

void analog_led_init(AnalogLED_t *led, int pin) {
    led->pin = pin;
    led->value = 0;
    led->is_sin_wave = 0;
    led->period = 0;
    led->last_update = 0;

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL,
        .duty = 0,
        .gpio_num = pin,
        .speed_mode = LEDC_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_TIMER
    };
    ledc_channel_config(&ledc_channel);
}

void analog_led_update(AnalogLED_t *led) {
    uint64_t current_time = esp_timer_get_time();
    int led_value = led->value;

    if (led->is_sin_wave) {
        double time_in_period = (current_time % (led->period * 1000)) / 1000.0;
        double angle = (2.0 * M_PI * time_in_period) / led->period;
        led_value = (int)(led->value * (0.5 + 0.5 * sin(angle)));
    }

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led_value);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void analog_set_led(AnalogLED_t *led, int value) {
    led->value = value;
    led->is_sin_wave = 0; // Stäng av sinusvågen
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led->value); // Sätt konstant ljusstyrka
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void analog_sin_wave(AnalogLED_t *led, int period) {
    led->is_sin_wave = 1;
    led->period = period; // Uppdatera perioden om sinusvågen är aktiv
}
