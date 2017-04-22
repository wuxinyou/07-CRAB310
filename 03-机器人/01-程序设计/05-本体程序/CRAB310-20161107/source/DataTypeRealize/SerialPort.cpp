/**
  ******************************************************************************
	*文件：SerialPort.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：串口类的实现
	*备注：该类是半分装的
	*
  ******************************************************************************  
	*/
	
#include "SerialPort.h"


//构造函数
SerialPort::SerialPort(int s_port,int s_baudrate)
{
	port=s_port;
	baudrate=s_baudrate;
	if(port==1)
	{
		COM=&USART_data_1;
		STM32_InitUsart1(baudrate);
	}

	else if(port==2)
	{
		COM=&USART_data_2;
		STM32_InitUsart2(baudrate);
	}
		
	else if(port==3)
	{
		COM=&USART_data_3;
		STM32_InitUsart3(baudrate);
	}
		
	else if(port==4)
	{
		COM=&USART_data_4;
		STM32_InitUsart4(baudrate);
	}
		
	else if(port==5)
	{
		COM=&USART_data_5;
		STM32_InitUsart5(baudrate);
	}
		
	else if(port==6)
	{
		COM=&USART_data_6;
		STM32_InitUsart6(baudrate);
	}
}

//析构函数
SerialPort::~SerialPort()
{
	COM=NULL;
}
int SerialPort::getPort()
{
	return port;
}


/**
  * 功  能：判定串口缓冲区是否有数据
  * 参  数：无
  * 返回值：
	*			true:有数据
  * 		false:无数据
  */
bool SerialPort::readAllow()
{
	return USART_RXBufferData_Available(COM);
}

/**
  * 功  能：从串口缓冲区中读取一个字节
  * 参  数：无
  * 返回值：读取的值
  */
uint8_t SerialPort::getChar(void)
{
	return USART_RXBuffer_GetByte(COM);
}

/**
  * 功  能：写一个数据到串口发送缓冲区
  * 参  数：待写的数据
  * 返回值：
	*			true:写入成功
	*			false:写入失败
  */
bool SerialPort::putChar(uint8_t data)
{
	return USART_TXBuffer_PutByte(COM,data);
}

/**
  * 功  能：写一串数据到串口缓冲区
  * 参  数：
	*			data：数组的指针
	*			maxSize：待写的长度
  * 返回值：无
  */
void SerialPort::write(uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(!putChar(data[i]));
}

/**
  * 功  能：写一个字符串到串口缓冲区
  * 参  数：
	*			data：字符串指针
  * 返回值：无
  */
void SerialPort::writeLine(const char* data)
{
	while(*data)
	{
		while(!putChar(*data));
		data++;
	}
}

/**
  * 功  能：打开串口
  * 参  数：无
  * 返回值：无
  */
void SerialPort::open(void)
{
	if(port==1)
	{
		USART_Cmd(USART1, ENABLE);
	}
		
	else if(port==2)
	{
		USART_Cmd(USART2, ENABLE);
	}
		
	else if(port==3)
	{
		USART_Cmd(USART3, ENABLE);
	}
		
	else if(port==4)
	{
		USART_Cmd(UART4, ENABLE);
	}
		
	else if(port==5)
	{
		USART_Cmd(UART5, ENABLE);
	}
		
	else if(port==6)
	{
		USART_Cmd(USART6, ENABLE);
	}
}

/**
  * 功  能：关闭串口
  * 参  数：无
  * 返回值：无
  */
void SerialPort::close(void)
{
	if(port==1)
	{
		USART_Cmd(USART1, DISABLE);
	}
		
	else if(port==2)
	{
		USART_Cmd(USART2, DISABLE);;
	}
		
	else if(port==3)
	{
		USART_Cmd(USART3, DISABLE);;
	}
		
	else if(port==4)
	{
		USART_Cmd(UART4, DISABLE);;
	}
		
	else if(port==5)
	{
		USART_Cmd(UART5, DISABLE);;
	}
		
	else if(port==6)
	{
		USART_Cmd(USART6, DISABLE);;
	}
}

