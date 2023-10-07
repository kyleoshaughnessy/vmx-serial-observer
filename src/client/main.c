/* ==== Application Includes =============================================== */
#include "serial_interface/vmx_serial_if.h"
#include <stm32f4xx_hal.h>

// We Act Studio STM32F411 “BlackPill” Development Board - PC13
#define LED_PORT                GPIOC
#define LED_PIN                 GPIO_PIN_13
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOC_CLK_ENABLE

/* ==== Functions ========================================================== */
void SysTick_Handler(void)
{
    HAL_IncTick();

    // 1 Hz blinking
    if ((HAL_GetTick() % 500) == 0)
    {
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    }
}

void initGPIO()
{
    GPIO_InitTypeDef GPIO_Config;

    GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Config.Pull = GPIO_NOPULL;
    GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Config.Pin = LED_PIN;

    LED_PORT_CLK_ENABLE();
    HAL_GPIO_Init(LED_PORT, &GPIO_Config);
}

int main(void)
{
    HAL_Init();
    initGPIO();

    // 1kHz ticks
    HAL_SYSTICK_Config(SystemCoreClock / 1000);

    while(1);

    return 0;
}
