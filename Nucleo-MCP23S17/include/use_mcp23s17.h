#ifndef _USE_MCP23S17_
#define _USE_MCP23S17_

#include "stm32f401xe.h"
#include "stm32f4xx.h"

#define GPIOA_PIN_5      5
#define GPIOA_PIN_6      6
#define GPIOA_PIN_7      7
#define GPIOB_PIN_6	 6

#define SPI_CLK_PIN   GPIOA_PIN_5 
//#define SPI_MISO_PIN  GPIOA_PIN_6 
#define SPI_MOSI_PIN  GPIOA_PIN_7
#define SPI_CS_PIN    GPIOB_PIN_6

#define GPIO_PIN_AF5_SPI1   0x05

#define GPIO_PIN_ALT_FUN_MODE                          ( (uint32_t)0x02)
#define GPIO_PIN_OUTPUT_MODE                           ( (uint32_t)0x01)
#define GPIO_PIN_OP_TYPE_PUSHPULL                      ( (uint32_t)0x00 )
#define GPIO_PIN_PULL_DOWN                             ( (uint32_t)0x11 )
#define GPIO_PIN_PULL_UP                               ( (uint32_t)0x01 )
#define GPIO_PIN_SPEED_MEDIUM                          ( (uint32_t)0x01 )

#define _HAL_RCC_GPIOA_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 0) )
#define _HAL_RCC_GPIOB_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 1) )

#define _HAL_RCC_SPI1_CLK_ENABLE()        (RCC->APB2ENR |=  (1 << 12) )

#define SPI_CR1_BR_PCLK_DIV_2   							( ( uint32_t)  0 << 3 )
#define SPI_CR1_BR_PCLK_DIV_4   							( ( uint32_t)  1 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_8   							( ( uint32_t)  2 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_16  							( ( uint32_t)  3 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_32  							( ( uint32_t)  4 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_64  							( ( uint32_t)  5 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_128  							( ( uint32_t)  6 << 3 ) 
#define SPI_CR1_BR_PCLK_DIV_256  							( ( uint32_t)  7 << 3 )

#define RESET  0 
#define SET  !RESET
#define PIN_LOW 0
#define PIN_HIGH 1

#define WRITE 0
#define READ  1

#define FIXED_BITS 0x04
#define A2 0
#define A1 0
#define A0 0
#define RW WRITE

#define IOCON_BANK_0_IODIRA 0x00
#define IOCON_BANK_0_IODIRB 0x01
#define IOCON_BANK_0_IOCON  0x0A
#define IOCON_BANK_0_GPIOA  0x12
#define IOCON_BANK_0_GPIOB  0x13
#define IOCON_BANK_0_OLATA  0x14
#define IOCON_BANK_0_OLATB  0x15

#define IOCON_BANK_1_IODIRA 0x00
#define IOCON_BANK_1_IODIRB 0x10
#define IOCON_BANK_1_IOCON  0x05
#define IOCON_BANK_1_GPIOA  0x09
#define IOCON_BANK_1_GPIOB  0x19
#define IOCON_BANK_1_OLATA  0x0A
#define IOCON_BANK_1_OLATB  0x1A

void SPI_Transmit(SPI_TypeDef* SPIx, uint16_t data) {
	if (!(SPIx->CR1 & SPI_CR1_SPE)) {SPIx->CR1 |= SPI_CR1_SPE;}  
	while ((SPIx->SR & SPI_SR_TXE) == 0 && (SPIx->SR & SPI_SR_BSY));  
	SPIx->DR = data; 
	while ((SPIx->SR & SPI_SR_BSY)); 
}

uint8_t SPI_Receive(SPI_TypeDef* SPIx) {
	if (!(SPIx->CR1 & SPI_CR1_SPE)) {SPIx->CR1 |= SPI_CR1_SPE;}  
	while ((SPIx->SR & SPI_SR_RXNE) == 0 && (SPIx->SR & SPI_SR_BSY)); 	
	return SPIx->DR; 
}

void SET_CS(uint8_t state) {
	if (state) {
		GPIOB->ODR |=  (1 << SPI_CS_PIN);
	} else {
		GPIOB->ODR &=  ~(1 << SPI_CS_PIN);
	}
}

void delay( )
{
	uint32_t cnt = 4000000;
	while(cnt--);
}
																													
void gpio_init(void) {
	_HAL_RCC_GPIOA_CLK_ENABLE();
	_HAL_RCC_GPIOB_CLK_ENABLE();

	GPIOA->AFR[0] |= (GPIO_PIN_AF5_SPI1 << ((SPI_CLK_PIN) * 4 ));
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * SPI_CLK_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * SPI_CLK_PIN));
	GPIOA->OTYPER |= (GPIO_PIN_OP_TYPE_PUSHPULL << SPI_CLK_PIN);
	GPIOA->PUPDR |= (GPIO_PIN_PULL_DOWN << (2 * SPI_CLK_PIN));

	#ifdef SPI_MISO_PIN
	GPIOA->AFR[0] |= (GPIO_PIN_AF5_SPI1 << ((SPI_MISO_PIN) * 4 ));
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * SPI_MISO_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * SPI_MISO_PIN));
	GPIOA->OTYPER |= (GPIO_PIN_OP_TYPE_PUSHPULL << SPI_MISO_PIN);
	GPIOA->PUPDR |= (GPIO_PIN_PULL_DOWN << (2 * SPI_MISO_PIN));	
	#endif

	GPIOA->AFR[0] |= (GPIO_PIN_AF5_SPI1 << ((SPI_MOSI_PIN) * 4 ));
	GPIOA->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * SPI_MOSI_PIN));
	GPIOA->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * SPI_MOSI_PIN));
	GPIOA->OTYPER |= (GPIO_PIN_OP_TYPE_PUSHPULL << SPI_MOSI_PIN);
	GPIOA->PUPDR |= (GPIO_PIN_PULL_UP << (2 * SPI_MOSI_PIN));	

	GPIOB->MODER   |= (GPIO_PIN_OUTPUT_MODE << ( 2 * SPI_CS_PIN));
	GPIOB->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * SPI_CS_PIN));
	GPIOB->OTYPER |= (GPIO_PIN_OP_TYPE_PUSHPULL << SPI_CS_PIN);
	GPIOB->PUPDR |= (GPIO_PIN_PULL_DOWN << (2 * SPI_CS_PIN));	
	GPIOB->ODR |=  (1 << SPI_CS_PIN);		
}

void spi_init(void) {
	_HAL_RCC_SPI1_CLK_ENABLE();

	SPI1->CR1 &= ~SPI_CR1_SPE;	
	SPI1->CR1 &= ~SPI_CR1_CPHA; 
	SPI1->CR1 &= ~SPI_CR1_CPOL;	
	SPI1->CR1 |= SPI_CR1_MSTR;	
	SPI1->CR1 |= SPI_CR1_DFF;  
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;	
	SPI1->CR1 |= ( SPI_CR1_SSM | (1 << 8) ); 
	SPI1->CR1 |= SPI_CR1_BR_PCLK_DIV_2; 
	SPI1->CR1 |= SPI_CR1_BIDIOE; 
	#ifdef SPI_MISO_PIN
		SPI1->CR1 &= ~SPI_CR1_BIDIMODE; 
	#endif
	SPI1->CR1 |= SPI_CR1_SPE;	
}

void mcp23s17_init() {
	uint8_t CTRL_BYTE;
	CTRL_BYTE = ((FIXED_BITS << 4) | (A2 << 3) | (A1 << 2) | (A0 << 1) | (RW << 0));

	SET_CS(PIN_LOW);
	SPI_Transmit(SPI1, (CTRL_BYTE << 8) | IOCON_BANK_0_IOCON);
	SPI_Transmit(SPI1, 0x2828);
	SET_CS(PIN_HIGH);

	SET_CS(PIN_LOW);
	SPI_Transmit(SPI1,(CTRL_BYTE << 8) | IOCON_BANK_0_IODIRA);
	SPI_Transmit(SPI1, 0x0000);
	SET_CS(PIN_HIGH);
	delay();
	
	SET_CS(PIN_LOW);
	SPI_Transmit(SPI1,(CTRL_BYTE << 8) | IOCON_BANK_0_GPIOA);
	
	while(1) {							  
		SPI_Transmit(SPI1, 0xABCD); 									
		delay();
	
		SPI_Transmit(SPI1, 0x0000);				
		delay();
	}
}

#endif
