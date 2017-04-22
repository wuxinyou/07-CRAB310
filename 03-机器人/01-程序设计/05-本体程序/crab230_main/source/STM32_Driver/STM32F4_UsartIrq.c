/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：串行中断函数集
*/
/* Includes ------------------------------------------------------------------*/
#include "STM32F4_UsartInit.h"

/**************************** USART1 IRQHandler ********************************/
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		USART_RXComplete(&USART_data_1);
  }
  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  { 
  	USART_ClearITPendingBit(USART1,USART_IT_TXE);  
    /* Write one byte to the transmit data register */
		USART1_DataRegEmpty(&USART_data_1);
   
  }

  if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART1,USART_IT_TC); 
	#ifdef USART1_RS485
		USART1_RS485_TX_DIS;
	#endif 
	
  }
}

/**************************** USART2 IRQHandler ********************************/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		USART_RXComplete(&USART_data_2);
  
  }
  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
  	USART_ClearITPendingBit(USART2,USART_IT_TXE);
	/* Write one byte to the transmit data register */
		USART2_DataRegEmpty(&USART_data_2); 
  }

   if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART2,USART_IT_TC);  
	#ifdef USART2_RS485
		USART2_RS485_TX_DIS;
	#endif  
  }
}

/**************************** USART3 IRQHandler ********************************/
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		USART_RXComplete(&USART_data_3);
  }
  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 
  	USART_ClearITPendingBit(USART3,USART_IT_TXE);  
    /* Write one byte to the transmit data register */
		USART3_DataRegEmpty(&USART_data_3);
   
  }

   if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART3,USART_IT_TC);  
	#ifdef USART3_RS485
		USART3_RS485_TX_DIS;
	#endif 
  }
}

/**************************** USART4 IRQHandler ********************************/
void UART4_IRQHandler(void)
{
	
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
		
  	USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		USART_RXComplete(&USART_data_4);
		
  }
  
  if(USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
  {
  	USART_ClearITPendingBit(UART4,USART_IT_TXE); 
    /* Write one byte to the transmit data register */
 		USART4_DataRegEmpty(&USART_data_4);
   
  }

   if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
  { 

  	USART_ClearITPendingBit(UART4,USART_IT_TC);  
	#ifdef USART4_RS485
		USART4_RS485_TX_DIS;
	#endif 
  }
}


/**************************** USART5 IRQHandler ********************************/
void UART5_IRQHandler(void)
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		USART_RXComplete(&USART_data_5);
  
  }
  
  if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
  {  
  	USART_ClearITPendingBit(UART5,USART_IT_TXE); 
    /* Write one byte to the transmit data register */
	USART5_DataRegEmpty(&USART_data_5);
   
  }

   if(USART_GetITStatus(UART5, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(UART5,USART_IT_TC);  
	#ifdef USART5_RS485
		USART5_RS485_TX_DIS;
	#endif 
  }
}

void USART6_IRQHandler(void)
{
  if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART6, USART_IT_RXNE);
    /* Read one byte from the receive data register */
		 USART_RXComplete(&USART_data_6);  
  } 
  if(USART_GetITStatus(USART6, USART_IT_TXE) != RESET)
  { 
  	USART_ClearITPendingBit(USART6,USART_IT_TXE);  
    /* Write one byte to the transmit data register */
		USART6_DataRegEmpty(&USART_data_6);  
  }
  if(USART_GetITStatus(USART6, USART_IT_TC) != RESET)
  { 
  	USART_ClearITPendingBit(USART6,USART_IT_TC);  
	#ifdef USART6_RS485
		USART6_RS485_TX_DIS;
	#endif 
  }
}
