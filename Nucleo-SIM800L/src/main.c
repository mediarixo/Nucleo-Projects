#include "../include/use_sim800l.h"
#include "stm32f4xx.h"
#include "stm32f401xe.h"

int main(void) 
{
    GPIO_Init();
    USART_init();
  
    uint8_t buffer[USART_BUFFER_SIZE];

    while(1) {  
      for (uint16_t i = 0; i <= USART_BUFFER_SIZE-1; i++) { buffer[i] = '\0'; }
      vcp_printf("Enter cmd: ");
      vcp_scanf(buffer);    
      vcp_printf("Executing command... %s\r\n", buffer);
      sim_printf("%s\r", buffer);
      sim_scanf(buffer);
    }
}


