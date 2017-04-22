#include "STM32F4_DriverInit.h"
#include <stdlib.h>		
SerialPort *THIS[6];

static uint8_t getChar_1(void)
{
	return USART_RXBuffer_GetByte(&USART_data_1);
}
static uint8_t getChar_2(void)
{
	return USART_RXBuffer_GetByte(&USART_data_2);
}
static uint8_t getChar_3(void)
{
	return USART_RXBuffer_GetByte(&USART_data_3);
}
static uint8_t getChar_4(void)
{
	return USART_RXBuffer_GetByte(&USART_data_4);
}
static uint8_t getChar_5(void)
{
	return USART_RXBuffer_GetByte(&USART_data_5);
}
static uint8_t getChar_6(void)
{
	return USART_RXBuffer_GetByte(&USART_data_6);
}


static bool putChar_1(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_1,data);
}
static bool putChar_2(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_2,data);
}
static bool putChar_3(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_3,data);
}
static bool putChar_4(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_4,data);
}
static bool putChar_5(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_5,data);
}
static bool putChar_6(uint8_t data)
{
	return USART_TXBuffer_PutByte(&USART_data_6,data);
}


static void write_1( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_1(data[i]));
}
static void write_2( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_2(data[i]));
}
static void write_3( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_3(data[i]));
}
static void write_4( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_4(data[i]));
}
static void write_5( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_5(data[i]));
}
static void write_6( uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(putChar_6(data[i]));
}

static void open_1(void)
{
	UART1E_ON;
}
static void open_2(void)
{
	UART2E_ON;
}
static void open_3(void)
{
	UART3E_ON;
}
static void open_4(void)
{
	UART4E_ON;
}
static void open_5(void)
{
	UART5E_ON;
}
static void open_6(void)
{
	UART6E_ON;
}

static void close_1(void)
{
	UART1E_OFF;
}
static void close_2(void)
{
	UART2E_OFF;
}
static void close_3(void)
{
	UART3E_OFF;
}
static void close_4(void)
{
	UART4E_OFF;
}
static void close_5(void)
{
	UART5E_OFF;
}
static void close_6(void)
{
	UART6E_OFF;
}



bool init_com(uint8_t port,uint16_t baudrate,SerialPort * myself)
{
	bool ans=false;
	myself->baudrate=baudrate;
	switch(port)
	{
		case 1:
			STM32_InitUsart1(myself->baudrate);
			myself->COM=&USART_data_1;
			myself->port=1;
			myself->getChar=getChar_1;
			myself->putChar=putChar_1;
			myself->write=write_1;
			myself->open=open_1;
			myself->close=close_1;
			ans=true;
			break;
		case 2:
			STM32_InitUsart2(myself->baudrate);
			myself->COM=&USART_data_2;
			myself->port=2;
			myself->getChar=getChar_2;
			myself->putChar=putChar_2;
			myself->write=write_2;
			myself->open=open_2;
			myself->close=close_2;
			ans=true;
			break;
		case 3:
			STM32_InitUsart3(myself->baudrate);
			myself->COM=&USART_data_3;
			myself->port=3;
			myself->getChar=getChar_3;
			myself->putChar=putChar_3;
			myself->write=write_3;
			myself->open=open_3;
			myself->close=close_3;
			ans=true;
			break;
		case 4:
			STM32_InitUsart4(myself->baudrate);
			myself->COM=&USART_data_4;
			myself->port=4;
			myself->getChar=getChar_4;
			myself->putChar=putChar_4;
			myself->write=write_4;
			myself->open=open_4;
			myself->close=close_4;
			ans=true;
			break;
		case 5:
			STM32_InitUsart5(myself->baudrate);
			myself->COM=&USART_data_5;
			myself->port=5;
			myself->getChar=getChar_5;
			myself->putChar=putChar_5;
			myself->write=write_5;
			myself->open=open_5;
			myself->close=close_5;
			ans=true;
			break;
		case 6:
			STM32_InitUsart6(myself->baudrate);
			myself->COM=&USART_data_6;
			myself->port=6;
			myself->getChar=getChar_6;
			myself->putChar=putChar_6;
			myself->write=write_6;
			myself->open=open_6;
			myself->close=close_6;
			ans=true;
			break;
		default:
			ans=false;
			break;
	}
	return ans;
}
SerialPort *CreatSerialPort(uint8_t port,uint16_t baudrate)
{
	SerialPort *temSerialPort=(SerialPort *)malloc(sizeof(SerialPort));
	temSerialPort->initMyself=init_com;
	temSerialPort->initMyself(port,baudrate,temSerialPort);
	return temSerialPort;
}




