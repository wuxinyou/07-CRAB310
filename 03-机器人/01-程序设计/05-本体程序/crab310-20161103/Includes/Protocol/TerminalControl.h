/**
  ******************************************************************************
	*文件：TerminalControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：Xbot和终端交互类的头文件
	*备注：
	*
  ******************************************************************************  
  */ 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _TERMINAL_CONTROL_H
#define _TERMINAL_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "SerialPort.h"
#include "DataChain.h"

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 
//串口工作模式宏
#define WIRE_WORK_MODE			0x01
#define WIRELESS_WORK_MODE	0x02
#define NOSIGNAL_WORK_MODE	0x00


class TerminalControl
{
public:
	TerminalControl(SerialPort *);
	virtual ~TerminalControl();
	void updateSendBuf(uint8_t * temBuf);
	void sendcommand();
	bool reciveData();
	uint8_t* getReciveData(){return reciveBuf;}
	int getSerialWorkMode(){return serialWorkMode;}
private:
	int serialWorkMode;
	SerialPort *terminalWireLessPort;		//无线串口号
	SerialPort *terminalWirePort;				//有线串口号
	RingChain *reciveChin;
	uint8_t *sendBuf; 
	uint8_t *reciveBuf;
	bool reciveData(SerialPort *);			//接收数据，将串口缓冲区的内容读取到reciveBuf

};

#endif /* _TERMINAL_CONTROL_H */


