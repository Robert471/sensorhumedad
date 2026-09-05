#ifndef __OUTPUT__
#define __OUTPUT__

#define PRT_LED1	GPIOA
#define PIN_LED1	GPIO_PIN_5

void output_init(void);
void output_high(void);
void output_low(void);

#endif


