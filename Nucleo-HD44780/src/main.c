#include "stm32f4xx.h"                  
#include <stdbool.h>
#include <stdint.h>

#include "../include/use_lcd_8bits.h"

int main()
{
    LCD_init();
    LCD_Cmd(0x01);		
    delay_milli(500);	
	
    LCD_Data('H');
    delay_milli(1);  	
    LCD_Data('E');
    delay_milli(1);    
    LCD_Data('L');
    delay_milli(1);    
    LCD_Data('L');
    delay_milli(1);    
    LCD_Data('O');

    delay_milli(500);

    while(1);

}
