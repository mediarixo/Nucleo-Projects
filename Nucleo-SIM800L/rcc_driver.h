#ifndef INC_RCC_DRIVER_H_
#define INC_RCC_DRIVER_H_

#include "stm32f401ret6.h"

uint32_t RCC_GetPLLOutputClock(void);
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);

#endif // !INC_RCC_DRIVER_H_

