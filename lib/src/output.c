#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "output.h"
#include "main.h"

void output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/*Configure GPIO pins : IN7_Pin IN6_Pin */
	GPIO_InitStruct.Pin = PIN_LED1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(PRT_LED1, &GPIO_InitStruct);

	output_low();
}

void output_high(void){ 
	HAL_GPIO_WritePin(PRT_LED1, PIN_LED1,GPIO_PIN_SET);
}

void output_low(void){ 
	HAL_GPIO_WritePin(PRT_LED1, PIN_LED1,GPIO_PIN_RESET);
}
