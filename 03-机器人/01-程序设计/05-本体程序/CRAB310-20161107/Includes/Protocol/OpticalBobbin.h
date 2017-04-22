/**
  ******************************************************************************
	*文件：OpticalBobbin.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-27
	*概要：GPS和IMU设备的控制协议类的头文件
	*备注：
  ******************************************************************************  
  */ 

/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _OPTICAL_BOBBIN_H  
#define _OPTICAL_BOBBIN_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 

class OpticalBobbin : public BaseControl
{
public:
	OpticalBobbin(SerialPort * p);
	virtual ~OpticalBobbin();
	void setWorkStatus(uint8_t status){workStatus=status;}
	void setLeftSpeed(uint8_t speed){leftSpeed=speed;}
	void setRightSpeed(uint8_t speed){rightSpeed=speed;}
	void setWireLength(uint8_t length){wireLength=length;}
	uint8_t getWireLength(){return wireLength;}
	
	void sendOpticalBobbinCommand();

private:
	uint8_t workStatus;		//线缆盘的控制状态
	uint8_t wireLength;		//线长，指留在盘中的线长
	uint8_t speed;				//自动线缆盘的放线速度
	uint8_t leftSpeed;		//右电机速度
	uint8_t rightSpeed;		//右电机速度
};
#endif  /*_OPTICAL_BOBBIN_H */


