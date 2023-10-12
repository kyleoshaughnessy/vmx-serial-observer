/* ==== Application Includes =============================================== */
#include "serial_interface/vmx_serial_if.h"
#include <stm32f4xx_hal.h>
#include <stdio.h>

/* ==== Globals ============================================================ */
UART_HandleTypeDef uartHandle =  { 0 };
uint8_t uartRxByte = 0;
uint8_t bReceived = 0;

typedef enum LED_COMMAND
{
    NOTHING,
    TURN_ON,
    TURN_OFF
} LED_COMMAND;

LED_COMMAND ledCommand = NOTHING;

/* ==== Functions ========================================================== */
static void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

static void initSystemClocks()
{
    RCC_OscInitTypeDef rccOscInit = {0};
    RCC_ClkInitTypeDef rccClkInit = {0};

    // Enable PWR clk
    __HAL_RCC_PWR_CLK_ENABLE();

    // Configure the main internal regulator output voltage
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Initialize RCC oscillators
    rccOscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    rccOscInit.HSEState       = RCC_HSE_ON;
    rccOscInit.PLL.PLLState   = RCC_PLL_ON;
    rccOscInit.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    rccOscInit.PLL.PLLM       = 25;
    rccOscInit.PLL.PLLN       = 192;
    rccOscInit.PLL.PLLP       = RCC_PLLP_DIV2;
    rccOscInit.PLL.PLLQ       = 4;
    if (HAL_RCC_OscConfig(&rccOscInit) != HAL_OK)
    {
        Error_Handler();
    }

    // Initialize CPU, AHB and APB clocks
    rccClkInit.ClockType      = RCC_CLOCKTYPE_HCLK   |
                                RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1  |
                                RCC_CLOCKTYPE_PCLK2;
    rccClkInit.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    rccClkInit.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    rccClkInit.APB1CLKDivider = RCC_HCLK_DIV2;
    rccClkInit.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&rccClkInit, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
}

static void initGPIO()
{
    GPIO_InitTypeDef gpioInit = { 0 };

    // Enable clocks for GPIO ports
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    gpioInit.Pin   = GPIO_PIN_13;
    gpioInit.Mode  = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull  = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOC, &gpioInit);
}

static void initUART(UART_HandleTypeDef *pUARTHandle)
{
    pUARTHandle->Instance          = USART1;
    pUARTHandle->Init.BaudRate     = 115200;
    pUARTHandle->Init.WordLength   = UART_WORDLENGTH_8B;
    pUARTHandle->Init.StopBits     = UART_STOPBITS_1;
    pUARTHandle->Init.Parity       = UART_PARITY_NONE;
    pUARTHandle->Init.Mode         = UART_MODE_TX_RX;
    pUARTHandle->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    pUARTHandle->Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(pUARTHandle) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (uartRxByte == '1')
    {
        ledCommand = TURN_OFF;
        bReceived = 1;
    }
    else if (uartRxByte == '2')
    {
        ledCommand = TURN_ON;
        bReceived = 1;
    }
    else
    {
        ledCommand = NOTHING;
        bReceived = 0;
    }
    uartRxByte = '\0';

    HAL_UART_Receive_IT(&uartHandle, &uartRxByte, 1);
}

int main(void)
{
    uint8_t msgOut[25] = { '\0' };
    uint8_t numChars;

    HAL_Init();
    initSystemClocks();
    initGPIO();
    initUART(&uartHandle);

    // Power on banner
    numChars = sprintf((char *)msgOut, "\r\n");
    HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);
    numChars = sprintf((char *)msgOut, "Device powered on...\r\n");
    HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);
    numChars = sprintf((char *)msgOut, "\r\n");
    HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);

    // Set initial led pin state
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    numChars = sprintf((char *)msgOut, "LED ON\r\n");
    HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);
    HAL_UART_Receive_IT(&uartHandle, &uartRxByte, 1);

    while (1)
    {
        if (bReceived)
        {
            if (ledCommand == TURN_OFF)
            {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                numChars = sprintf((char *)msgOut, "LED OFF\r\n");
                HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);
            }
            else if (ledCommand == TURN_ON)
            {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                numChars = sprintf((char *)msgOut, "LED ON\r\n");
                HAL_UART_Transmit(&uartHandle, msgOut, numChars + 1, 100);
            }

            bReceived = 0;
        }
        HAL_Delay(50);
    }

    return 0;
}
