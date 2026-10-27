
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "config.h"


static void GPIO_Init(void)
{

    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    //Ініціалізація СВІТЛОДІОДА
    gpio.Pin = LED_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_PORT, &gpio);
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);

     //Ініціалізація КНОПКИ
    gpio.Pin = BTN_PIN;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(BTN_PORT, &gpio);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    if (GPIO_Pin == BTN_PIN)
    {
        if (now - last_press > DEBOUNCE_MS)
        {
            last_press = now;
            press = true;
            LED_STATE_IS ++; 
        }
    }
}

int main(void)
{
    HAL_Init();
    GPIO_Init();
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

    while (1)
    {
        if (press)
        {
            switch (LED_STATE_IS)
            {
            case NO_ACTIVE:
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

                break;

            case BLINK:
            {
                uint32_t now = HAL_GetTick();

                if (now - last_blink > BLINK_TIME_MS)
                    {
                        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
                        last_blink = HAL_GetTick();
                    }
                break;
            }  
            case ON:
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
                break;
            
            default:
                        LED_STATE_IS = NO_ACTIVE;
                break;
            }
        }
    }
}