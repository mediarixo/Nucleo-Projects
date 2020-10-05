#include "stm32f4xx.h"                  
#include "../include/use_mcp23s17.h"

int main() {	
	gpio_init();	
	spi_init();	
	mcp23s17_init();

	while(1);
}
