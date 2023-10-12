/* ==== Includes =========================================================== */
#include "stm32f4xx_hal.h"

/* ==== Functions ========================================================== */
/*!
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

/*!
 * @brief UART MSP Initialization
 * This function configures the hardware resources
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(huart->Instance==USART1)
    {
        // Peripheral clock enable
        __HAL_RCC_USART1_CLK_ENABLE();

        // GPIO port clock enable
        __HAL_RCC_GPIOA_CLK_ENABLE();

        //
        // USART1 GPIO Configuration
        // PA9  -> USART1_TX
        // PA10 -> USART1_RX
        //
        GPIO_InitStruct.Pin       = GPIO_PIN_9|GPIO_PIN_10;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // USART1 interrupt Init
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

/*!
 * @brief UART MSP De-Initialization
 * This function freezes the hardware resources
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if(huart->Instance==USART1)
    {
        // Peripheral clock disable
        __HAL_RCC_USART1_CLK_DISABLE();

        //
        // USART1 GPIO Configuration
        // PA9  -> USART1_TX
        // PA10 -> USART1_RX
        //
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

        // USART1 interrupt DeInit
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
}
