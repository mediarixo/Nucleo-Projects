#ifndef _DRV_MCP23017_
#define _DRV_MCP23017_

#include "stm32f401xe.h"

#define GPIOB_PIN_9 	9
#define GPIOB_PIN_8 	8

#define I2C1_SCL_PIN 	GPIOB_PIN_8
#define I2C1_SDA_PIN 	GPIOB_PIN_9


#define GPIO_PIN_AF4_I2C1   0x04

#define GPIO_PIN_ALT_FUN_MODE             ( (uint32_t)0x02 )
#define GPIO_PIN_OUTPUT_MODE              ( (uint32_t)0x01 )
#define GPIO_PIN_INPUT_MODE								( (uint32_t)0x00 )
#define GPIO_PIN_OP_TYPE_PUSHPULL         ( (uint32_t)0x00 )
#define GPIO_PIN_OP_TYPE_OPENDRAIN        ( (uint32_t)0x01 )
#define GPIO_PIN_NO_PULL_PUSH             ( (uint32_t)0x00 )
#define GPIO_PIN_PULL_UP                  ( (uint32_t)0x01 )
#define GPIO_PIN_PULL_DOWN                ( (uint32_t)0x11 )
#define GPIO_PIN_SPEED_MEDIUM             ( (uint32_t)0x01 )
#define GPIO_PIN_SPEED_LOW                ( (uint32_t)0x00 )


#define _DRV_RCC_GPIOB_CLK_ENABLE()       (RCC->AHB1ENR |=  (1 << 1) )
#define _DRV_RCC_I2C1_CLK_ENABLE()				(RCC->APB1ENR |=  (1 << 21))

#define I2C_PERIPHERAL_CLK_FREQ_16MHZ 		( (uint32_t)0x0F )

#define SLAVE_ADDRESS 0x20
#define SLAVE_OWN_ADDRESS 0x53

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

typedef enum
{
  DRV_I2C_STATE_RESET             = 0x00,  
  DRV_I2C_STATE_READY             = 0x01,  
  DRV_I2C_STATE_BUSY              = 0x02, 
  DRV_I2C_STATE_BUSY_TX           = 0x12, 
  DRV_I2C_STATE_BUSY_RX           = 0x22, 
  DRV_I2C_STATE_MEM_BUSY_TX       = 0x32, 
  DRV_I2C_STATE_MEM_BUSY_RX       = 0x42, 
  DRV_I2C_STATE_TIMEOUT           = 0x03, 
  DRV_I2C_STATE_ERROR             = 0x04  
}drv_i2c_state_t;

#define I2C_REG_CR1_POS      ((uint32_t)1 << 11)
#define I2C_REG_CR1_ACK      ((uint32_t)1 << 10)
#define I2C_ACK_ENABLE        1
#define I2C_ACK_DISABLE        0
#define I2C_REG_CR1_STOP_GEN               ((uint32_t)1 << 9)
#define I2C_REG_CR1_START_GEN            ((uint32_t)1 << 8)
#define I2C_REG_CR1_NOSTRETCH            ((uint32_t)1 << 7)
#define I2C_ENABLE_CLK_STRETCH   0
#define I2C_DISABLE_CLK_STRETCH  1
#define I2C_REG_CR1_ENABLE_I2C             ((uint32_t)1 << 0)

#define I2C_REG_CR2_BUF_INT_ENABLE       ((uint32_t) ( 1 << 10 ) )
#define I2C_REG_CR2_EVT_INT_ENABLE       ((uint32_t) ( 1 << 9 ) )
#define I2C_REG_CR2_ERR_INT_ENABLE       ((uint32_t) ( 1 << 8 ) )

#define I2C_PERIPHERAL_CLK_FREQ_2MHZ      ((uint32_t)2 )  
#define I2C_PERIPHERAL_CLK_FREQ_3MHZ      ((uint32_t)3 )  
#define I2C_PERIPHERAL_CLK_FREQ_4MHZ     ((uint32_t)4 )  
#define I2C_PERIPHERAL_CLK_FREQ_5MHZ     ((uint32_t)5 )  
#define I2C_PERIPHERAL_CLK_FREQ_6MHZ     ((uint32_t)6 )  
#define I2C_PERIPHERAL_CLK_FREQ_7MHZ     ((uint32_t)7 )  
#define I2C_PERIPHERAL_CLK_FREQ_8MHZ     ((uint32_t)8 ) 
#define I2C_PERIPHERAL_CLK_FREQ_9MHZ     ((uint32_t)9 )  
#define I2C_PERIPHERAL_CLK_FREQ_10MHZ     ((uint32_t)10 )  

#define I2C_REG_OAR1_ADDRMODE        ((uint32_t) 1 << 15 )
#define I2C_ADDRMODE_7BIT          0
#define I2C_ADDRMODE_10BI          1

#define I2C_REG_OAR1_14TH_BIT              ((uint32_t) 1 << 14 )
#define I2C_REG_OAR1_7BIT_ADDRESS_POS       1

#define I2C_REG_SR1_TIMEOUT_FLAG              ( (uint32_t) 1 << 14)
#define I2C_REG_SR1_OVR_FLAG              ( (uint32_t) 1 << 11)
#define I2C_REG_SR1_AF_FAILURE_FLAG            ( (uint32_t) 1 << 10)
#define I2C_REG_SR1_ARLO_FLAG            ( (uint32_t) 1 << 9)
#define I2C_REG_SR1_BUS_ERROR_FLAG            ( (uint32_t) 1 << 8)
#define I2C_REG_SR1_TXE_FLAG                  ( (uint32_t) 1 << 7)
#define I2C_REG_SR1_RXNE_FLAG                ( (uint32_t) 1 << 6)
#define I2C_REG_SR1_STOP_DETECTION_FLAG       ( (uint32_t) 1 << 4) 
#define I2C_REG_SR1_BTF_FLAG                 ( (uint32_t) 1 << 2)
#define I2C_REG_SR1_ADDR_FLAG                 ( (uint32_t) 1 << 1)	
#define I2C_REG_SR1_ADDR_SENT_FLAG         ( (uint32_t)1 << 1 )   
#define I2C_REG_SR1_ADDR_MATCHED_FLAG           ( (uint32_t)1 << 1 ) 	
#define I2C_REG_SR1_SB_FLAG                 ( (uint32_t) 1 << 0)	

#define I2C_REG_SR2_BUS_BUSY_FLAG             ( (uint32_t) 1 << 1)	
#define I2C_BUS_IS_BUSY                       1
#define I2C_BUS_IS_FREE                       0

#define I2C_REG_SR2_MSL_FLAG           ( (uint32_t) 1 << 0)	
#define I2C_MASTER_MODE                1
#define I2C_SLAVE_MODE                 0

#define I2C_REG_SR2_TRA_FLAG          ( (uint32_t) 1 << 2)	
#define I2C_RX_MODE                   0
#define I2C_TX_MODE                   1

#define I2C_REG_CCR_ENABLE_FM             ( (uint32_t) 1 << 15)
#define I2C_ENABLE_SM                     0 
#define I2C_ENABLE_FM                     1

#define I2C_REG_CCR_DUTY                   ( (uint32_t) 1 << 14)
#define I2C_FM_DUTY_16BY9                  1
#define I2C_FM_DUTY_2                      0

/* Clock values */
#define TM_I2C_CLOCK_STANDARD         100000  
#define TM_I2C_CLOCK_FAST_MODE        400000  
#define TM_I2C_CLOCK_FAST_MODE_PLUS   1000000
#define TM_I2C_CLOCK_HIGH_SPEED       3400000

typedef struct
{
	uint32_t ClockSpeed;       
	uint32_t DutyCycle;        
	uint32_t OwnAddress1;     
	uint32_t AddressingMode;   
	uint32_t DualAddressMode;  
	uint32_t OwnAddress2;      
	uint32_t GeneralCallMode;  
	uint32_t NoStretchMode;    
	uint32_t ack_enable; 
	uint8_t master;
	
}i2c_init_t;

typedef struct
{
	I2C_TypeDef                *Instance;  /*!< I2C registers base address     */

	i2c_init_t                  Init;       /*!< I2C communication parameters   */

	uint8_t                    *pBuffPtr;  /*!< Pointer to I2C transfer buffer */

	uint32_t                   XferSize;   /*!< I2C transfer size              */

	__IO uint32_t              XferCount;  /*!< I2C transfer counter           */

	drv_i2c_state_t            State;      /*!< I2C communication state        */
	uint32_t ErrorCode;     

}i2c_handle_t;

void GPIO_Init(void) {
	  _DRV_RCC_GPIOB_CLK_ENABLE();
	  		
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

void drv_i2c_configure_ccr(I2C_TypeDef *i2cx, uint32_t pclk, uint32_t clkspeed, uint32_t duty_cycle)
{
	uint32_t ccr = 0;
	if(clkspeed <= 100000)
	{
		ccr = ( pclk * 1000000) / (clkspeed << 1);
		
	}else
	{
		 if(duty_cycle == I2C_FM_DUTY_2)
		 {
			 ccr = ( pclk * 1000000)/(3 * clkspeed);
		 }
		 
		  if(duty_cycle == I2C_FM_DUTY_16BY9)
		 {
			ccr = ( pclk * 1000000)/(25 * clkspeed);
		 }	
	}
	
	i2cx->CCR |= ccr;
}
	

void drv_i2c_rise_time_configuration(I2C_TypeDef *i2cx,uint32_t freqrange, uint32_t ClockSpeed)
{
	uint32_t trise;
	if( ClockSpeed <= 100000)
	{
		trise = freqrange +1;
	}else
	{
		trise = (((freqrange * 300) / 1000) + 1);
	}
		i2cx->TRISE  &= ~(0x3F);
		i2cx->TRISE  |= trise;
}

void drv_i2c_clk_init(I2C_TypeDef *i2cx, uint32_t clkspeed, uint32_t duty_cycle)
{
	uint32_t pclk = I2C_PERIPHERAL_CLK_FREQ_8MHZ;
	i2cx->CR2 |= (pclk );
	drv_i2c_rise_time_configuration(i2cx,pclk, clkspeed);
	drv_i2c_configure_ccr(i2cx,pclk,clkspeed,duty_cycle);
}

void drv_i2c_set_addressing_mode(I2C_TypeDef *i2cx, uint32_t adr_mode)
{
	if(adr_mode == I2C_ADDRMODE_10BI)
		i2cx->OAR1 |= I2C_REG_OAR1_ADDRMODE;
	else 
		i2cx->OAR1 &= ~I2C_REG_OAR1_ADDRMODE;
}



void drv_i2c_manage_ack(I2C_TypeDef *i2cx, uint32_t ack_noack)
{
	if(ack_noack == I2C_ACK_ENABLE)
		i2cx->CR1 |= I2C_REG_CR1_ACK;
	else
		i2cx->CR1 &= ~I2C_REG_CR1_ACK;
}

void drv_i2c_manage_clock_stretch(I2C_TypeDef *i2cx, uint32_t no_stretch)
{
	if(no_stretch)
	{
		i2cx->CR1 |= I2C_REG_CR1_NOSTRETCH;
	}else
	{
		i2cx->CR1 &= ~I2C_REG_CR1_NOSTRETCH;
	}
}

void drv_i2c_set_own_address1(I2C_TypeDef *i2cx, uint32_t own_address)
{
	i2cx->OAR1 &= ~( 0x7f << 1);
	i2cx->OAR1 |=  (own_address << 1);
}

void drv_i2c_init(i2c_handle_t *handle)
{
	drv_i2c_clk_init(handle->Instance, handle->Init.ClockSpeed,handle->Init.DutyCycle);
	drv_i2c_set_addressing_mode(handle->Instance, handle->Init.AddressingMode);
	drv_i2c_manage_ack(handle->Instance, handle->Init.ack_enable);
	drv_i2c_manage_clock_stretch(handle->Instance,handle->Init.NoStretchMode);
	drv_i2c_set_own_address1(handle->Instance,handle->Init.OwnAddress1);
	
}

void I2C_Init(void){
  i2c_handle_t i2c_handle;
  _DRV_RCC_I2C1_CLK_ENABLE() ;
	i2c_handle.Instance = I2C1;
	i2c_handle.Init.ack_enable = I2C_ACK_ENABLE;
	i2c_handle.Init.AddressingMode = I2C_ADDRMODE_7BIT; 
	i2c_handle.Init.ClockSpeed = TM_I2C_CLOCK_STANDARD;
	i2c_handle.Init.DutyCycle = I2C_FM_DUTY_2;
	i2c_handle.Init.GeneralCallMode = 0;
	i2c_handle.Init.NoStretchMode = I2C_ENABLE_CLK_STRETCH;
	i2c_handle.Init.OwnAddress1 = SLAVE_OWN_ADDRESS;
  drv_i2c_init(&i2c_handle);
}

void delay( )
{
	uint32_t cnt = 4000000;
	while(cnt--);
}

void clear_addr_flag(I2C_TypeDef *i2cx)
{
	uint16_t val;
	
	val = i2cx->SR1;
	val = i2cx->SR2;
	(void)val;
}

uint8_t i2c_wait_untill_addr_set(I2C_TypeDef *i2cx)
{
	if (i2cx->SR1 & I2C_SR1_ADDR )
	{
		return 1 ;
	}
	return 0;
}

uint8_t i2c_wait_untill_sb_set(I2C_TypeDef *i2cx)
{
	if (i2cx->SR1 & I2C_SR1_SB )
	{
		return 1 ;
	}
	return 0;
}

uint8_t is_bus_busy(I2C_TypeDef *i2cx)
{
	if(i2cx->SR2 & I2C_SR2_BUSY)
		return 1;
	else
		return 0;
}

void I2C_Transmit(I2C_TypeDef *I2Cx, uint8_t address, uint8_t *pdata) {
    if (!(I2Cx->CR1 & I2C_CR1_PE)) { I2Cx->CR1 |= I2C_CR1_PE; }	

    while(is_bus_busy(I2C1) );
    I2C1->CR1 &= ~I2C_CR1_POS;  
    I2C1->CR1 |= I2C_CR1_START; 
    
    while(! i2c_wait_untill_sb_set(I2C1) );
    I2C1->DR = address;
    
    while ( ! i2c_wait_untill_addr_set(I2C1) );
    clear_addr_flag(I2C1);
   
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata++);
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata++);
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->DR = (*pdata);

    while ((I2C1->SR1 & I2C_SR1_TXE) == 0);
    I2C1->CR1 |= I2C_CR1_STOP;
    
}

void mcp23017_init(void) {
  uint8_t pdata[3];
  
	uint8_t CTRL_BYTE;
	CTRL_BYTE = ((FIXED_BITS << 4) | (A2 << 3) | (A1 << 2) | (A0 << 1) | (RW << 0));
  
  pdata[0] = IOCON_BANK_0_IOCON;
  pdata[1] = 0x08; 
  pdata[2] = 0x08;
  I2C_Transmit(I2C1, CTRL_BYTE, pdata);
	
  pdata[0] = IOCON_BANK_0_IODIRA;
  pdata[1] = 0x00; 
  pdata[2] = 0x00;
  I2C_Transmit(I2C1, CTRL_BYTE, pdata);

	delay();
	
		while(1) {
			pdata[0] = IOCON_BANK_0_GPIOA;
			pdata[1] = 0xAB; //GPIOA 1010 1011
			pdata[2] = 0xCD; //GPIOB 1100 1101
			I2C_Transmit(I2C1, CTRL_BYTE, pdata);
			delay();

			pdata[0] = IOCON_BANK_0_GPIOA;
			pdata[1] = 0x00; //GPIOA
			pdata[2] = 0x00; //GPIOB
			I2C_Transmit(I2C1, CTRL_BYTE, pdata);
			delay();
		}
}

#endif
