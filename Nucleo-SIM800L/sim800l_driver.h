#ifndef INC_SIM800L_DRIVER_H_
#define INC_SIM800L_DRIVER_H_

#include "stm32f401ret6.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

extern USART_Handle_t *VCPHandle, *SIMHandle;

#define USART_BUFFER_SIZE  UINT8_MAX  
#define VCP                VCPHandle
#define SIM                SIMHandle
#define ECHO               1
#define NOECHO             !ECHO
#define SIM_ENDING_CHAR    '\0'
#define VCP_ENDING_CHAR    '\r'

#define vcp_scanf(x)       uscanf(VCP, (uint8_t*)x, ECHO, VCP_ENDING_CHAR)
#define vcp_printf(x, ...) uprintf(VCP, x, ##__VA_ARGS__)

#define sim_scanf(x)       uscanf(SIM, (uint8_t*)x, ECHO, SIM_ENDING_CHAR)
#define sim_printf(x, ...) uprintf(SIM, x, ##__VA_ARGS__)

void uprintf(USART_Handle_t *pUSARTHandle, char* format, ...);
void uscanf(USART_Handle_t *pUSARTHandle, uint8_t *pdata, bool do_echo, char end_char);

void send_sms(const char phonenumber[], const char textmessage[]);

#endif /* INC_SIM800L_DRIVER_H_ */

