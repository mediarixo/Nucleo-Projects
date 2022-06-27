#include "i2c_driver.h"

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t State) {
    if (State == ENABLE) {
        if (pI2Cx == I2C1) {
            I2C1_PCLK_EN();
        } 
    } else {
        if (pI2Cx == I2C1) {
            I2C1_PCLK_DI();
        } 
    }
}

static uint32_t RCC_GetPLLOutputClock(void) {
    // !!!WARNING - NOT IMPLEMENTED!!!
    return 0;
}

static uint32_t RCC_GetPCLK1Value(void) {

    uint32_t pclk1, systemclk, hpre, ahbprescaler;
    uint8_t clksource, ppre1, apb1prescaler;
    clksource = ((RCC->CFGR >> 2) & 0x3);
    if (clksource == 0) {
        //using HSI
        systemclk = 16000000;
    } else if (clksource == 1) {
        //using HSE
        systemclk = 8000000;
    } else if (clksource == 2) {
        //using PLL
        systemclk = RCC_GetPLLOutputClock();
    }
    hpre = ((RCC->CFGR >> 4) & 0xF);
    if (hpre < 8) {
        ahbprescaler = 1;
    } else if (hpre == 8){
        ahbprescaler = 2;
    } else if (hpre == 9){
        ahbprescaler = 4;
    } else if (hpre == 10){
        ahbprescaler = 8;
    } else if (hpre == 11){
        ahbprescaler = 16;
    } else if (hpre == 12){
        ahbprescaler = 32;
    } else if (hpre == 13){
        ahbprescaler = 64;
    } else if (hpre == 14){
        ahbprescaler = 128;
    } else if (hpre == 15){
        ahbprescaler = 256;
    } else if (hpre == 16){
        ahbprescaler = 512;
    }
    ppre1 = ((RCC->CFGR > 10) & 0x7);
    if (ppre1 < 4) {
        apb1prescaler = 1;
    } else if (ppre1 == 4) {
        apb1prescaler = 2;
    } else if (ppre1 == 5) {
        apb1prescaler = 4;
    } else if (ppre1 == 6) {
        apb1prescaler = 8;
    } else if (ppre1 == 7) {
        apb1prescaler = 16;
    }
    pclk1 = ((systemclk / ahbprescaler) / apb1prescaler);
    return pclk1;
}

void I2C_Init(I2C_RegDef_t *pI2Cx) {
    uint32_t tempReg = 0;
    uint16_t ccr_value = 0;
    uint8_t trise_value = 0;
    
    I2C_PeriClockControl(pI2Cx, ENABLE);
    
    pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);

    tempReg |= (I2C_ACK_ENABLE << I2C_CR1_ACK);
    pI2Cx->CR1 = tempReg;

    tempReg = 0;
    tempReg |= RCC_GetPCLK1Value() / 1000000U;
    pI2Cx->CR2 = (tempReg & 0x3F); //safe-masking first 5 bits

    tempReg = 0;
    tempReg |= MASTER_ADDR << 1;
    //bit 14 Should always be kept at 1 by software
    tempReg |= (1 << 14);   
    pI2Cx->OAR1 = (tempReg & 0xFF);

    tempReg = 0;
    tempReg &= ~(1 << I2C_CCR_FS);
    ccr_value = (RCC_GetPCLK1Value()) / (2 * I2C_SCL_SPEED_SM);
    tempReg |= (ccr_value & 0xFFF);
    pI2Cx->CCR = tempReg;

    trise_value = (RCC_GetPCLK1Value() / 1000000U) + 1;
    pI2Cx->TRISE = (trise_value & 0x3F);

    pI2Cx->CR1 |= (1 << I2C_CR1_PE);
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t RnWbit) {
    SlaveAddr <<= 1;
    if (RnWbit == RESET) {
        SlaveAddr &= ~(1);  // RnWbit is cleared
    } else {
        SlaveAddr |= (1);   // RnWbit is set
    }
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx) {
    uint32_t dummyRead = 0;
    dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR2;
    (void)dummyRead;
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx) {
    pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx) {
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

static uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName) {
    return(pI2Cx->SR1 & FlagName) ? SET : RESET;
}

void I2C_SendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr) {
    I2C_GenerateStartCondition(pI2Cx);

    while(! I2C_GetFlagStatus(pI2Cx, I2C_FLAG_SB) );

    I2C_ExecuteAddressPhase(pI2Cx, SlaveAddr, RESET);

    while(! I2C_GetFlagStatus(pI2Cx, I2C_FLAG_ADDR) );

    I2C_ClearADDRFlag(pI2Cx);

    while (Len > 0) {
        while(! I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE) );
        pI2Cx->DR = *pTxBuffer++;
        Len--;
    }

    while(! I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE) );
    while(! I2C_GetFlagStatus(pI2Cx, I2C_FLAG_BTF) );

    I2C_GenerateStopCondition(pI2Cx);
}

