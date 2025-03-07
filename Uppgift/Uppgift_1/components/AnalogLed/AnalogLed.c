/*#include "AnalogLed.h"

void analog_led_init(int pin, int duty_cycle, double frequency, AnalogLed_t *led) {
    led->pin = pin;
    led->timer_channel = 0;
    led->period = 3000; // 3 sek sinusvågor
    led->last_update = xTaskGetTickCount();
    led->duty_cycle = (duty_cycle >= 0 && duty_cycle <= 255) //? duty_cycle : 200; // Använd ett fast värde mellan 0 och 255
    led->target_duty_cycle = led->duty_cycle;
    led->amplitude = 1.0;
    led->frequency = (frequency >= 0.0) ? frequency : 1.0;
    led->led_on = false; // Initialisera LED till av

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = led->timer_channel,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = pin,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&ledc_channel);
}

void setAnalogLed(bool led_on, int duty_cycle, double frequency, AnalogLed_t *led) {
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 255) duty_cycle = 255;
    led->led_on = led_on;
    led->target_duty_cycle = duty_cycle;
    led->frequency = frequency;
}

void update_analog(AnalogLed_t *led) {
    TickType_t now = xTaskGetTickCount();
    TickType_t elapsed = now - led->last_update;

    if (elapsed > pdMS_TO_TICKS(100)) {
        led->last_update = now;
        double delta = led->target_duty_cycle - led->amplitude;
        led->amplitude += delta * 0.1;

        if (!led->led_on) {
            led->duty_cycle = 0;
        } else if (led->frequency == 0.0) {
            led->duty_cycle = led->target_duty_cycle; 
        } else {
            double angle = (2.0 * M_PI * ((double)(now % pdMS_TO_TICKS(led->period)) / (double)pdMS_TO_TICKS(led->period))) * led->frequency;
            led->duty_cycle = (int)(0.5 * (1.0 + sin(angle)) * led->target_duty_cycle);
        }

        ledc_set_duty(LEDC_LOW_SPEED_MODE, led->timer_channel, led->duty_cycle);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, led->timer_channel);

        printf("LED Pin: %d\n", led->pin);
        printf("Elapsed Time: %u ticks\n", (unsigned int)elapsed);
        printf("Duty Cycle: %d\n", led->duty_cycle);
    }
}

void sin_wave(double period, AnalogLed_t *led) {
    led->period = period;
} */

#include "AnalogLed.h"

void analog_led_init(int pin, int duty_cycle, double frequency, AnalogLed_t *led) {
    led->pin = pin;
    led->timer_channel = 0;
    led->period = 3000; // 3 sek sinusvågor
    led->last_update = xTaskGetTickCount();
    led->duty_cycle = (duty_cycle >= 0 && duty_cycle <= 255) ? duty_cycle : 200; // Använd ett fast värde mellan 0 och 255
    led->target_duty_cycle = led->duty_cycle;
    led->amplitude = 1.0;
    led->frequency = (frequency >= 0.0) ? frequency : 1.0;
    led->led_on = false; // Initialisera LED till av
    led->behavior = 0; // Initialisera beteende till 0

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = led->timer_channel,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = pin,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&ledc_channel);
}

void setAnalogLed(bool led_on, int duty_cycle, double frequency, int behavior, AnalogLed_t *led) {
    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 255) duty_cycle = 255;
    led->led_on = led_on;
    led->target_duty_cycle = duty_cycle;
    led->frequency = frequency;
    led->behavior = behavior;

    switch (behavior) {
        case 0: // LED släckt
            led->duty_cycle = 0;
            ledc_set_duty(LEDC_LOW_SPEED_MODE, led->timer_channel, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, led->timer_channel);
            break;
        case 1: // LED lyser jämt
            led->duty_cycle = duty_cycle;
            ledc_set_duty(LEDC_LOW_SPEED_MODE, led->timer_channel, duty_cycle);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, led->timer_channel);
            break;
        case 2: // LED blinkar i sinusvågor
            led->amplitude = duty_cycle / 2.0;
            led->period = 1.0 / frequency * 1000; // Perioden i millisekunder
            break;
        default:
            printf("Okänt beteende: %d\n", behavior);
            break;
    }
}

void update_analog(AnalogLed_t *led) {
    TickType_t now = xTaskGetTickCount();
    TickType_t elapsed = now - led->last_update;

    if (elapsed > pdMS_TO_TICKS(100)) {
        led->last_update = now;
        double delta = led->target_duty_cycle - led->amplitude;
        led->amplitude += delta * 0.1;

        if (!led->led_on) {
            led->duty_cycle = 0;
        } else if (led->frequency == 0.0) {
            led->duty_cycle = led->target_duty_cycle; 
        } else {
            double angle = (2.0 * M_PI * ((double)(now % pdMS_TO_TICKS(led->period)) / (double)pdMS_TO_TICKS(led->period))) * led->frequency;
            led->duty_cycle = (int)(0.5 * (1.0 + sin(angle)) * led->target_duty_cycle);
        }

        ledc_set_duty(LEDC_LOW_SPEED_MODE, led->timer_channel, led->duty_cycle);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, led->timer_channel);

        printf("LED Pin: %d\n", led->pin);
        printf("Elapsed Time: %u ticks\n", (unsigned int)elapsed);
        printf("Duty Cycle: %d\n", led->duty_cycle);
    }
}

void sin_wave(double period, AnalogLed_t *led) {
    led->period = period;
}



