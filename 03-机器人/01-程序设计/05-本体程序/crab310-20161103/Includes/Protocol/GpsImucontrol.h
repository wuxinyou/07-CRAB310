/**
  ******************************************************************************
	*文件：GpsImuControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-27
	*概要：GPS和IMU设备的控制协议类的头文件
	*备注：
  ******************************************************************************  
  */ 

/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _GPS_IMU_CONTROL_H
#define _GPS_IMU_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类

/* 类型定义 --------------------------------------------------------------------*/

/* 宏定义-----------------------------------------------------------------------*/ 
//用电池供电时误差2伏 用电池供电无误差
// #define SUB_VOLTAGE 10

#ifdef SUB_VOLTAGE 
	//正常工作电压>24伏 实际是26伏
	#define  NORMAL_VOLTAGE				(130-SUB_VOLTAGE)
	//警告电压>23伏 实际是25伏
	#define  WARNING_VOLTAGE			(125-SUB_VOLTAGE)
	//危险电压>22伏 实际是24伏
	#define  DANGER_VOLTAGE				(120-SUB_VOLTAGE)
	//失能电压>21伏 实际是23伏
	#define  DISABILITY_VOLTAGE		(115-SUB_VOLTAGE)
#else
	#define  NORMAL_VOLTAGE				130
	#define  WARNING_VOLTAGE			125
	#define  DANGER_VOLTAGE				120
	#define  DISABILITY_VOLTAGE		115
#endif


class GpsImuControl : public BaseControl
{
public:
	GpsImuControl(SerialPort * p);
	virtual ~GpsImuControl();
	void sendsetLEDColorCommand();
	void setPowerLEDColor(uint8_t);
	void setPowerLEDColorFromVoltage(uint8_t);
	
private:
	uint8_t powerLEDColor;
	
};
#endif  /*_GPS_IMU_CONTROL_H */


