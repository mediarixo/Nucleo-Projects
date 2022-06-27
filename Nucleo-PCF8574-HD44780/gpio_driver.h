#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "stm32f401ret6.h"

#define GPIOB_PIN_NO_8           8
#define GPIOB_PIN_NO_9           9
#define GPIO_MODE_ALTFN         2
#define GPIO_OP_TYPE_OPENDRAIN  1
#define GPIO_SPEED_FAST         2
#define GPIO_PIN_PULLUP         1
#define GPIO_NO_ALTFN           4

void GPIO_Init(uint8_t GPIO_PinNumber);

#endif /* !INC_GPIO_DRIVER_H_ */
