#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

// LED PWM-konfiguration
#define LED_PIN GPIO_NUM_2
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT
#define LEDC_FREQUENCY 5000 // 5 kHz

// Knapp PIN-konfigurationer
#define BTN_INC_PIN GPIO_NUM_12
#define BTN_DEC_PIN GPIO_NUM_14

void app_main(void)
{
    // Konfiguration av knappar
    gpio_config_t btn_io_conf = {};
    btn_io_conf.intr_type = GPIO_INTR_DISABLE;
    btn_io_conf.mode = GPIO_MODE_INPUT;
    btn_io_conf.pin_bit_mask = (1ULL << BTN_INC_PIN) | (1ULL << BTN_DEC_PIN);
    btn_io_conf.pull_down_en = 1;
    btn_io_conf.pull_up_en = 0;
    gpio_config(&btn_io_conf);

    // Konfiguration av LED PWM
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_PIN,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);

    int duty = 0;
    while (1)
    {
        //avläsning av knappvärden
        int btn_inc_val = gpio_get_level(BTN_INC_PIN);
        int btn_dec_val = gpio_get_level(BTN_DEC_PIN);

        //Duty cycle baserat på knapptryckningar
        if (btn_inc_val == 1 && duty < (1 << LEDC_DUTY_RES) - 1) {
            duty++;
        }
        if (btn_dec_val == 1 && duty > 0) {
            duty--;
        }

        // Uppdatera LED duty cycle
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

        printf("Duty cycle - driftcycel: %d\n", duty);

        // Väntar innan nästa avläsning
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
