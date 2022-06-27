#include "gpio_driver.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t State) {
    if (State == ENABLE) {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_EN();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_EN();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_EN();
        }
    } else {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_DI();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_DI();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_DI();
        }
    }
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint32_t tempReg = 0;

    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
        tempReg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //safe-clearing
        pGPIOHandle->pGPIOx->MODER |= tempReg;
    } else { /* interrupt mode */ }

    tempReg = 0;
    tempReg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //safe-clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= tempReg;

    tempReg = 0;
    tempReg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //safe-clearing
    pGPIOHandle->pGPIOx->PUPDR |= tempReg;

    tempReg = 0;
    tempReg = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //safe-clearing
    pGPIOHandle->pGPIOx->OTYPER |= tempReg;

    tempReg = 0;
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7) {
            tempReg = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4));
            pGPIOHandle->pGPIOx->AFRL &= ~(0xF << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber * 4)); //safe-clearing
            pGPIOHandle->pGPIOx->AFRL |= tempReg;
        } else {
            tempReg = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8) * 4));
            pGPIOHandle->pGPIOx->AFRH &= ~(0xF << ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8) * 4));
            pGPIOHandle->pGPIOx->AFRH |= tempReg;
        }
    }
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
    if (pGPIOx == GPIOA) {
        GPIOA_REG_RESET();
    } else if (pGPIOx == GPIOB) {
        GPIOB_REG_RESET();
    }
}
