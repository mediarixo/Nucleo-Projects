#include "stm32f401ret6.h"
#include "sim800l_driver.h"
#include <string.h>
#include <stdlib.h>

#define USART_BUFFER_SIZE  UINT8_MAX 

USART_Handle_t *VCPHandle, *SIMHandle;


void USART_GPIOInits(void) {
	GPIO_Handle_t USARTPins;
	USARTPins.pGPIOx = GPIOA;
	USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	USARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PUSHPULL;
	USARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PULLUP;
	USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0x7;
	USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//PA2(D1) -> USART2_TX
	USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&USARTPins);

	//PA3(D0) -> USART2_RX
	USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&USARTPins);

	//PA9(D8) -> USART1_TX
	USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&USARTPins);

	//PA10(D2) -> USART1_RX
	USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&USARTPins);
}

void USART_Inits(void) {
	VCPHandle = malloc(sizeof(USART_Handle_t));
	VCPHandle->pUSARTx = USART2;
	VCPHandle->USART_Config.USART_Baud = USART_STD_BAUD_9600;
	VCPHandle->USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	VCPHandle->USART_Config.USART_Mode = USART_MODE_TXRX;
	VCPHandle->USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	VCPHandle->USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	VCPHandle->USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(VCPHandle);

	SIMHandle = malloc(sizeof(USART_Handle_t));
	SIMHandle->pUSARTx = USART1;
	SIMHandle->USART_Config.USART_Baud = USART_STD_BAUD_9600;
	SIMHandle->USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	SIMHandle->USART_Config.USART_Mode = USART_MODE_TXRX;
	SIMHandle->USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	SIMHandle->USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	SIMHandle->USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(SIMHandle);

	USART_PeripheralControl(VCPHandle->pUSARTx, ENABLE);
	USART_PeripheralControl(SIMHandle->pUSARTx, ENABLE);
}

void delay() {
	uint32_t i;
	for (i = 0; i < 5000000; i++);
}

int main(void) {
	uint8_t buffer[USART_BUFFER_SIZE];

	USART_GPIOInits();
	USART_Inits();

	//phonenumber must be in the format "+ZZxxxxxxxxxx" where ZZ is the country code
	send_sms("+ZZxxxxxxxxxx","If you see this message the sim800l module works correctly!");
  	sim_printf("AT\r\n");
	sim_scanf(buffer);

	while(1) {
			memset(buffer, '\0', USART_BUFFER_SIZE);
			vcp_printf("Input a command: ");
			vcp_scanf(buffer);
			vcp_printf("Executing: %s\r\n", buffer);
			sim_printf("%s", buffer);
			sim_scanf(buffer);						
	}
}
