#ifndef INC_STM32F401RET6_H_
#define INC_STM32F401RET6_H_

#include <stdint.h>
#define __vo volatile

#define FLASH_BASEADDR         0x08000000U
#define SRAM1_BASEADDR         0x20000000U
#define SRAM
#define ROM                    0x1FFF0000U

#define PERIPH_BASEADDR		      0X40000000U
#define APB1PERIPH_BASEADDR	   PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR    (PERIPH_BASEADDR+0x00010000)  
#define AHB1PERIPH_BASEADDR    (PERIPH_BASEADDR+0x00020000)
 
#define RCC_BASEADDR             (AHB1PERIPH_BASEADDR+0x3800)
#define GPIOA_BASEADDR           (AHB1PERIPH_BASEADDR+0x0000)
#define GPIOB_BASEADDR           (AHB1PERIPH_BASEADDR+0x0400)
#define GPIOC_BASEADDR           (AHB1PERIPH_BASEADDR+0x0800)
#define I2C1_BASEADDR		          (APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASEADDR		          (APB1PERIPH_BASEADDR+0x5800)
#define I2C3_BASEADDR		          (APB1PERIPH_BASEADDR+0x5C00)
#define USART1_BASEADDR          (APB2PERIPH_BASEADDR+0x1000)
#define USART6_BASEADDR          (APB2PERIPH_BASEADDR+0x1400)
#define USART2_BASEADDR          (APB1PERIPH_BASEADDR+0x4400)  
 
typedef struct {
    __vo uint32_t MODER;
    __vo uint32_t OTYPER;
    __vo uint32_t OSPEEDR;
    __vo uint32_t PUPDR;
    __vo uint32_t IDR;
    __vo uint32_t ODR;
    __vo uint32_t BSRR;
    __vo uint32_t LCKR;
    __vo uint32_t AFRL;
    __vo uint32_t AFRH;
} GPIO_RegDef_t;

typedef struct {
    __vo uint32_t CR;
    __vo uint32_t PLLCFGR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;
    __vo uint32_t AHB1RSTR;
    __vo uint32_t AHB2RSTR;
         uint32_t RESERVED1[2];
    __vo uint32_t APB1RSTR;
    __vo uint32_t APB2RSTR;
         uint32_t RESERVED2[2];
    __vo uint32_t AHB1ENR;
    __vo uint32_t AHB2ENR;
         uint32_t RESERVED3[2];
    __vo uint32_t APB1ENR;
    __vo uint32_t APB2ENR;
         uint32_t RESERVED4[2];
    __vo uint32_t AHB1LPENR;
    __vo uint32_t AHB2LPENR;
         uint32_t RESERVED5[2];
    __vo uint32_t APB1LPENR;
    __vo uint32_t APB2LPENR;
         uint32_t RESERVED6[2];
    __vo uint32_t BDCR;
    __vo uint32_t CSR;
         uint32_t RESERVED7[2];
    __vo uint32_t SSCGR;
    __vo uint32_t PLLI2SCFGR;
    __vo uint32_t DCKCFGR;
} RCC_RegDef_t;

typedef struct {
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t OAR1;
    __vo uint32_t OAR2;
    __vo uint32_t DR;
    __vo uint32_t SR1;
    __vo uint32_t SR2;
    __vo uint32_t CCR;
    __vo uint32_t TRISE;
    __vo uint32_t FLTR;
} I2C_RegDef_t;

typedef struct {
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t BRR;
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t CR3;
    __vo uint32_t GTPR;
} USART_RegDef_t;

#define RCC                    ((RCC_RegDef_t*)RCC_BASEADDR)
#define GPIOA                  ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                  ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                  ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define I2C1                   ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2                   ((I2C_RegDef_t*)I2C2_BASEADDR) 
#define I2C3                   ((I2C_RegDef_t*)I2C3_BASEADDR) 
#define USART1                 ((USART_RegDef_t*)USART1_BASEADDR)
#define USART6                 ((USART_RegDef_t*)USART6_BASEADDR)
#define USART2                 ((USART_RegDef_t*)USART2_BASEADDR)

#define GPIOA_PCLK_EN()           (RCC->AHB1ENR |= (1 << 0))
#define GPIOA_PCLK_DI()           (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_EN()           (RCC->AHB1ENR |= (1 << 1))
#define GPIOB_PCLK_DI()           (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_EN()           (RCC->AHB1ENR |= (1 << 2))
#define GPIOC_PCLK_DI()           (RCC->AHB1ENR &= ~(1 << 2))
#define I2C1_PCLK_EN()            (RCC->APB1ENR |= (1 << 21))
#define I2C1_PCLK_DI()            (RCC->APB1ENR &= ~(1 << 21)) 
#define I2C2_PCLK_EN()            (RCC->APB1ENR |= (1 << 22))
#define I2C2_PCLK_DI()            (RCC->APB1ENR &= ~(1 << 22)) 
#define I2C3_PCLK_EN()            (RCC->APB1ENR |= (1 << 23))
#define I2C3_PCLK_DI()            (RCC->APB1ENR &= ~(1 << 23)) 
#define USART1_PCLK_EN()          (RCC->APB2ENR |= (1 << 4)) 
#define USART1_PCLK_DI()          (RCC->APB2ENR &= ~(1 << 4)) 
#define USART6_PCLK_EN()          (RCC->APB2ENR |= (1 << 5)) 
#define USART6_PCLK_DI()          (RCC->APB2ENR &= ~(1 << 5)) 
#define USART2_PCLK_EN()          (RCC->APB1ENR |= (1 << 17)) 
#define USART2_PCLK_DI()          (RCC->APB1ENR &= ~(1 << 17)) 

#define I2C_CR1_PE             0
#define I2C_CR1_NOSTRETCH      7
#define I2C_CR1_START          8
#define I2C_CR1_STOP           9
#define I2C_CR1_ACK            10
#define I2C_CR1_SWRST          15

#define I2C_CR2_FREQ           0
#define I2C_CR2_ITERREN        8
#define I2C_CR2_ITEVTEN        9
#define I2C_CR2_ITBUFEN        10

#define I2C_SR1_SB             0
#define I2C_SR1_ADDR           1
#define I2C_SR1_BTF            2
#define I2C_SR1_STOPF          4
#define I2C_SR1_RXNE           6
#define I2C_SR1_TXE            7
#define I2C_SR1_BERR           8
#define I2C_SR1_ARLO           9
#define I2C_SR1_AF             10
#define I2C_SR1_OVR            11

#define I2C_SR1_TIMEOUT        14
#define I2C_SR2_MSL            0
#define I2C_SR2_BUSY           1
#define I2C_SR2_TRA            2

#define I2C_CCR_CCR            0
#define I2C_CCR_DUTY           14
#define I2C_CCR_FS             15

#define I2C_TRISE_TRISE        0

#define USART_SR_PE           0
#define USART_SR_FE           1
#define USART_SR_NF           2
#define USART_SR_ORE          3
#define USART_SR_IDLE         4
#define USART_SR_RXNE         5
#define USART_SR_TC           6
#define USART_SR_TXE          7
#define USART_SR_LBD          8
#define USART_SR_CTS          9

#define USART_BRR_DIV_FRACTION 0
#define USART_BRR_DIV_MANTISSA 4

#define USART_CR1_SBK         0
#define USART_CR1_RWU         1
#define USART_CR1_RE          2
#define USART_CR1_TE          3
#define USART_CR1_IDLEIE      4
#define USART_CR1_RXNEIE      5
#define USART_CR1_TCIE        6
#define USART_CR1_TXEIE       7
#define USART_CR1_PEIE        8
#define USART_CR1_PS          9
#define USART_CR1_PCE         10
#define USART_CR1_WAKE        11
#define USART_CR1_M           12
#define USART_CR1_UE          13
#define USART_CR1_OVER8       15

#define USART_CR2_ADD         0
#define USART_CR2_LBDL        5
#define USART_CR2_LBDIE       6
#define USART_CR2_LBCL        8
#define USART_CR2_CPHA        9
#define USART_CR2_CPOL        10
#define USART_CR2_CLKEN       11
#define USART_CR2_STOP        12
#define USART_CR2_LINEN       14

#define USART_CR3_EIE         0    
#define USART_CR3_IREN        1
#define USART_CR3_IRLP        2
#define USART_CR3_HDSEL       3
#define USART_CR3_NACK        4
#define USART_CR3_SCEN        5
#define USART_CR3_DMAR        6
#define USART_CR3_DMAT        7
#define USART_CR3_RTSE        8
#define USART_CR3_CTSE        9
#define USART_CR3_CTSIE       10
#define USART_CR3_ONEBIT      11

#define USART_GTPR_PSC        0
#define USART_GTPR_GT         8

#define RCC_APB1RSTR_I2C1RST   21
#define RCC_APB1RSTR_I2C2RST   22
#define RCC_APB1RSTR_I2C3RST   23
#define RCC_AHB1RSTR_GPIOARST  0
#define RCC_AHB1RSTR_GPIOBRST  1
#define RCC_AHB1RSTR_GPIOCRST  2
#define RCC_APB2RSTR_USART1RST 4
#define RCC_APB2RSTR_USART6RST 5
#define RCC_APB1RSTR_USART2RST 17

#define GPIOA_REG_RESET()      do { RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOARST); RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOARST); } while (0)
#define GPIOB_REG_RESET()      do { RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOBRST); RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOBRST); } while (0)
#define GPIOC_REG_RESET()      do { RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOCRST); RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOCRST); } while (0)

#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE

#include "gpio_driver.h"
#include "usart_driver.h"
#include "rcc_driver.h"

#endif /* INC_STM32F401RET6_H_ */ 
