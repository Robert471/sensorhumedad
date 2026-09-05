/**
 *	@file 		uart.h
 * 	@brief 		Header file para usart.c
 * 	@par 			DEVICE:	STM32F103C8T6 
 * 	@author 	Robert Ramirez Barrera
 * 	@version 	1.0
 * 	@date			16/06/2017
 * 	@bug
 *	@pre 		Antes de llamar a esta funcion:
 * 						- incluir en el proyecto a "stm32f1xx_hal_uart.c" y "stm32f1xx_hal_uart_ex.c"
 *						-	Habilitar al periferico con #define HAL_ADC_MODULE_ENABLED
 * 	@warning 	El uso inadecuado de esta libreria puede interrumpir el programa principal.
 * 	@par 			Licence/Copyright
 * 						This sources code are under GNU LGPL licence (* : see on "http://www.gnu.org/licenses/licenses.html").
 *           		- This files can be used for commercial usage and free usage.
 *           		- The files should be free*, publiched.
 *           		- This authors should be informed about modification done this.
 *
 *       			The documentation is under GNU FDL licence (* see on "http://www.gnu.org/licenses/licenses.html").
 *
 */
#ifndef __RS232__
#define __RS232__

#include "stm32f4xx.h"
void rs232_send_byte(char TxData);
void rs232_send_string(volatile char *s);
void rs232_init(uint32_t baud);

void rs232_echo(void);
void rs232_buffer_clear(void);

#endif
