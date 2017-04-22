/**
  ******************************************************************************
	*文件：PowerControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电源管理协议的头文件
	*备注：
	*
  ******************************************************************************  
	*/ 

/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _POWER_CONTROL_H
#define _POWER_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 

class PowerControl : public BaseControl
{
public:
	PowerControl(SerialPort * p);
	virtual ~PowerControl();
	void sendPowerOnOffCommand();						//发送开关机命令
	void sendGetEctQuantityCommand(int8_t);					//发送电量读取命令
	void sendGetTemperatureCommand(uint8_t);					//发送电量读取命令PowerControl
	void sendGetTempCommand(int8_t);								//发送温度读取命令
	bool checkPowerKey();														//检测关机按键
	void shutDown(){powerDown=true;}
// 	bool getPowerReadState(){return powerReadState;}
private:
	bool powerReadState;														//关机状态
	bool powerDown;
	void sendPowerOffCommand();							//发送关机命令
	void sendPowerOnCommand();							//发送开机命令
};
#endif  /*_POWER_CONTROL_H */


