#include "pcf8574_driver.h"

int main(void) {
	LCD_Init();
	LCD_Clear();         
	
	LCD_SetCursorPos(1,0);   
	LCD_Print("*WELCOME HOME*");
	
	LCD_SetCursorPos(1,1);
	LCD_Print("HITACHI DRIVER"); 

	LCD_SetCursorPos(1,2);
	LCD_Print("TO THE NEW"); 
	
	LCD_SetCursorPos(3,3);
	LCD_Print("LCD MODULE!!!"); 
	
	while(1);
}
