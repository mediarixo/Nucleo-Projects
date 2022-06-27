#include "pcf8574_driver.h"

void LCD_Init() {
	Setup_driver();
	LCD_Cmd(LCD_FUNCTIONSET | LCD_8BIT_MODE | LCD_2LINE | LCD_5x8DOTS);		
	LCD_Cmd(LCD_ENTRYMODESET | LCD_AUTOINCREMENT | LCD_NOSHIFT);		
	LCD_Cmd(LCD_DISPLAYCONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);		
	LCD_SetBacklight(ON);
	LCD_Home();	
}

void LCD_Clear(){
	LCD_Cmd(LCD_CLEARDISPLAY);
	delay_milli(2); 
}

void LCD_Home(){
	LCD_Cmd(LCD_RETURNHOME);  
	delay_milli(2);
}

void LCD_Print(const char *str)
{
	uint8_t len = strlen(str);
	while (len > 0) {
		LCD_Data(*str++);
		len--;
	}
}

void LCD_SetCursorPos(uint8_t x, uint8_t y) {
	x += (y < 1) ? 0x00 : 0x40;
	LCD_Cmd(LCD_SET_DDRAM_ADDR | x);
	delay_micro(40);	
}

void LCD_SetBacklight(bool state) {
	LCD_Backlight = (state == OFF) ? LCD_NOBACKLIGHT : LCD_BACKLIGHT;
	LCD_Cmd(0);
}

static void LCD_write4bits(uint8_t value) {
	uint8_t data;
	value |= LCD_Backlight;
	data = value;
  	I2C_SendData(I2C1, &data, 1, LCD_ADDR);
	
	// pulse EN high for around 1us
	data = value | EN; 
  	I2C_SendData(I2C1, &data, 1, LCD_ADDR);
	delay_micro(1);		
	
	// pulse EN back to low
	data = value;
  	I2C_SendData(I2C1, &data, 1, LCD_ADDR);
	delay_micro(50);		
}

static void delay_milli(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3180; j++)
	  {}
}

static void delay_micro(int n)
{
	int i, j;
	for (i=0; i<n; i++)
	 for (j=0; j<3; j++)
	  {}
}

static void LCD_Cmd(uint8_t command) {
	LCD_write4bits(command & 0xF0);		
	LCD_write4bits(command << 4);
}

static void LCD_Data(uint8_t data) {
	LCD_write4bits((data & 0xF0) | RS);		
	LCD_write4bits((data << 4) | RS);
}

static void Setup_driver(void) {
	GPIO_Init(GPIOB_PIN_NO_8); //PB8(D15) -> I2C1_SCL
	GPIO_Init(GPIOB_PIN_NO_9); //PB9(D14) -> I2C1_SDA
	I2C_Init(I2C1);
}
