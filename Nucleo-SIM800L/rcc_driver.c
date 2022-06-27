#include "rcc_driver.h"

uint32_t RCC_GetPLLOutputClock(void) {
    /* !!!WARNING: NOT IMPLEMENTED !!!*/
    return 0;
}

uint32_t RCC_GetPCLK1Value(void) {
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

uint32_t RCC_GetPCLK2Value(void) {
    uint32_t pclk2, systemclk, hpre, ahbprescaler;
    uint8_t clksource, ppre2, apb2prescaler;
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
    ppre2 = ((RCC->CFGR > 13) & 0x7);
    if (ppre2 < 4) {
        apb2prescaler = 1;
    } else if (ppre2 == 4) {
        apb2prescaler = 2;
    } else if (ppre2 == 5) {
        apb2prescaler = 4;
    } else if (ppre2 == 6) {
        apb2prescaler = 8;
    } else if (ppre2 == 7) {
        apb2prescaler = 16;
    }
    pclk2 = ((systemclk / ahbprescaler) / apb2prescaler);
    return pclk2;
}
