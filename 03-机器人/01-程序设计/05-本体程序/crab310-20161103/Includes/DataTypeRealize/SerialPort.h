
#ifndef _SERIALPORT_H
#define _SERIALPORT_H

#ifdef __cplusplus  
extern "C"
{
#endif
	#include <stdlib.h>			 
	#include "STM32F4_UsartInit.h"
#ifdef __cplusplus
				 
	class SerialPort
	{
		public:
			SerialPort(int,int);
			~SerialPort();
			int getPort();
			bool readAllow();
			uint8_t getChar(void);
			bool putChar(uint8_t);
			void write( uint8_t * data, uint8_t maxSize );
			void writeLine(const char*);
			void open(void);
			void close(void);
		private:
			USART_data_t *COM;
			int port;
			int baudrate;
	};
}  
#endif
#endif

