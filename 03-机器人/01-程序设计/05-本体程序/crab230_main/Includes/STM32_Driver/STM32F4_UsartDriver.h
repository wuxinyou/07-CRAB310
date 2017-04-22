/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：使用前需要先配置RS485端口的使能情况与引脚情况

*/
#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include "stm32f4xx.h"
// #include "MySysDefine.h"
#include "STM32F4_GpioInit.h"
// #include <stdlib.h>	
// #include "STM32F4_UsartInit.h"
// typedef uint8_t bool;
#define USART1_RS485  
// #define USART2_RS485  
#define USART3_RS485  
// #define USART4_RS485  
// #define USART5_RS485  
// #define USART6_RS485  




#define __GPIO_UART1E_PORT	GPIOA
#define __GPIO_UART2E_PORT	GPIOA				
#define __GPIO_UART3E_PORT	GPIOA				
#define __GPIO_UART4E_PORT	GPIOD
#define __GPIO_UART5E_PORT	GPIOD
#define __GPIO_UART6E_PORT	GPIOA

#define __GPIO_UART1E_PIN	GPIO_Pin_4
#define __GPIO_UART2E_PIN	GPIO_Pin_5
#define __GPIO_UART3E_PIN	GPIO_Pin_7
#define __GPIO_UART4E_PIN	GPIO_Pin_1
#define __GPIO_UART5E_PIN	GPIO_Pin_0
#define __GPIO_UART6E_PIN	GPIO_Pin_8

#define RCC_ClockCmdGpio_USART1_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
#define RCC_ClockCmdGpio_USART2_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
#define RCC_ClockCmdGpio_USART3_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
#define RCC_ClockCmdGpio_USART4_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RCC_ClockCmdGpio_USART5_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RCC_ClockCmdGpio_USART6_RS485	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)


#define UART1E_ON			GPIO_SetBits(__GPIO_UART1E_PORT, __GPIO_UART1E_PIN)	
#define UART1E_OFF		GPIO_ResetBits(__GPIO_UART1E_PORT, __GPIO_UART1E_PIN)
#define UART2E_ON			GPIO_SetBits(__GPIO_UART2E_PORT, __GPIO_UART2E_PIN)	
#define UART2E_OFF		GPIO_ResetBits(__GPIO_UART2E_PORT, __GPIO_UART2E_PIN)
#define UART3E_ON			GPIO_SetBits(__GPIO_UART3E_PORT, __GPIO_UART3E_PIN)	
#define UART3E_OFF		GPIO_ResetBits(__GPIO_UART3E_PORT, __GPIO_UART3E_PIN)
#define UART4E_ON			GPIO_SetBits(__GPIO_UART4E_PORT, __GPIO_UART4E_PIN)	
#define UART4E_OFF		GPIO_ResetBits(__GPIO_UART4E_PORT, __GPIO_UART4E_PIN)
#define UART5E_ON			GPIO_SetBits(__GPIO_UART5E_PORT, __GPIO_UART5E_PIN)	
#define UART5E_OFF		GPIO_ResetBits(__GPIO_UART5E_PORT, __GPIO_UART5E_PIN)
#define UART6E_ON			GPIO_SetBits(__GPIO_UART6E_PORT, __GPIO_UART6E_PIN)	
#define UART6E_OFF		GPIO_ResetBits(__GPIO_UART6E_PORT, __GPIO_UART6E_PIN)

#ifdef USART1_RS485
	#define USART1_RS485_TX_EN  	UART1E_ON
	#define USART1_RS485_TX_DIS		UART1E_OFF
#endif

	
#ifdef USART2_RS485
	#define USART2_RS485_TX_EN   	UART2E_ON
	#define USART2_RS485_TX_DIS	 	UART2E_OFF
#endif
	
#ifdef USART3_RS485
	#define USART3_RS485_TX_EN  	UART3E_ON
	#define USART3_RS485_TX_DIS		UART3E_OFF
#endif
	
#ifdef USART4_RS485
	#define USART4_RS485_TX_EN   	UART4E_ON
	#define USART4_RS485_TX_DIS		UART4E_OFF
#endif
	
#ifdef USART5_RS485
	#define USART5_RS485_TX_EN 		UART5E_ON 
	#define USART5_RS485_TX_DIS		UART5E_OFF		
#endif

#ifdef USART6_RS485
	#define USART6_RS485_TX_EN 		UART6E_ON 
	#define USART6_RS485_TX_DIS		UART6E_OFF		
#endif

/* USART buffer defines. */

typedef USART_TypeDef USART_t; 

/* \brief  Receive buffer size: 2,4,8,16,32,64,128 or 256 bytes. */
#define USART_RX_BUFFER_SIZE 128
/* \brief Transmit buffer size: 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 128
/* \brief Receive buffer mask. */
#define USART_RX_BUFFER_MASK ( USART_RX_BUFFER_SIZE - 1 )
/* \brief Transmit buffer mask. */
#define USART_TX_BUFFER_MASK ( USART_TX_BUFFER_SIZE - 1 )


#if ( USART_RX_BUFFER_SIZE & USART_RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif
#if ( USART_TX_BUFFER_SIZE & USART_TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif


/* \brief USART transmit and receive ring buffer. */
typedef struct USART_Buffer
{
	/* \brief Receive buffer. */
	volatile int8_t RX[USART_RX_BUFFER_SIZE];
	/* \brief Transmit buffer. */
	volatile int8_t TX[USART_TX_BUFFER_SIZE];
	/* \brief Receive buffer head. */
	volatile int8_t RX_Head;
	/* \brief Receive buffer tail. */
	volatile int8_t RX_Tail;
	/* \brief Transmit buffer head. */
	volatile int8_t TX_Head;
	/* \brief Transmit buffer tail. */
	volatile int8_t TX_Tail;
} USART_Buffer_t;


/*! \brief Struct used when interrupt driven driver is used.
*
*  Struct containing pointer to a usart, a buffer and a location to store Data
*  register interrupt level temporary.
*/
typedef struct Usart_and_buffer
{
	/* \brief Pointer to USART module to use. */
	USART_t * usart;
	/* \brief Data buffer. */
	USART_Buffer_t buffer;
// 	void (*STM32_InitUsart)(u32 Baudrate);
} USART_data_t;







/*! \brief Check if data register empty flag is set.
 *
 *  \param _usart      The USART module.
 */
#define USART_IsTXDataRegisterEmpty(_usart) (((_usart)->STATUS & USART_DREIF_bm) != 0)



/*! \brief Put data (5-8 bit character).
 *
 *  Use the macro USART_IsTXDataRegisterEmpty before using this function to
 *  put data to the TX register.
 *
 *  \param _usart      The USART module.
 *  \param _data       The data to send.
 */
#define USART_PutChar(_usart, _data) ((_usart)->DATA = _data)



/*! \brief Checks if the RX complete interrupt flag is set.
 *
 *   Checks if the RX complete interrupt flag is set.
 *
 *  \param _usart     The USART module.
 */
#define USART_IsRXComplete(_usart) (((_usart)->STATUS & USART_RXCIF_bm) != 0)




/*! \brief Get received data (5-8 bit character).
 *
 *  This macro reads out the RX register.
 *  Use the macro USART_RX_Complete to check if anything is received.
 *
 *  \param _usart     The USART module.
 *
 *  \retval           Received data.
 */
#define USART_GetChar(_usart)  ((_usart)->DATA)



extern void USART_InterruptDriver_Initialize(USART_data_t * usart_data,
                                      USART_t * usart);


extern uint8_t USART_TXBuffer_FreeSpace(USART_data_t * usart_data);
extern uint8_t USART_TXBuffer_PutByte(USART_data_t * usart_data, uint8_t data);
extern uint8_t USART_RXBufferData_Available(USART_data_t * usart_data);
extern uint8_t USART_RXBuffer_GetByte(USART_data_t * usart_data);
extern uint8_t USART_RXComplete(USART_data_t * usart_data);

extern void USART_DataRegEmpty(USART_data_t * usart_data);
extern void USART1_DataRegEmpty(USART_data_t * usart_data);
extern void USART2_DataRegEmpty(USART_data_t * usart_data);
extern void USART3_DataRegEmpty(USART_data_t * usart_data);
extern void USART4_DataRegEmpty(USART_data_t * usart_data);
extern void USART5_DataRegEmpty(USART_data_t * usart_data);
extern void USART6_DataRegEmpty(USART_data_t * usart_data);

#define USART_CR1_TXEIE_gm 	(uint16_t)(1<<7)

#endif
