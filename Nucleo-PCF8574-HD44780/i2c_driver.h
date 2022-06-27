#ifndef INC_I2C_DRIVER_H_
#define INC_I2C_DRIVER_H_

#include "stm32f401ret6.h"

#define MASTER_ADDR  0x61
#define I2C_SCL_SPEED_SM        100000

#define I2C_ACK_ENABLE          1
#define I2C_ACK_DISABLE         0

#define I2C_FM_DUTY_2           0
#define I2C_FM_DUTY_16_9        1

#define I2C_FLAG_SB             (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR           (1 << I2C_SR1_ADDR)
#define I2C_FLAG_TXE            (1 << I2C_SR1_TXE)
#define I2C_FLAG_BTF            (1 << I2C_SR1_BTF)

void I2C_Init(I2C_RegDef_t *pI2Cx);
void I2C_SendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t State);

#endif /* INC_I2C_DRIVER_H_ */
