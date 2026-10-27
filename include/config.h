#pragma once
#include "stm32f4xx_hal.h"
#include <stdbool.h>

struct Config
{
    #define LED_PORT GPIOC
    #define LED_PIN GPIO_PIN_15
    #define BTN_PORT GPIOA
    #define BTN_PIN GPIO_PIN_5
    #define DEBOUNCE_MS 200
    #define BLINK_TIME_MS 500

   
};

    volatile uint32_t last_press = 0;
    volatile uint32_t last_blink = 0;
    volatile bool press = false;
    volatile uint8_t LED_STATE_IS = 0;

enum led_state { //state machine
    NO_ACTIVE,
    BLINK,
    ON
};
