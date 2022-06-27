#include "stm32f4xx.h"                  // Device header
#include "drv_mcp23017.h"

int main() {
  GPIO_Init();
  I2C_Init();
  mcp23017_init();
  
  while(1);
}
