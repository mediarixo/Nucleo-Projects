#include "usart_driver.h"

/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t State) {
    if (State == ENABLE) {
        if (pUSARTx == USART1) {
            USART1_PCLK_EN();
        } else if (pUSARTx == USART6) {
            USART6_PCLK_EN();
        } else if (pUSARTx == USART2) {
            USART2_PCLK_EN();
        }
    } else {
        if (pUSARTx == USART1) {
            USART1_PCLK_DI();
        } else if (pUSARTx == USART6) {
            USART6_PCLK_DI();
        } else if (pUSARTx == USART2) {
            USART2_PCLK_DI();
        }
    }
}

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx;

	uint32_t usartdiv;

	uint32_t M_part,F_part;

  uint32_t tempreg=0;

  if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   PCLKx = RCC_GetPCLK2Value();
  }else
  {
	   PCLKx = RCC_GetPCLK1Value();
  }

  if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
  {
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
	   usartdiv = ((25 * PCLKx) / (4 *BaudRate));
  }

  M_part = usartdiv/100;
  tempreg |= M_part << 4;

  F_part = (usartdiv - (M_part * 100));

  if(pUSARTx->CR1 & ( 1 << USART_CR1_OVER8))
   {
	  F_part = ((( F_part * 8)+ 50) / 100)& ((uint8_t)0x07);
   }else
   {
	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);
   }

  tempreg |= F_part;

  pUSARTx->BRR = tempreg;
}

void USART_Init(USART_Handle_t *pUSARTHandle) {

	uint32_t tempReg=0;

	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempReg|= (1 << USART_CR1_RE);
	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempReg |= ( 1 << USART_CR1_TE );

	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		tempReg |= ( ( 1 << USART_CR1_RE) | ( 1 << USART_CR1_TE) );
	}

	tempReg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M ;

	if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_ENABLE_EVEN)
	{
		tempReg |= ( 1 << USART_CR1_PCE);
	}else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_ENABLE_ODD )
	{
	    tempReg |= ( 1 << USART_CR1_PCE);
	    tempReg |= ( 1 << USART_CR1_PS);
	}

	pUSARTHandle->pUSARTx->CR1 = tempReg;

	tempReg=0;

	tempReg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	pUSARTHandle->pUSARTx->CR2 = tempReg;

	tempReg=0;
	
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		tempReg |= (1 << USART_CR3_CTSE);
	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		tempReg |= (1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		tempReg |= ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
	}

	pUSARTHandle->pUSARTx->CR3 = tempReg;

	USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}

void USART_DeInit(USART_RegDef_t *pUSARTx) {
    if (pUSARTx == USART1) {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_USART1RST);
    } else if (pUSARTx == USART6) {
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_USART6RST);
    } else if (pUSARTx == USART2) {
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_USART2RST);
    }
}

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t State) {
    if (State == ENABLE) {
        pUSARTx->CR1 |= (1 << USART_CR1_UE);
    } else {
        pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
    }
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName) {
    return(pUSARTx->SR & FlagName) ? SET : RESET;
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint32_t i;
	uint16_t *pdata;
	for(i = 0 ; i < Len; i++)
	{
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE));

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				pTxBuffer++;
			}
		}
		else
		{
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}

	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));
}

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len, bool *timeout)
{
	uint32_t i, t = 0;
	for(i = 0 ; i < Len; i++)
	{
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_RXNE)) { if (t >= USART_MAX_DELAY) {*timeout = true; break;} if (pUSARTHandle->pUSARTx == USART1) t++; }

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS) {
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE) {
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);
				pRxBuffer++;
                pRxBuffer++;
			} else {
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
				pRxBuffer++;
			}
		} else {
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE) {
				 *pRxBuffer = pUSARTHandle->pUSARTx->DR;
			} else {
				 *pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);
			}
			pRxBuffer++;
		}
	}

}
