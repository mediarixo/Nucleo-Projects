#ifndef INC_USART_DRIVER_H_
#define INC_USART_DRIVER_H_

#include "stm32f401ret6.h"
#include <stdbool.h>

typedef struct {
    uint8_t     USART_Mode;
    uint32_t    USART_Baud;
    uint8_t     USART_NoOfStopBits;
    uint8_t     USART_WordLength;
    uint8_t     USART_ParityControl;
    uint8_t     USART_HWFlowControl;
} USART_Config_t;

typedef struct {
    USART_RegDef_t  *pUSARTx;
    USART_Config_t  USART_Config;
} USART_Handle_t;

#define USART_MODE_ONLY_TX      0
#define USART_MODE_ONLY_RX      1
#define USART_MODE_TXRX         2

#define USART_STD_BAUD_1200			1200
#define USART_STD_BAUD_2400			2400
#define USART_STD_BAUD_9600			9600
#define USART_STD_BAUD_19200 		19200
#define USART_STD_BAUD_38400 		38400
#define USART_STD_BAUD_57600 		57600
#define USART_STD_BAUD_115200 		115200
#define USART_STD_BAUD_230400 		230400
#define USART_STD_BAUD_460800 		460800
#define USART_STD_BAUD_921600 		921600
#define USART_STD_BAUD_2M 			2000000
#define SUART_STD_BAUD_3M 			3000000

#define USART_PARITY_ENABLE_ODD     2
#define USART_PARITY_ENABLE_EVEN    1
#define USART_PARITY_DISABLE        0

#define USART_WORDLEN_8BITS         0
#define USART_WORDLEN_9BITS         1

#define USART_STOPBITS_1            0
#define USART_STOPBITS_0_5          1
#define USART_STOPBITS_2            2
#define USART_STOPBITS_1_5          3

#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

#define USART_FLAG_TXE              (1 << USART_SR_TXE)
#define USART_FLAG_TC               (1 << USART_SR_TC)
#define USART_FLAG_RXNE             (1 << USART_SR_RXNE)

#define USART_MAX_DELAY    1000000

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t State);

void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len, bool *timeout);

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t State);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName);
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

#endif /* INC_USART_DRIVER_H_ */
