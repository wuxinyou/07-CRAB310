/**
  ******************************************************************************
	*文件：BaseControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电机及其他设备的协议的基类的头文件
	*备注：
	*
  ******************************************************************************  
	*/ 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _BASE_CONTROL_H
#define _BASE_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "DataChain.h"
#include "SerialPort.h"

/* 类型定义 --------------------------------------------------------------------*/
//联合体定义 方便数据转换
typedef union{
        uint16_t DATA_U16;
				int16_t DATA_16;
        unsigned char DATA_8[2];
// 				char DATA_8[2];
}ctrData;
/* 宏定义-----------------------------------------------------------------------*/ 
#define COMMAMD_LEN 6
#define	PORT_AMOUNT	6


class BaseControl
{
public:
	BaseControl(SerialPort *);
	virtual ~BaseControl();
	
	void setAddr(uint8_t a){addr=a;}
	void sendCommand();		//命令发送函数
	static uint8_t * getReciveData(uint8_t num){return  reciveBuf[num];}
	static bool reciveData(SerialPort *temPort);		//数据接收函数

	uint8_t getNumCounter(){return numCounter;}		 //获取计数器的值
	void resetNumCounter();												 //重设发送计数器
	void setErrorFlag(uint8_t);										 //设置错误编号
	void setErrorFlag_1(uint8_t);									 //设置错误编号
	void resetErrorFlag(){errorFlag=0;}		 				 //复位错误编号
	uint8_t getErrorFlag(){return errorFlag;}		   //获取错误编号

protected:
	SerialPort *port;			//串口号

	uint8_t frameHeader;	//帧头
	uint8_t addr;					//地址
	uint8_t command;			//命令字
	ctrData *data;				//数据的储存共用体
	uint8_t numCounter;		//发送计数器
	uint8_t errorFlag;    //错误编号
private:
	static uint8_t reciveBuf[PORT_AMOUNT][COMMAMD_LEN]; 	//数据的接收数组 
	static RingChain* reciveChin[PORT_AMOUNT];						//接收数据的中转链表
	inline uint8_t subChecksum();//计算校验和

	
};

#endif /* _BASE_CONTROL_H */


