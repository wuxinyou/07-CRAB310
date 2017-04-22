/**
  ******************************************************************************
	*文件：CodedDiscControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：码盘协议类头文件
	*备注：
	*
  ******************************************************************************  
	*/ 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _CODED_DISC_CONTROL_H
#define _CODED_DISC_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
// #include "BaseControl.h"     //协议的基类
#include "SerialPort.h"
#ifdef __cplusplus  
extern "C"
{
#endif
#include "STM32_Adc.h"
#ifdef __cplusplus  
}
#endif
/* 类型定义 --------------------------------------------------------------------*/
typedef union{
        uint16_t DATA_U16;
				int16_t DATA_16;
        unsigned char DATA_8[2];
}CodeDiscData;

/* 宏定义-----------------------------------------------------------------------*/ 

class CodedDiscControl
{
public:
	CodedDiscControl(SerialPort * p);
	virtual ~CodedDiscControl();

	void sendCodeDiscCommand();							//发送速度命令 参数：命令编号（命令的类型）
	bool reciveData();

	CodeDiscData * getCylinder(){return  cylinder;}
	CodeDiscData * getAngle(){return  angle;}


	void resetNumCounter();												 //重设发送计数器
	void setErrorFlag(uint8_t);										 //设置错误编号
	void setErrorFlag_1(uint8_t);									 //设置错误编号

	void resetErrorFlag(){errorFlag=0;}		 				 //复位错误编号
	uint8_t getNumCounter(){return numCounter;}		 //获取计数器的值
	uint8_t getErrorFlag(){return errorFlag;}		   //获取错误编号
	uint16_t getADCAngle();
	void initADC();
private:
	SerialPort *port;
	CodeDiscData *cylinder;
	CodeDiscData *angle;
	uint8_t numCounter;		//发送计数器
	uint8_t errorFlag;    //错误编号
	uint16_t ADCangle;
};
#endif  /*_CODED_DISC_CONTROL_H */


