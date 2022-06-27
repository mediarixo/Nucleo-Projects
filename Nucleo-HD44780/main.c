#define USE_4BITS

#ifndef USE_8BITS
#include "drv_lcd_4bits.h"
#else
#include "drv_lcd_8bits.h"
#endif

int main()
{
    LCD_Init();    
    LCD_Print("Welcome HITACHI");
    LCD_SetCursorPos(0,1);
    LCD_Print("I LOVE 4 BITS");
    
    while(1) {
    }
}
