/*#include "AnalogLed.h"

static uint64_t start_time = 0;

void analogLed_init(AnalogLed* led, uint8_t pin) {
    led->pin = pin;
    led->brightness = 0;
    led->period = 0;
    led->blink_on = 0;
    led->blink_off = 0;
    led->is_blinking = 0;
    start_time = esp_timer_get_time();

    // Init LED PWM funktion 
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,  
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,  
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE, 
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pin,
        .duty           = 0, 
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

void analogLed_update(AnalogLed* led) {
    if (led->blink_off) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0); 
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    } else if (led->blink_on) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 8191); 
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    } else if (led->is_blinking && led->period > 0) {
        uint64_t time_elapsed = esp_timer_get_time() - start_time;
        float sin_value = (sin(2 * M_PI * (time_elapsed % (led->period * 1000)) / (led->period * 1000)) + 1) / 2;
        uint32_t duty = (uint32_t)(sin_value * led->brightness * 8191 / 255);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty); 
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    } else {
        uint32_t duty = led->brightness * 8191 / 255;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty); 
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0); 
    }
}

void analogLed_setBrightness(AnalogLed* led, uint8_t value) {
    if (value <= 255) {
        led->blink_off = 0;
        led->blink_on = 1;
        led->is_blinking = 0;
    } else if (value == 0) {
        led->blink_off = 1;
        led->blink_on = 0;
        led->is_blinking = 0;
    } else {
        led->brightness = value;
        led->blink_off = 0;
        led->blink_on = 0;
        led->is_blinking = 1;
    }
    analogLed_update(led);
}

void analogLed_setBlinking(AnalogLed* led, uint8_t is_blinking) {
    led->is_blinking = is_blinking;
}*/



/*#include "AnalogLed.h"

static uint64_t start_time = 0;

void analogLed_init(AnalogLed* led, uint8_t pin) {
    led->pin = pin;
    led->brightness = 255; // Standard ljusstyrka
    led->period = 4000; // Standard blinkperiod
    led->blink_on = 0;
    led->blink_off = 0;
    led->is_blinking = 0;
    led->mode_changed = 0; // Initialt har läget inte ändrats
    start_time = esp_timer_get_time();

    // Init LED PWM funktion 
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = pin,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

void analogLed_update(AnalogLed* led) {
    if (led->mode_changed) { // Om läget har ändrats, uppdatera blinkläget
        if (led->blink_off) {
            led->is_blinking = 0;
        } else if (led->blink_on) {
            led->is_blinking = 1;
        }
        led->mode_changed = 0; // Läget har nu uppdaterats
    }

    if (led->blink_off) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    } else if (led->is_blinking) {
        uint64_t time_elapsed = esp_timer_get_time() - start_time;
        float sin_value = (sin(2 * M_PI * time_elapsed / (led->period * 1000)) + 1) / 2; // Mjukare sinusvåg
        uint32_t duty = (uint32_t)(sin_value * led->brightness * 8191 / 255);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    } else if (led->blink_on) {
        uint32_t duty = led->brightness * 8191 / 255;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    } else {
        uint32_t duty = led->brightness * 8191 / 255;
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }
}

void setAnalogLed(AnalogLed* led, uint8_t value) {
    led->brightness = value;
    led->blink_off = 0;
    led->blink_on = 1;
    led->is_blinking = 0;
    analogLed_update(led);
}

void analogLed_setBlinking(AnalogLed* led, uint32_t period) {
    led->period = period;
    led->is_blinking = 1;
}

void set_led_blink_mode(AnalogLed* led, uint8_t blink_on, uint8_t blink_off) {
    led->blink_on = blink_on;
    led->blink_off = blink_off;
    led->mode_changed = 1; // Indikerar att läget har ändrats
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

void analog_set_led(AnalogLED_t *led, int value, int period) {
    led->value = value;
    led->period = period;
    if (!led->is_sin_wave) {
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led->value);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}

void analog_sin_wave(AnalogLED_t *led, int enable) {
    if (enable) {
        led->is_sin_wave = 1;
    } else {
        led->is_sin_wave = 0;
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, led->value);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
    }
}


