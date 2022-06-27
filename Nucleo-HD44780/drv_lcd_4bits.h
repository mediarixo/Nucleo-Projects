#ifndef INC_DRV_LCD_4BITS_H_
#define INC_DRV_LCD_4BITS_H_

#include "stm32f401xe.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define RS  1   
#define RW  2   
#define EN  4   

#define LCD_BACKLIGHT    		0x08           
#define LCD_NOBACKLIGHT  		0x00	

#define LCD_FUNCTIONSET     	0x20
#define LCD_4BIT_MODE 			0x00			
#define LCD_2LINE 				0x08			
#define LCD_5x8DOTS 			0x00

#define LCD_ENTRYMODESET 	    0x04
#define LCD_AUTOINCREMENT		0x02
#define LCD_NOSHIFT				0X00	

#define LCD_DISPLAYCONTROL      0x08
#define LCD_DISPLAY_ON 			0x04			
#define LCD_DISPLAY_OFF 		0x00
#define LCD_CURSOR_ON 			0x02			
#define LCD_CURSOR_OFF 			0x00
#define LCD_BLINK_ON 			0x01			
#define LCD_BLINK_OFF 			0x00

#define LCD_CLEARDISPLAY 		0x01
#define LCD_RETURNHOME 			0x02
#define LCD_SET_DDRAM_ADDR 		0x80

void LCD_Init(void);
void LCD_Print(const char* my_string);
void LCD_SetCursorPos(uint8_t x, uint8_t y);
void LCD_Clear(void);
void LCD_Home(void);
static void LCD_Write4bits(unsigned char data, unsigned char control);
static void LCD_set_control(unsigned char data, bool par);
static void LCD_Cmd(unsigned char command);
static void LCD_Data(unsigned char data);
static void PIN_init(GPIO_TypeDef* GPIOx, uint16_t pin_no, uint16_t mode);
static void PIN_high(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void PIN_low(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void LCD_set_data(unsigned char command);
static void delay_micro(int n);
static void delay_milli(int n);

void LCD_Init(void) {
    RCC->AHB1ENR |=  (1 << 0);	
	RCC->AHB1ENR |=  (1 << 1);
	RCC->AHB1ENR |=  (1 << 2);

    PIN_init(GPIOB, 8, 0x01); //B8 -> RS (LSB)
	PIN_init(GPIOB, 9, 0x01); //B9 -> RW
	PIN_init(GPIOA, 5, 0x01); //A5 -> EN
	PIN_init(GPIOA, 9, 0x01); //A9 -> D4
	PIN_init(GPIOC, 7, 0x01); //C7 -> D5
	PIN_init(GPIOB, 6, 0x01); //B6 -> D6
	PIN_init(GPIOA, 7, 0x01); //A7 -> D7 (MSB)

	LCD_Cmd(LCD_FUNCTIONSET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS);		
	LCD_Cmd(LCD_ENTRYMODESET | LCD_AUTOINCREMENT | LCD_NOSHIFT);		
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON);		
	LCD_Clear();	
}

void LCD_Print(const char* my_string) {
    uint8_t len = strlen(my_string);
    while (len > 0) {
        LCD_Data(*my_string++);
        delay_milli(1);  
        len--;
    }	
	delay_milli(500);
}

void LCD_SetCursorPos(uint8_t x, uint8_t y) {
	uint8_t ddram_offset[] = { 0x00, 0x40 };
	LCD_Cmd(LCD_SET_DDRAM_ADDR | (x + ddram_offset[y]));	
	delay_micro(40);
}

void LCD_Clear() {
	LCD_Cmd(LCD_CLEARDISPLAY);
	delay_milli(2); 
}

void LCD_Home() {
	LCD_Cmd(LCD_RETURNHOME);  
	delay_milli(2);
}

static void LCD_Write4bits(unsigned char data, unsigned char control) {
    data &= 0xF0;
    control &= 0x0F;

	LCD_set_data(data | control);
    LCD_set_data(data | control | EN);

    delay_micro(1);

    LCD_set_data(data);
}

static void LCD_Data(unsigned char data) {
	LCD_Write4bits(data & 0xF0, RS);
    LCD_Write4bits(data << 4, RS);

	delay_micro(40);
}

static void LCD_Cmd(unsigned char command) {
	LCD_Write4bits(command & 0xF0, 0);
	LCD_Write4bits(command << 4, 0);
 	
	if(command < 4) {
		delay_milli(2);
	} else {
		delay_milli(40);
	}
}


static void PIN_init(GPIO_TypeDef* GPIOx, uint16_t pin_no, uint16_t mode) 
{
	GPIOx->MODER |= ( mode << (2 * pin_no) );	
	GPIOx->OTYPER |= ( 0x00 << (pin_no) );   
	GPIOx->OSPEEDR |= ( 0x03 << (2 * pin_no) ); 
	GPIOx->PUPDR |= ( 0x00 << (2 * pin_no) ); 
}

static void PIN_high(GPIO_TypeDef* GPIOx, uint16_t pin_no) 
{
	GPIOx->ODR |= ( 1 << pin_no );
}

static void PIN_low(GPIO_TypeDef* GPIOx, uint16_t pin_no) 
{
	GPIOx->ODR &= ~( 1 << pin_no );
}

static void LCD_set_data(unsigned char command)
{		
	bool _D7 = (command >> 7) & 0x01;
	bool _D6 = (command >> 6) & 0x01;
	bool _D5 = (command >> 5) & 0x01;
	bool _D4 = (command >> 4) & 0x01;
	bool _EN = (command >> 2) & 0x01;
	bool _RW = (command >> 1) & 0x01;
	bool _RS = (command >> 0) & 0x01;
	
	if (_D7 == 0)
		PIN_low(GPIOA, 7);
	else
		PIN_high(GPIOA, 7);
	
	if (_D6 == 0)
		PIN_low(GPIOB, 6);
	else
		PIN_high(GPIOB, 6);

	if (_D5 == 0)
		PIN_low(GPIOC, 7);
	else
		PIN_high(GPIOC, 7);

	if (_D4 == 0)
		PIN_low(GPIOA, 9);
	else
		PIN_high(GPIOA, 9);

	if (_EN == 0)
		PIN_low(GPIOA, 5);
	else
		PIN_high(GPIOA, 5);

	if (_RW == 0)
		PIN_low(GPIOB, 9);
	else
		PIN_high(GPIOB, 9);

	if (_RS == 0)
		PIN_low(GPIOB, 8);
	else
		PIN_high(GPIOB, 8);
}	

static void delay_micro(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3; j++)
	  {}
}

static void delay_milli(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3180; j++)
	  {}
}

#endif /* INC_DRV_LCD_4BITS_H_ */
