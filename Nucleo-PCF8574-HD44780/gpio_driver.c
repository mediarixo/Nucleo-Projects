#include "gpio_driver.h"


void GPIO_Init(uint8_t GPIO_PinNumber) {
    uint32_t tempReg = 0;
    GPIO_RegDef_t   *pGPIOx = GPIOB;

    GPIOB_PCLK_EN();

    tempReg = (GPIO_MODE_ALTFN << ( 2 * GPIO_PinNumber));
    pGPIOx->MODER &= ~(0x3 << GPIO_PinNumber); //safe-clearing
    pGPIOx->MODER |= tempReg;

    tempReg = 0;
    tempReg = (GPIO_SPEED_FAST << ( 2 * GPIO_PinNumber));
    pGPIOx->OSPEEDR &= ~(0x3 << GPIO_PinNumber); //safe-clearing
    pGPIOx->OSPEEDR |= tempReg;

    tempReg = 0;
    tempReg = (GPIO_PIN_PULLUP << ( 2 * GPIO_PinNumber));
    pGPIOx->PUPDR &= ~(0x3 << GPIO_PinNumber); //safe-clearing
    pGPIOx->PUPDR |= tempReg;

    tempReg = 0;
    tempReg = (GPIO_OP_TYPE_OPENDRAIN << GPIO_PinNumber);
    pGPIOx->OTYPER &= ~(0x1 << GPIO_PinNumber); //safe-clearing
    pGPIOx->OTYPER |= tempReg;

    tempReg = 0;
    tempReg = ( GPIO_NO_ALTFN << ((GPIO_PinNumber % 8) * 4));
    pGPIOx->AFRH &= ~(0xF << ((GPIO_PinNumber % 8) * 4));
    pGPIOx->AFRH |= tempReg;
}
