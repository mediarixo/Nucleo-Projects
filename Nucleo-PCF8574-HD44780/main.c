#include "pcf8574_driver.h"

int main(void) {
	LCD_Init();
	LCD_Clear();         
	
	LCD_SetCursorPos(1,0);   
	LCD_Print("*WELCOME HOME*");
	
	LCD_SetCursorPos(1,1);
	LCD_Print("HITACHI DRIVER"); 
			
	while(1);
}
