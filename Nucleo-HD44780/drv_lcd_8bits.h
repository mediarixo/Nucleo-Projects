#ifndef INC_DRV_LCD_8BITS_H_
#define INC_DRV_LCD_8BITS_H_

#include "stm32f401xe.h"
#include <stdbool.h>
#include <string.h>

#define NONE 0
#define OR   1

#define LCD_BACKLIGHT    		0x08           
#define LCD_NOBACKLIGHT  		0x00			

#define LCD_FUNCTIONSET     	0x20
#define LCD_8BIT_MODE 			0x10			
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
void LCD_Clear();
void LCD_Home();
static void LCD_Cmd(unsigned char command);
static void LCD_Data(unsigned char data);
static void PIN_init(GPIO_TypeDef* GPIOx, uint16_t pin_no, uint16_t mode);
static void PIN_high(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void PIN_low(GPIO_TypeDef* GPIOx, uint16_t pin_no);
static void LCD_set_control(unsigned char data, bool par);
static void LCD_set_data(unsigned char newcommand);
static void delay_micro(int n);
static void delay_milli(int n);

void LCD_Init(void)
{
	RCC->AHB1ENR |=  (1 << 0);	
	RCC->AHB1ENR |=  (1 << 1);  
	RCC->AHB1ENR |=  (1 << 2);  
	
	PIN_init(GPIOA, 5, 0x01); 
	PIN_init(GPIOA, 7, 0x01);
	PIN_init(GPIOA, 8, 0x01);
	PIN_init(GPIOA, 9, 0x01);
	PIN_init(GPIOA, 10, 0x01);
	PIN_init(GPIOB, 5, 0x01);
	PIN_init(GPIOB, 6, 0x01);
	PIN_init(GPIOB, 8, 0x01);
	PIN_init(GPIOB, 9, 0x01);
	PIN_init(GPIOB, 10, 0x01);
	PIN_init(GPIOC, 7, 0x01);
	
	LCD_Cmd(LCD_FUNCTIONSET | LCD_8BIT_MODE | LCD_2LINE | LCD_5x8DOTS);		
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

static void LCD_Data(unsigned char data)
{	
	LCD_set_control(0x20, NONE); 
	LCD_set_data(data);
	LCD_set_control(0x80, OR);   
	delay_micro(50);              
	LCD_set_control(0x00, NONE); 
	delay_micro(0);
}

static void LCD_Cmd(unsigned char command)
{
	LCD_set_control(0x00, NONE); 
	LCD_set_data(command);
	LCD_set_control(0x80, NONE); 
	delay_micro(20);							 
	LCD_set_control(0x00, NONE); 
	if (command < 4)
		delay_milli(2);
	else
		delay_micro(37);
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

static void LCD_set_control(unsigned char data, bool par)
{
	static unsigned char newdata;
	bool EN, RW, RS ;
	if (par == 1)	//OR
		newdata |= data;
	else
		newdata = data;

	EN = (newdata >> 7) & 0x01;		
	RW = (newdata >> 6) & 0x01;
	RS = (newdata >> 5) & 0x01;
		
	if (EN == 0) 
		PIN_low(GPIOA, 5); 
	else
		PIN_high(GPIOA, 5);       
	
  if (RW == 0)
		PIN_low(GPIOB, 9);       
	else
		PIN_high(GPIOB, 9);      
	
	if (RS == 0) 
		PIN_low(GPIOB, 8);       
	else
		PIN_high(GPIOB, 8);       
}

static void LCD_set_data(unsigned char command)
{		
	bool D7 = (command >> 7) & 0x01;
	bool D6 = (command >> 6) & 0x01;
	bool D5 = (command >> 5) & 0x01;
	bool D4 = (command >> 4) & 0x01;
	bool D3 = (command >> 3) & 0x01;
	bool D2 = (command >> 2) & 0x01;
	bool D1 = (command >> 1) & 0x01;
	bool D0 = (command >> 0) & 0x01;
	
	if (D7 == 0)
		PIN_low(GPIOA, 7);
	else
		PIN_high(GPIOA, 7);
	
	if (D6 == 0)
		PIN_low(GPIOB, 6);
	else
		PIN_high(GPIOB, 6);

	if (D5 == 0)
		PIN_low(GPIOC, 7);
	else
		PIN_high(GPIOC, 7);

	if (D4 == 0)
		PIN_low(GPIOA, 9);
	else
		PIN_high(GPIOA, 9);

	if (D3 == 0)
		PIN_low(GPIOA, 8);
	else
		PIN_high(GPIOA, 8);

	if (D2 == 0)
		PIN_low(GPIOB, 10);
	else
		PIN_high(GPIOB, 10);

	if (D1 == 0)
		PIN_low(GPIOB, 5);
	else
		PIN_high(GPIOB, 5);

	if (D0 == 0)
		PIN_low(GPIOA, 10);
	else
		PIN_high(GPIOA, 10);
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

#endif /* INC_DRV_LCD_8BITS_H_ */
