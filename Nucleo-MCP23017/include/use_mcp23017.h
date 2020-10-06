#ifndef _USE_MCP23017_
#define _USE_MCP23017_

#include "stm32f401xe.h"
#include "stm32f4xx.h"

#define GPIOB_PIN_9 	9
#define GPIOB_PIN_8 	8

#define I2C1_SCL_PIN 	GPIOB_PIN_8
#define I2C1_SDA_PIN 	GPIOB_PIN_9

#define GPIO_PIN_AF4_I2C1   0x04

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

#define _HAL_RCC_GPIOB_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 1) )
#define _HAL_RCC_I2C1_CLK_ENABLE()	  (RCC->APB1ENR |=  (1 << 21))

#define I2C_PERIPHERAL_CLK_FREQ_8MHZ 	   ( (uint32_t)0x08 )
#define I2C_PERIPHERAL_CLK_FREQ_16MHZ 	   ( (uint32_t)0x0F )

#define I2C_CLOCK_STANDARD         100000  

#define SLAVE_ADDRESS 0x20
#define SLAVE_OWN_ADDRESS 0x53
#define INPUT_MASK 0x1U

#define WRITE 0
#define READ  1

#define FIXED_BITS 0x04
#define A2 0
#define A1 0
#define A0 0

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

void GPIO_Init()
{
    _HAL_RCC_GPIOB_CLK_ENABLE();
	  		
    GPIOB->AFR[1]  |= (GPIO_PIN_AF4_I2C1 << ((I2C1_SCL_PIN % 8) * 4 ));  	
    GPIOB->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * I2C1_SCL_PIN));
    GPIOB->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * I2C1_SCL_PIN));
    GPIOB->OTYPER  |= (GPIO_PIN_OP_TYPE_OPENDRAIN << I2C1_SCL_PIN);
    GPIOB->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * I2C1_SCL_PIN));

    GPIOB->AFR[1]  |= (GPIO_PIN_AF4_I2C1 << ((I2C1_SDA_PIN % 8) * 4 )); 	
    GPIOB->MODER   |= (GPIO_PIN_ALT_FUN_MODE << ( 2 * I2C1_SDA_PIN));
    GPIOB->OSPEEDR |= (GPIO_PIN_SPEED_MEDIUM << (2 * I2C1_SDA_PIN));
    GPIOB->OTYPER  |= (GPIO_PIN_OP_TYPE_OPENDRAIN << I2C1_SDA_PIN);
    GPIOB->PUPDR   |= (GPIO_PIN_PULL_UP << (2 * I2C1_SDA_PIN));
}

void I2C_Init()
{
    _HAL_RCC_I2C1_CLK_ENABLE();

    I2C1->CR1 &= ~(I2C_CR1_PE);

    I2C1->OAR1 &= ~(I2C_OAR1_ADDMODE);

    I2C1->CR2 |= (I2C_PERIPHERAL_CLK_FREQ_8MHZ & 0x3F);	

    I2C1->TRISE  &= ~(0x3F);
    I2C1->TRISE |= I2C_PERIPHERAL_CLK_FREQ_8MHZ + 1;

    I2C1->CCR |= ( I2C_PERIPHERAL_CLK_FREQ_8MHZ * 1000000) / (I2C_CLOCK_STANDARD << 1);

    I2C1->OAR1 &= ~I2C_OAR1_ADDMODE;

    I2C1->CR1 |= I2C_CR1_ACK;

    I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;
    
    I2C1->OAR1 &= ~( 0x7f << 1);
    uint32_t own_address = SLAVE_OWN_ADDRESS;
    I2C1->OAR1 |=  (own_address << 1); 
    
    I2C1->CR1 |= I2C_CR1_PE;
}

void delay( )
{
	uint32_t cnt = 4000000;
	while(cnt--);
}

void I2C_Transmit(I2C_TypeDef *I2Cx, uint8_t address, uint8_t *pdata) {
    if (!(I2Cx->CR1 & I2C_CR1_PE)) { I2Cx->CR1 |= I2C_CR1_PE; }	
    
    while(I2Cx->SR2 & I2C_SR2_BUSY);  
    
    I2Cx->CR1 &= ~I2C_CR1_POS;  
    I2Cx->CR1 |= I2C_CR1_START; 

    while(! (I2Cx->SR1 & I2C_SR1_SB ) );
    I2Cx->DR = address;
    
    while ( ! (I2Cx->SR1 & I2C_SR1_ADDR ) );
    uint16_t val;
    val = I2Cx->SR1;
    val = I2Cx->SR2;

    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata++);
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata++);
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata);
    
    while ((I2Cx->SR1 & I2C_SR1_TXE) == 0);
    I2Cx->CR1 |= I2C_CR1_STOP;
}

uint16_t I2C_Receive(I2C_TypeDef* I2Cx, uint8_t w_address, uint8_t reg_address, uint8_t r_address)
{
    uint8_t pdata[2];
  
    if (!(I2Cx->CR1 & I2C_CR1_PE)) { I2Cx->CR1 |= I2C_CR1_PE; }	
    
    while(I2Cx->SR2 & I2C_SR2_BUSY);  
    
    I2Cx->CR1 &= ~I2C_CR1_POS;  
    I2Cx->CR1 |= I2C_CR1_START; 

    while(! (I2Cx->SR1 & I2C_SR1_SB ) );
    I2Cx->DR = w_address;
    
    while ( ! (I2Cx->SR1 & I2C_SR1_ADDR ) );
    uint16_t val;
    val = I2Cx->SR1;
    val = I2Cx->SR2;
    
    while ((I2Cx->SR1 & I2C_SR1_TXE) == 0);
    I2Cx->DR = reg_address;
    
    while ((I2Cx->SR1 & I2C_SR1_TXE) == 0);   
     
    I2Cx->CR1 &= ~I2C_CR1_POS;  
    I2Cx->CR1 |= I2C_CR1_ACK;  
    I2Cx->CR1 |= I2C_CR1_START; 

    while(! (I2Cx->SR1 & I2C_SR1_SB ) );
    I2Cx->DR = r_address;

    while ( ! (I2Cx->SR1 & I2C_SR1_ADDR ) ); 

    I2Cx->CR1 &= ~(I2C_CR1_ACK);
    I2Cx->CR1 |= I2C_CR1_POS; 
    val = I2Cx->SR1;
    val = I2Cx->SR2;
    
    while ((I2Cx->SR1 & I2C_SR1_BTF) == 0);
    I2Cx->CR1 |= I2C_CR1_STOP;
    pdata[0] = I2C1->DR;
    pdata[1] = I2C1->DR;
    
    return (pdata[1] << 8) + pdata[0];
}

void mcp23017_init(void) {
  uint8_t pdata[3];
  uint16_t volatile data = 0x0U;
	
  uint8_t CTRL_BYTE_W, CTRL_BYTE_R;
  CTRL_BYTE_W = ((FIXED_BITS << 4) | (A2 << 3) | (A1 << 2) | (A0 << 1) | (WRITE << 0));
  CTRL_BYTE_R = ((FIXED_BITS << 4) | (A2 << 3) | (A1 << 2) | (A0 << 1) | (READ << 0));
  
  pdata[0] = IOCON_BANK_0_IOCON;
  pdata[1] = 0x08; 
  pdata[2] = 0x08;
  I2C_Transmit(I2C1, CTRL_BYTE_W, pdata);
	
  pdata[0] = IOCON_BANK_0_IODIRA;
  pdata[1] = INPUT_MASK; 
  pdata[2] = 0x00;
  I2C_Transmit(I2C1, CTRL_BYTE_W, pdata);

  delay();
	
  while(1) {
	  if (data & INPUT_MASK) {
              pdata[0] = IOCON_BANK_0_GPIOA;
              pdata[1] = 0xAB; //GPIOA
              pdata[2] = 0xCD; //GPIOB
              I2C_Transmit(I2C1, CTRL_BYTE_W, pdata);
          }
	  
	  delay();
           
          pdata[0] = IOCON_BANK_0_GPIOA;
          pdata[1] = 0x00; //GPIOA
          pdata[2] = 0x00; //GPIOB
          I2C_Transmit(I2C1, CTRL_BYTE_W, pdata);
			
	  delay();
	  
	  data = I2C_Receive(I2C1, CTRL_BYTE_W, IOCON_BANK_0_GPIOA, CTRL_BYTE_R);
          }
}

#endif
