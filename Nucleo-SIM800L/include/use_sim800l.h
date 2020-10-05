#ifndef _USE_SIM800L_
#define _USE_SIM800L_

#include "stm32f401xe.h"
#include "stm32f4xx.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define GPIOA_PIN_2		2
#define GPIOA_PIN_3   3
#define GPIOA_PIN_9   9
#define GPIOA_PIN_10  10
#define USART2_TX_PIN GPIOA_PIN_2
#define USART2_RX_PIN GPIOA_PIN_3
#define USART1_TX_PIN GPIOA_PIN_9
#define USART1_RX_PIN GPIOA_PIN_10

#define GPIO_PIN_AF7_USART2 0x07
#define GPIO_PIN_AF7_USART1 0x07

#define GPIO_PIN_ALT_FUN_MODE             ( (uint32_t)0x02 )
#define GPIO_PIN_OUTPUT_MODE              ( (uint32_t)0x01 )
#define GPIO_PIN_INPUT_MODE		  ( (uint32_t)0x00 )
#define GPIO_PIN_OP_TYPE_PUSHPULL         ( (uint32_t)0x00 )
#define GPIO_PIN_OP_TYPE_OPENDRAIN        ( (uint32_t)0x01 )
#define GPIO_PIN_NO_PULL_PUSH             ( (uint32_t)0x00 )
#define GPIO_PIN_PULL_UP                  ( (uint32_t)0x01 )
#define GPIO_PIN_PULL_DOWN                ( (uint32_t)0x11 )
#define GPIO_PIN_SPEED_MEDIUM             ( (uint32_t)0x01 )
#define GPIO_PIN_SPEED_LOW                ( (uint32_t)0x00 )

#define _HAL_RCC_GPIOA_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 0) )
#define _HAL_RCC_USART2_CLK_ENABLE()      (RCC->APB1ENR |=  (1 << 17))
#define _HAL_RCC_USART1_CLK_ENABLE()      (RCC->APB2ENR |=  (1 << 4) )

#define USART_MAX_DELAY    10000
#define USART_BUFFER_SIZE  UINT8_MAX  
#define VCP                USART2
#define SIM                USART1
#define ECHO               1
#define NOECHO             !ECHO
#define SIM_ENDING_CHAR    '\0'
#define VCP_ENDING_CHAR    '\r'

#define vcp_scanf(x)       uscanf(VCP, (uint8_t*)x, ECHO, VCP_ENDING_CHAR)
#define vcp_printf(x, ...) uprintf(VCP, x, ##__VA_ARGS__)

#define sim_scanf(x)       uscanf(SIM, (uint8_t*)x, ECHO, SIM_ENDING_CHAR)
#define sim_printf(x, ...) uprintf(SIM, x, ##__VA_ARGS__)

void GPIO_Init()
{
	_HAL_RCC_GPIOA_CLK_ENABLE();

	GPIOA->AFR[0]  |= (GPIO_PIN_AF7_USART2 << ((USART2_TX_PIN) * 4 ));
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * USART2_TX_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * USART2_TX_PIN));
	GPIOA->OTYPER  |= (GPIO_PIN_OP_TYPE_PUSHPULL << USART2_TX_PIN);
	GPIOA->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * USART2_TX_PIN));

    	GPIOA->AFR[0]  |= (GPIO_PIN_AF7_USART2 << ((USART2_RX_PIN) * 4 ));
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * USART2_RX_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * USART2_RX_PIN));
	GPIOA->OTYPER  |= (GPIO_PIN_OP_TYPE_PUSHPULL << USART2_RX_PIN);
	GPIOA->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * USART2_RX_PIN));
  
    	GPIOA->AFR[1]  |= (GPIO_PIN_AF7_USART1 << ((USART1_TX_PIN % 8) * 4 )); 
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * USART1_TX_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * USART1_TX_PIN));
	GPIOA->OTYPER  |= (GPIO_PIN_OP_TYPE_PUSHPULL << USART1_TX_PIN);
	GPIOA->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * USART1_TX_PIN));
    
    	GPIOA->AFR[1]  |= (GPIO_PIN_AF7_USART1 << ((USART1_RX_PIN % 8) * 4 )); 
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * USART1_RX_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * USART1_RX_PIN));
	GPIOA->OTYPER  |= (GPIO_PIN_OP_TYPE_PUSHPULL << USART1_RX_PIN);
	GPIOA->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * USART1_RX_PIN));
}

void USART_init()
{
	_HAL_RCC_USART2_CLK_ENABLE();
	_HAL_RCC_USART1_CLK_ENABLE();
    
	USART2->BRR = 0x8B;
	
	USART2->CR1 &= ~(USART_CR1_M);
	USART2->CR2 &= ~(USART_CR2_STOP);

	USART2->CR1 |= USART_CR1_TE; 	
    	USART2->CR1 |= USART_CR1_RE;  
	USART2->CR1 |= USART_CR1_UE;	
  
	USART1->BRR = 0x8B;

	USART1->CR1 &= ~(USART_CR1_M);
	USART1->CR2 &= ~(USART_CR2_STOP);

	USART1->CR1 |= USART_CR1_TE; 	
   	USART1->CR1 |= USART_CR1_RE;  
	USART1->CR1 |= USART_CR1_UE;
}

void USART_Transmit(USART_TypeDef *USARTx, uint8_t* str)
{
	while (!(USARTx->SR & USART_SR_TXE));	
	USARTx->DR = *str;
}

uint8_t USART_Receive(USART_TypeDef *USARTx, bool *timeout)
{
    	uint16_t t = 0;
    	while (!(USARTx->SR & USART_SR_RXNE)) { if (t >= USART_MAX_DELAY) {*timeout = true; break;} if (USARTx == SIM) t++; }
    	return USARTx->DR;
}

void uprintf(USART_TypeDef *USARTx, char* format, ...)
{
    	char buffer[USART_BUFFER_SIZE];
    	uint16_t len;
    	va_list args;
    	va_start(args, format);
    	vsprintf(buffer, format, args);
    	len = strlen(buffer);
    	for (uint16_t cnt=0; cnt < len; cnt++) {
		USART_Transmit(USARTx, (uint8_t*)&buffer[cnt]);
    	}
    	va_end(args);
}

void uscanf(USART_TypeDef *USARTx, uint8_t *pdata, bool do_echo, char end_char)
{
   	char buffer[USART_BUFFER_SIZE];
    	uint16_t i;
    	bool timeout = false;
    	for (i = 0; i <= USART_BUFFER_SIZE-1; i++) { buffer[i] = '\0'; }
    	i = 0;
    	do {
      		if (!timeout) { buffer[i] = USART_Receive(USARTx, &timeout); } 
      		if (do_echo) { uprintf(VCP, "%c", buffer[i]); } 
      		*(pdata++) = buffer[i++]; 
      		if (buffer[i-1] == end_char) { timeout = true; }
    	} while (buffer[i-1] != end_char);  
    	if (USARTx == VCP) uprintf(VCP, "\r\n");    
}

#endif
