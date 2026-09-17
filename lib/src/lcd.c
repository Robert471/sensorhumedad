#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "lcd.h"
//#include "stdio.h"
/*
 * char strtemp[15];
 * sprintf(strtemp, "TEMP=%d", temparature);
 *
 * */
void lcd_init(void)
{
	/*
		LCDRS_PIN      //	PA9
		LCDE_PIN       //	PC7
		LCD4_PIN       //	PB5
		LCD5_PIN       //	PB4
		LCD6_PIN       //	PB10
		LCD7_PIN       //	PA8
	*/
	RCC->AHB1ENR |= (1<<2) | (1<<1) | (1<< 0);

	GPIOA->MODER   &= ~(1 << 2*(9) + 1);	//	A9
	GPIOA->MODER   |=  (1 << 2*(9) );
	GPIOA->OTYPER  &= ~(1 <<   (9) );
	GPIOA->OSPEEDR |=  (1 << (2*(9) + 1) ) |  (1 <<  2*(9) );		//	01: 25 MHz Medium speed
	GPIOA->PUPDR   &= ~(1 << (2*(9) + 1) ) & ~(1 << (2*(9)) );

	GPIOC->MODER   &= ~(1 <<  2*(7) + 1);	//	C7
	GPIOC->MODER   |=  (1 <<  2*(7) );
	GPIOC->OTYPER  &= ~(1 <<   (7) );
	GPIOC->OSPEEDR |=  (1 << (2*(7) + 1) ) |  (1 <<  2*(7) );
	GPIOC->PUPDR   &= ~(1 << (2*(7) + 1) ) & ~(1 << (2*(7)) );

	GPIOB->MODER   &= ~(1 <<  2*(5) + 1);	//	B5
	GPIOB->MODER   |=  (1 <<  2*(5) );
	GPIOB->OTYPER  &= ~(1 <<    (5) );
	GPIOB->OSPEEDR |=  (1 << (2*(5) + 1) ) |  (1 <<  2*(5) );
	GPIOB->PUPDR   &= ~(1 << (2*(5) + 1) ) & ~(1 << (2*(5)) );

	GPIOB->MODER   &= ~(1 <<  2*(4) + 1);	//	B4
	GPIOB->MODER   |=  (1 <<  2*(4) );
	GPIOB->OTYPER  &= ~(1 <<    (4) );
	GPIOB->OSPEEDR |=  (1 << (2*(4) + 1) ) |  (1 <<  2*(4) );
	GPIOB->PUPDR   &= ~(1 << (2*(4) + 1) ) & ~(1 << (2*(4)) );

	GPIOB->MODER   &= ~(1 <<  2*(10) + 1);	//	B10
	GPIOB->MODER   |=  (1 <<  2*(10) );
	GPIOB->OTYPER  &= ~(1 <<    (10) );
	GPIOB->OSPEEDR |=  (1 << (2*(10) + 1) ) |  (1 <<  2*(10) );
	GPIOB->PUPDR   &= ~(1 << (2*(10) + 1) ) & ~(1 << (2*(10)) );

	GPIOA->MODER   &= ~(1 <<  2*(8) + 1);	//	A8
	GPIOA->MODER   |=  (1 <<  2*(8) );
	GPIOA->OTYPER  &= ~(1 <<    (8) );
	GPIOA->OSPEEDR |=  (1 << (2*(8) + 1) ) |  (1 <<  2*(8) );
	GPIOA->PUPDR   &= ~(1 << (2*(8) + 1) ) & ~(1 << (2*(8)) );

	HAL_Delay(15);
	LCD7_OFF; LCD6_OFF; LCD5_OFF; LCD4_OFF;
	LCDE_OFF;
	//LCDRW_OFF;
	LCDRS_OFF;
	//---------one------
	LCD7_OFF; LCD6_OFF; LCD5_ON; LCD4_ON;
	LCDE_ON;
	//LCDRW_OFF;
	LCDRS_OFF;
	HAL_Delay(10);
	LCDE_OFF;
	HAL_Delay(10);
	//-----------two-----------
	LCD7_OFF; LCD6_OFF; LCD5_ON; LCD4_ON;
	LCDE_ON;
	//LCDRW_OFF;
	LCDRS_OFF;
	HAL_Delay(10);
	LCDE_OFF;
	HAL_Delay(10);
	//-------three-------------
	LCD7_OFF; LCD6_OFF; LCD5_ON; LCD4_OFF;
	LCDE_ON;
	//LCDRW_OFF;
	LCDRS_OFF;
	HAL_Delay(10);
	LCDE_OFF;
	HAL_Delay(10);
	//--------4 bit--dual line--5x8 dots---------------
	lcd_command(SETLCD_4BITS_2LINE);
	//-----increment address, invisible cursor shift------
	lcd_command(DISPLAY_ON_D_OFF_CB);
	//-----Clear display
	lcd_clear();
}

void lcd_putc(unsigned char ch){		//Sends Char to LCD

	LCDRS_ON;

  if ( ch & 0x10 ) {
		LCD4_ON;
	} else {
		LCD4_OFF;
	}
	if ( ch & 0x20 ) {
		LCD5_ON;
	} else {
    LCD5_OFF;
	}
	if ( ch & 0x40 ) {
		LCD6_ON;
	} else {
		LCD6_OFF;
	}
	if ( ch & 0x80 ) {
		LCD7_ON;
	} else {
		LCD7_OFF;
	}

	LCDE_ON;
	HAL_Delay(2);//__delay_us(300);
	LCDE_OFF;
	HAL_Delay(2);//__delay_us(300);

	if ( ch & 0x01 ) {
		LCD4_ON;
	} else {
		LCD4_OFF;
	}
	if ( ch & 0x02 ) {
		LCD5_ON;
	} else {
    LCD5_OFF;
	}
	if ( ch & 0x04 ) {
		LCD6_ON;
	} else {
    LCD6_OFF;
	}
	if ( ch & 0x08 ) {
		LCD7_ON;
	} else {
    LCD7_OFF;
	}

	LCDE_ON;
	HAL_Delay(2);//__delay_us(300);
	LCDE_OFF;
	HAL_Delay(2);//__delay_us(300);
}
void lcd_command(unsigned char cmd){	//Sends Command to LCD

	LCDRS_OFF;

	if ( cmd & 0x10 ) {
		LCD4_ON;
	} else {
		LCD4_OFF;
	}
	if ( cmd & 0x20 ) {
		LCD5_ON;
	} else {
		LCD5_OFF;
	}
	if ( cmd & 0x40 ) {
		LCD6_ON;
	} else {
		LCD6_OFF;
	}
	if ( cmd & 0x80 ) {
		LCD7_ON;
	} else {
		LCD7_OFF;
	}

	LCDE_ON;
	HAL_Delay(2);//__delay_us(300);
	LCDE_OFF;
	HAL_Delay(2);//__delay_us(300);

	if ( cmd & 0x01 ) {
		LCD4_ON;
	} else {
		LCD4_OFF;
	}
	if ( cmd & 0x02 ) {
		LCD5_ON;
	} else {
		LCD5_OFF;
	}
	if ( cmd & 0x04 ) {
		LCD6_ON;
	} else {
		LCD6_OFF;
	}
	if ( cmd & 0x08 ) {
		LCD7_ON;
	} else {
		LCD7_OFF;
	}

	LCDE_ON;
	HAL_Delay(2);//__delay_us(300);
	LCDE_OFF;
	HAL_Delay(2);//__delay_us(300);

}

void lcd_puts(char* data, unsigned char nBytes){	//Outputs string to LCD
	register unsigned char i=0;

	for(i=0; i<nBytes; i++){	// print data
		lcd_putc(data[i]);
	}
}

void lcd_gotoxy(unsigned char x, unsigned char y){		//Cursor to X Y position
	register unsigned char DDRAMAddr;

	switch(y){		// remap lines into proper order
	case 1: DDRAMAddr = LCD_LINE0_DDRAMADDR+x-1; break;
	case 2: DDRAMAddr = LCD_LINE1_DDRAMADDR+x-1; break;
	case 3: DDRAMAddr = LCD_LINE2_DDRAMADDR+x-1; break;
	case 4: DDRAMAddr = LCD_LINE3_DDRAMADDR+x-1; break;
	default: DDRAMAddr =LCD_LINE0_DDRAMADDR+x-1;break;
	}
	lcd_command(1<<LCD_DDRAM|DDRAMAddr);	// set data address
}
/*  Funcion para escribir en la CGRAM
 *	DATASHEET HD44780U (LCD-II) (Dot Matrix Liquid Crystal Display Controller/Driver)
 *	page 19.
 * */
void lcd_definechar(unsigned char *car,unsigned char CGRAM_dir){
	unsigned char i=0,a=0;
	a=(CGRAM_dir<<3)|1<<LCD_CGRAM;		//	posiciona en la CGRAM address
	for(i=0;i<8;i++){
        lcd_command(a++);			//	incrementa la direccion para la data
		lcd_putc(car[i]);			//	escribe caracter
	}
}

void lcd_clear(void){
    lcd_command(CLEAR_DISPLAY);
}


