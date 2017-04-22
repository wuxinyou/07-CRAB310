/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：使用前需要先配置RS485端口的使能情况与引脚情况

*/
#include "STM32F4_UsartDriver.h"


/*! \brief Initializes buffer and selects what USART module to use.
 *
 *  Initializes receive and transmit buffer and selects what USART module to use,
 *  and stores the data register empty interrupt level.
 *
 *  \param usart_data           The USART_data_t struct instance.
 *  \param usart                The USART module.
 *  \param dreIntLevel          Data register empty interrupt level.
 */
void USART_InterruptDriver_Initialize(USART_data_t * usart_data,
                                      USART_t * usart)
{
	usart_data->usart = usart;

	usart_data->buffer.RX_Tail = 0;
	usart_data->buffer.RX_Head = 0;
	usart_data->buffer.TX_Tail = 0;
	usart_data->buffer.TX_Head = 0;
}

 


/*! \brief Test if there is data in the transmitter software buffer.
 *
 *  This function can be used to test if there is free space in the transmitter
 *  software buffer.
 *
 *  \param usart_data The USART_data_t struct instance.
 *
 *  \retval true      There is data in the receive buffer.
 *  \retval false     The receive buffer is empty.
 */
uint8_t USART_TXBuffer_FreeSpace(USART_data_t * usart_data)
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = (usart_data->buffer.TX_Head + 1) & USART_TX_BUFFER_MASK;
	uint8_t tempTail = usart_data->buffer.TX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/*! \brief Test if there is data in the transmitter software buffer.
 *
 *  This function can be used to test if there is free space in the transmitter
 *  software buffer.
 *
 *  \param usart_data The USART_data_t struct instance.
 *
 *  \retval true      There is data in the receive buffer.
 *  \retval false     The receive buffer is empty.
 */
uint8_t USART_TXBuffer_SendAll(USART_data_t * usart_data)
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = (usart_data->buffer.TX_Head-1 ) & USART_TX_BUFFER_MASK;
	uint8_t tempTail = usart_data->buffer.TX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/*! \brief Put data (5-8 bit character).
 *
 *  Stores data byte in TX software buffer and enables DRE interrupt if there
 *  is free space in the TX software buffer.
 *
 *  \param usart_data The USART_data_t struct instance.
 *  \param data       The data to send.
 */
uint8_t USART_TXBuffer_PutByte(USART_data_t * usart_data,uint8_t data)
{
	uint16_t tempCR1;
	uint8_t tempTX_Head;
	uint8_t TXBuffer_FreeSpace;
	USART_Buffer_t * TXbufPtr;

	TXbufPtr = &usart_data->buffer;
	TXBuffer_FreeSpace = USART_TXBuffer_FreeSpace(usart_data);


	if(TXBuffer_FreeSpace)//串口缓冲区未满
	{
	  	tempTX_Head = TXbufPtr->TX_Head;
	  	TXbufPtr->TX[tempTX_Head]= data;
		/* Advance buffer head. */
		TXbufPtr->TX_Head = (tempTX_Head + 1) & USART_TX_BUFFER_MASK;
		/* Enable DRE interrupt.开中断 */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 | USART_CR1_TXEIE_gm);
		usart_data->usart->CR1 = tempCR1;
// 		USART_Cmd(usart_data->usart,ENABLE);
// 		usart_data->usart->CR1 |= USART_CR1_UE;
	}
	return TXBuffer_FreeSpace;
}



/*! \brief Test if there is data in the receive software buffer.
 *
 *  This function can be used to test if there is data in the receive software
 *  buffer.
 *
 *  \param usart_data         The USART_data_t struct instance
 *
 *  \retval true      There is data in the receive buffer.
 *  \retval false     The receive buffer is empty.

		
 */
uint8_t USART_RXBufferData_Available(USART_data_t * usart_data)
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = usart_data->buffer.RX_Head;
	uint8_t tempTail = usart_data->buffer.RX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}



/*! \brief Get received data (5-8 bit character).
 *
 *  The function USART_RXBufferData_Available should be used before this
 *  function is used to ensure that data is available.
 *
 *  Returns data from RX software buffer.
 *
 *  \param usart_data       The USART_data_t struct instance.
 *
 *  \return         Received data.
 */
uint8_t USART_RXBuffer_GetByte(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;

	bufPtr = &usart_data->buffer;
	ans = (bufPtr->RX[bufPtr->RX_Tail]);

	/* Advance buffer tail. */
	bufPtr->RX_Tail = (bufPtr->RX_Tail + 1) & USART_RX_BUFFER_MASK;
	
	return ans;
}

/*! \brief RX Complete Interrupt Service Routine.
 *
 *  RX Complete Interrupt Service Routine.
 *  Stores received data in RX software buffer.
 *
 *  \param usart_data      The USART_data_t struct instance.
 */
uint8_t USART_RXComplete(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;
	uint8_t tempRX_Head;
	uint8_t tempRX_Tail;
	uint8_t data;

	bufPtr = &usart_data->buffer;
	/* Advance buffer head. */
	tempRX_Head = (bufPtr->RX_Head + 1) & USART_RX_BUFFER_MASK;

	/* Check for overflow. */
	tempRX_Tail = bufPtr->RX_Tail;
	data = usart_data->usart->DR;

	if (tempRX_Head == tempRX_Tail) {
	  	ans = 0;
	}else{
		ans = 1;
		usart_data->buffer.RX[usart_data->buffer.RX_Head] = data;
		usart_data->buffer.RX_Head = tempRX_Head;
	}
	return ans;
}



/*! \brief Data Register Empty Interrupt Service Routine.
 *
 *  Data Register Empty Interrupt Service Routine.
 *  Transmits one byte from TX software buffer. Disables DRE interrupt if buffer
 *  is empty. Argument is pointer to USART (USART_data_t).
 *
 *  \param usart_data      The USART_data_t struct instance.
 */
void USART_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
		
					if(usart_data->usart==USART1)
					{
						#ifdef USART1_RS485
							USART1_RS485_TX_EN;
						#endif
					}
					else if(usart_data->usart==USART2)
					{
						#ifdef USART2_RS485
							USART2_RS485_TX_EN;
						#endif
					}	
					else if(usart_data->usart==USART3)
					{
						#ifdef USART3_RS485
							USART3_RS485_TX_EN;
						#endif
					}	
					else if(usart_data->usart==UART4)
					{
						#ifdef USART4_RS485
							USART4_RS485_TX_EN;
						#endif
					}	
					else if(usart_data->usart==UART5)
					{
						#ifdef USART5_RS485
							USART5_RS485_TX_EN;
						#endif
					}	
					else if(usart_data->usart==USART6)
					{
						#ifdef USART6_RS485
							USART6_RS485_TX_EN;
						#endif
					}	


		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;
// 		usart_data->usart->DR = usart_data->buffer.TX_Head;
		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}

}

/****************************************  USART1_DataRegEmpty **************************/

void USART1_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */

	#ifdef USART1_RS485
		USART1_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

/****************************************  USART2_DataRegEmpty **************************/

void USART2_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
	#ifdef USART2_RS485
		USART2_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

/****************************************  USART3_DataRegEmpty **************************/

void USART3_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
	#ifdef USART3_RS485
		USART3_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

/****************************************  USART4_DataRegEmpty **************************/

void USART4_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
	#ifdef USART4_RS485
		USART4_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;
// 		usart_data->usart->DR = usart_data->buffer.TX_Head;
		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}

}

/****************************************  USART5_DataRegEmpty **************************/

void USART5_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
	#ifdef USART5_RS485
		USART5_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

/****************************************  USART6_DataRegEmpty **************************/

void USART6_DataRegEmpty(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &usart_data->buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = usart_data->buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart_data->usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart_data->usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
	#ifdef USART6_RS485
		USART6_RS485_TX_EN;
	#endif
		data = bufPtr->TX[usart_data->buffer.TX_Tail];
		usart_data->usart->DR = data;

		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & USART_TX_BUFFER_MASK;
	}
}

