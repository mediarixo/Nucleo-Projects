#ifndef INC_DRV_PCF8574_H_
#define INC_DRV_PCF8574_H_

#include "stm32f401ret6.h"
#include <string.h>
#include <stdbool.h>

//comment out next line if using other version chip
#define CHIP_PCF8574A

#ifdef CHIP_PCF8574A
#define LCD_ADDR	0x3F
#else
#define LCD_ADDR	0x27
#endif

#define RS  1                           
#define RW  2                           
#define EN  4          

#define ON  1
#define OFF 0

#define LCD_BACKLIGHT           0x08           
#define LCD_NOBACKLIGHT         0x00			

#define LCD_FUNCTIONSET     	0x20
#define LCD_8BIT_MODE 			0x10	
#define LCD_2LINE 				0x08	
#define LCD_5x8DOTS 			0x00

#define LCD_ENTRYMODESET 	    0x04
#define LCD_AUTOINCREMENT 		0x02	
#define LCD_NOSHIFT             0x00

#define LCD_DISPLAYCONTROL      0x08
#define LCD_DISPLAY_ON 			0x04	
#define LCD_DISPLAY_OFF 		0x00
#define LCD_CURSOR_ON 			0x02	
#define LCD_CURSOR_OFF 			0x00
#define LCD_BLINK_ON 			0x01	
#define LCD_BLINK_OFF 			0x00

#define LCD_CLEARDISPLAY 	    0x01
#define LCD_RETURNHOME 		    0x02
#define LCD_SET_DDRAM_ADDR 	    0x80

static uint8_t LCD_Backlight;

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Print(const char *str);
void LCD_SetCursorPos(uint8_t x, uint8_t y);
void LCD_SetBacklight(bool state);
static void LCD_write4bits(uint8_t value);
static void delay_milli(int n);
static void delay_micro(int n);
static void LCD_Cmd(uint8_t command);
static void LCD_Data(uint8_t data);
static void Setup_driver(void);

#endif /* INC_DRV_PCF8574_H_ */
