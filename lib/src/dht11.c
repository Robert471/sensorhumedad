
#include "stm32f4xx_hal.h"
#include "dht11.h"
#include "stm32f4xx.h"                  // Device header

extern UART_HandleTypeDef huart2;

uint8_t temperatura = 0, humedad = 0;

int dht11_read(void)
{
	uint8_t bit = 0;
	uint8_t data[5];

	/*
	1.	Envía “0” por un tiempo de 18ms
	2.	Envía “1” por un tiempo de 40us
	3.	Espera una señal de “0” por un tiempo de 80us
	4.	Espera una señal de “1” por un tiempo de 80us
	5.	Lectura de datos de 40bits, espera por un tiempo de 50us luego espera el tiempo del bit si es menor a 26-28 us es “0” si es mayor a 70us es “1”
	6.	Verificar el checksum, y leer los datos
	 * */

	RCC->AHB1ENR |= (1 << 2);	//	ENABLED CLOCK GPIOC
	//CONFIGURANDO EL PC3 COMO SALIDA
	GPIOC->MODER &= ~(1 << (2*(3) + 1));					//	01: MODO SALIDA
	GPIOC->MODER |=  (1 << (2*(3) ));
	GPIOC->OTYPER &= ~(1 << (3));							//	 0: PUSH PULL
	GPIOC->OSPEEDR |= (1 << (2*(3) + 1)) | ( 1 << 2*(3));	//	11: MAXIMA VELOCIDAD
	GPIOC->PUPDR &= ~(1 << (2*(3) + 1)) & ~(1 << (2*(3)));	//	00: NO PULL UP NI PULL DOWN

	// 1.	Envía “0” por un tiempo de 18ms
	GPIOC->ODR &= ~(1 << 3);
	TIM3->CNT = 0;
	while(TIM3->CNT <= 18000);	//	18ms
	//2.	Envía “1” por un tiempo de 40us
	GPIOC->ODR |= (1 << 3);
	TIM3->CNT = 0;
	while(TIM3->CNT <= 40);		//	40us

	GPIOC->MODER &= ~(1 << (2*(3) + 1)) & ~(1 << (2*(3)));	//	00: MODO ENTRADA
	GPIOC->PUPDR &= ~(1 << (2*(3) + 1)) & ~(1 << (2*(3)));	//	00: NO PULL UP NI PULL DOWN
	//3.	Espera una señal de “0” por un tiempo de 80us
	TIM3->CNT = 0;
	while( !(GPIOC->IDR & (1 << 3)) )
	{
		if( TIM3->CNT > 100 )	return 1;	//	FALLO POR TIMEOUT
	}
	//4.	Espera una señal de “1” por un tiempo de 80us
	TIM3->CNT = 0;
	while( (GPIOC->IDR & (1 << 3)) )
	{
		if( TIM3->CNT > 100 )	return 1;	//	FALLO POR TIMEOUT
	}

	//5.	Lectura de datos de 40bits, espera por un tiempo de 50us luego espera el
	//	tiempo del bit si es menor a 26-28 us es “0” si es mayor a 70us es “1”
	for(uint8_t j = 0; j < 5; j++)
	{
		for(uint8_t i = 0; i < 8; i++)	//	8bits
		{
			while( !(GPIOC->IDR & (1 << 3)) );
			TIM3->CNT = 0;
			while(TIM3->CNT <= 30);
			if( GPIOC->IDR & (1 << 3 ))
			{
				//bit = 1
				bit = (bit << 1) | 1;
			}else
			{
				//bit = 0
				bit = (bit << 1);
			}
			while( GPIOC->IDR & (1 << 3) );
		}
		data[j] = bit;
	}
	//	6.	Verificar el checksum, y leer los datos
	if( data[4] != (data[0] + data[1] + data[2] + data[3]) )
		return 2;	//	FALLO POR CHECKSUM

	humedad =  data[0];
	temperatura =  data[2];

	return 0;


}

