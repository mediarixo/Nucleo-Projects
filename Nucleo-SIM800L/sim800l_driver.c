#include "sim800l_driver.h"

void uprintf(USART_Handle_t *pUSARTHandle, char* format, ...) {
	char buffer[USART_BUFFER_SIZE];
	uint16_t len;
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	len = strlen(buffer);
	USART_SendData(pUSARTHandle, (uint8_t*)buffer, len);
	va_end(args);
}

void uscanf(USART_Handle_t *pUSARTHandle, uint8_t *pdata, bool do_echo, char end_char) {
	char buffer[USART_BUFFER_SIZE];
	uint16_t i = 0;
	bool timeout = false;
	memset(buffer, '\0', USART_BUFFER_SIZE);
	do {
		if (!timeout) { USART_ReceiveData(pUSARTHandle, (uint8_t*)&buffer[i], 1, &timeout); } 
		if ((do_echo) && (pUSARTHandle == VCP)) { uprintf(VCP, "%c", buffer[i]); } 
		*(pdata++) = buffer[i++]; 
		if (buffer[i-1] == end_char) { timeout = true; }
	} while (buffer[i-1] != end_char);   
	if ((do_echo) && (pUSARTHandle == SIM)) { uprintf(VCP, "%s", buffer); } 
 	if (pUSARTHandle == VCP) uprintf(VCP, "\r\n");    
}

void send_sms(const char phonenumber[], const char textmessage[]) {	
	char cmd_data[USART_BUFFER_SIZE];
	sim_printf("AT+CMGF=1\r\n");
	sim_scanf(cmd_data);					
	sim_printf("AT+CMGS=\"%s\"\r\n", phonenumber);
	sim_scanf(cmd_data);								
	sim_printf("%s",textmessage);
	sim_scanf(cmd_data);		  			
	sim_printf("\x1A");
	sim_scanf(cmd_data);
}
