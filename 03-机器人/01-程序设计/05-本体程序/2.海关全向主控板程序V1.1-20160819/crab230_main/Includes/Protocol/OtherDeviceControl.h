/**
  ******************************************************************************
	*文件：OtherDeviceControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：其他一些设备的控制协议类的头文件
	*备注：
  ******************************************************************************  
  */ 

/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _OTHER_DEVICE_CONTROL_H
#define _OTHER_DEVICE_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 
// #define RED 	false
// #define GREEN true

class OtherDeviceControl : public BaseControl
{
public:
	OtherDeviceControl(SerialPort * p);
	virtual ~OtherDeviceControl();
	void sendOtherDeviceCommand();							//发送其余设备控制命令
	void sendWeaponControlCommand();						//发送武器控制命令
	void sendGunControlCommand();						//发送武器控制命令

	void laserSightOn()			{setLaserSight(true);}
	void laserSightOff()		{setLaserSight(false);}
	void floodLightOn()			{setFloodLight(true);}
	void floodLightOff()		{setFloodLight(false);}
	void headLightOn()			{setheadLight(true);}
	void headLightOff()			{setheadLight(false);}
	void allLightOn()				{setFloodLight(true);setheadLight(true);}
	void allLightOff()			{setFloodLight(false);setheadLight(false);}
	void PowLedTrunRed()		{setPowerPilotLamp(false);}
	void PowLedTrunGreen()	{setPowerPilotLamp(true);}
	void setVideoSelect(uint8_t);
	void setVideoZoom(uint8_t);
private:
	bool floodLightFlag;
	bool headLightFlag;
	bool powerPilotLampFlag;
	bool laserSightFlag;
	uint8_t videoSelectFlag;
	uint8_t videoZoom;
	void setFloodLight(bool);
	void setheadLight(bool);
	void setPowerPilotLamp(bool);
	void setLaserSight(bool);
	
};
#endif  /*_OTHER_DEVICE_CONTROL_H */


