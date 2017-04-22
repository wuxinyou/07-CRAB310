
#ifndef _SERIALPORT_H
	#define _SERIALPORT_H

	#include <stdlib.h>	
	#include <stdint.h>	
	#include "stm32f10x.h"
	#include "STM32_GPIO.h"
	#include "STM32_Priority.h"

	typedef USART_TypeDef USART_t;
	typedef GPIO_TypeDef GPIO_t;
	#define RX_BUFFER_SIZE 32
	#define TX_BUFFER_SIZE 32
	#define RX_BUFFER_MASK ( RX_BUFFER_SIZE - 1 )
	#define TX_BUFFER_MASK ( TX_BUFFER_SIZE - 1 )
	#if ( RX_BUFFER_SIZE & RX_BUFFER_MASK )
		#error RX buffer size is not a power of 2
	#endif
	#if ( TX_BUFFER_SIZE & TX_BUFFER_MASK )
		#error TX buffer size is not a power of 2
	#endif

	typedef struct USART_Buffer
	{
			__IO uint8_t RX[RX_BUFFER_SIZE];
			__IO uint8_t TX[TX_BUFFER_SIZE];
			__IO uint8_t RX_Head;
			__IO uint8_t RX_Tail;
			__IO uint8_t TX_Head;
			__IO uint8_t TX_Tail;
	}USART_Buffer_t;

	class USART_data_t
	{
		public:
			USART_data_t(void);
		public:
			bool txBuffer_GetFreeStatus(void);
			bool txBuffer_SendAll(void);
			uint8_t txBuffer_PutByte(uint8_t);
			bool rxBuffer_GetAvailableStatus(void);
			uint8_t rxBuffer_GetByte(void);
			bool rxComplete(void);
			void dataRegEmpty(void);
			void enableTX(void);				//	使能485发送
			void disabledTX(void);			//	失能485发送
		public:
			USART_t * usart;
			USART_Buffer_t buffer;
			bool useRS485Flag;
			GPIO_t* ctrTxPort;					//	控制485发送的端口号
			uint16_t ctrTxPin;					//	控制485发送的引脚号
	};
	
	class SerialPort
	{
		public:
			SerialPort(int s_port=1,int s_baudrate=19200);
			~SerialPort();
			int getPort(void);
			bool readAllow(void);
			uint8_t getChar(void);
			bool putChar(uint8_t);
			void write( uint8_t * data, uint8_t maxSize );
			void writeLine(const char*);
			void open(void);							//	打开串口
			void close(void);							//	关闭串口
			void setRS485CtrTx(GPIO_TypeDef*,uint16_t);
			void setPriority(uint8_t,uint8_t);
		private:
			int USART_IRQn;								//	中断号
			void initUsart(void);
			void usartConfig(USART_TypeDef*,uint32_t,uint16_t);
			void usartGpioInit(void);
		private:
			USART_data_t *COM;
			int port;
			int baudrate;
	};

#endif

