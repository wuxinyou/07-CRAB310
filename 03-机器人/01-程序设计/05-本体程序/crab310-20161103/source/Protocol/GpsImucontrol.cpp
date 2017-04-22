/**
  ******************************************************************************
	*文件：GpsImuControl.c
	*作者：叶依顺
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-27
	*概要：GPS和IMU设备的控制协议类的实现
	*备注：
  ******************************************************************************  
  */ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "GpsImuControl.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 
#define POWER_LED_CTR 0X07

#define GREEN 		0X01
#define RED 			0X02
#define NO_COLOR 	0X03


GpsImuControl::GpsImuControl(SerialPort * p):BaseControl(p)
{
	powerLEDColor=GREEN;
}
//OtherDeviceControl类析构函数
GpsImuControl::~GpsImuControl()
{
	
}

/**
  * 功  能：设置电源灯的颜色
  * 参  数：
	*		color ：灯的颜色参数
  * 返回值：无
  * 
  */
void GpsImuControl::setPowerLEDColor(uint8_t color)
{
	powerLEDColor=color;
}

/**
  * 功  能：根据电压值设置电源指示灯的颜色
  * 参  数：
	*		voltage ：电压值参数 
  * 返回值：无
  * 
  */
// bool GpsImuControl::setPowerLEDColorFromVoltage(uint8_t voltage)
// {
// 	static uint8_t index=0;
// 	
// 	if(voltage>NORMAL_VOLTAGE)//亮绿灯
// 	{
// 		setPowerLEDColor(GREEN);
// 		index=0;
// 	}
// 	else if(voltage>WARNING_VOLTAGE)//绿灯和红灯交替亮
// 	{
// 		if(powerLEDColor==GREEN)
// 			setPowerLEDColor(RED);
// 		else
// 			setPowerLEDColor(GREEN);
// 		index=0;
// 	}
// 	else if(voltage>DANGER_VOLTAGE)//亮红灯
// 	{
// 		setPowerLEDColor(RED);
// 		index=0;
// 	}
// 	else //红灯闪
// 	{
// 		if(powerLEDColor==NO_COLOR)
// 			setPowerLEDColor(RED);
// 		else
// 			setPowerLEDColor(NO_COLOR);
// 		index++;
// 	}
// 	if(index>20)
// 	{
// 		index=0;
// 		return true;
// 	}
// 	else 
// 		return false;
// }
           void GpsImuControl::setPowerLEDColorFromVoltage(uint8_t voltage)
{
	if(voltage>130)//绿灯全亮 130 127 124 121 118 
	{
		setPowerLEDColor(5);
	}
	else if(voltage>127)
	{
		setPowerLEDColor(4);
	}
	else if(voltage>124)
	{
		setPowerLEDColor(3);
	}
	else if(voltage>121)
	{
		setPowerLEDColor(2);
	}
	else if(voltage>118)
	{
		setPowerLEDColor(1);
	}
	else
	{
		setPowerLEDColor(0);
	}
}

void GpsImuControl::sendsetLEDColorCommand()
{
	uint8_t Command[6]={0xA4, 0x01, 0x17, 0x00, 0x00, 0x00};
	Command[4]=powerLEDColor;
	Command[5]=0xBC+Command[4];
	port->write(Command,6);
}






