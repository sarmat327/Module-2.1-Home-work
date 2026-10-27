#pragma once
#include "stm32f4xx_hal.h"
#include <stdbool.h>

struct Config
{
    #define LED_PORT GPIOC
    #define LED_PIN GPIO_PIN_13
    #define BTN_PORT GPIOA
    #define BTN_PIN GPIO_PIN_5
    #define DEBOUNCE_MS 100

   
};

    volatile uint32_t last_press = 0;
    volatile bool press = false;

enum led_state { //state machine
    NO_ACTIVE,
    BLINK,
    ON
};
