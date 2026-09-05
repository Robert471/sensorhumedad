
#include "stm32f4xx_hal.h"
#include "rs232.h"
#include "stm32f4xx.h"                  // Device header

extern UART_HandleTypeDef huart2;

void rs232_init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	huart2.Instance = USART2;
	huart2.Init.BaudRate = baud;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);
	
	//-------------------	ENABLED INTERRUPT
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	
}

void rs232_send_byte(char TxData){
	while((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) ? SET : RESET) == RESET);
	huart2.Instance->DR = TxData;
}

void rs232_send_string(volatile char *s)
{
	while(*s){
		while((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TXE) ? SET : RESET) == RESET);
		huart2.Instance->DR = *s;
		*s++;
	}
}
