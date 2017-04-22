/**
  ******************************************************************************
	*文件：OtherDeviceControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：其他一些设备的控制协议类的实现
	*备注：
  ******************************************************************************  
  */ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "OtherDeviceControl.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 

//OtherDeviceControl类构造函数
OtherDeviceControl::OtherDeviceControl(SerialPort * p):BaseControl(p)
{
	addr=0X09;
	command|=0X31;
	floodLightFlag=false;
	headLightFlag=false;
	powerPilotLampFlag=false;
	laserSightFlag=false;
}

//OtherDeviceControl类析构函数
OtherDeviceControl::~OtherDeviceControl()
{
	
}

/**
  * 功  能：发送武器控制命令
  * 参  数：无
  * 返回值：无
  * 
  */
void OtherDeviceControl::sendWeaponControlCommand()
{
	uint8_t weaponCommand[6]={0XA4,0X09,0X32,0XB5,0XF5,0X89};
	port->write(weaponCommand,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * 功  能：发送武器控制命令
  * 参  数：无
  * 返回值：无
  * 
  */
void OtherDeviceControl::sendGunControlCommand()
{
	uint8_t weaponCommand[6]={0XA4,0X09,0X32,0XA5,0XE5,0X69};
	port->write(weaponCommand,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * 功  能：发送其余设备控制命令
  * 参  数：无
  * 返回值：无
  * 
  */
void OtherDeviceControl::sendOtherDeviceCommand()							//发送其余设备控制命令
{
	data->DATA_16=0x0000;
	if(powerPilotLampFlag)
		data->DATA_8[1]|=0x01;
	else
		data->DATA_8[1]&=0xfe;
	
	if(laserSightFlag)
		data->DATA_8[1]|=0x20;
	else
		data->DATA_8[1]&=0xdf;
	
	if(floodLightFlag)
		data->DATA_8[1]|=0x40;
	else
		data->DATA_8[1]&=0xbf;
	
	if(headLightFlag)
		data->DATA_8[1]|=0x80;
	else
		data->DATA_8[1]&=0x7f;
	
	data->DATA_8[0]|=videoZoom;
	data->DATA_8[0]|=(uint8_t)(videoSelectFlag<<5);
	sendCommand();	//命令内容设置完毕，发送命令
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}


/**
  * 功  能：设置四分屏图像选择
  * 参  数：控制数据
	* 参数值：0x00:云台图像显示
	*					0x01:手抓图像显示
	*					0x02:前视图像显示
	*					0x03:后视图像显示
	*					0x04:四分屏图像显示
  * 返回值：无
  */
void OtherDeviceControl::setVideoSelect(uint8_t value)
{
	if(value<5)
		videoSelectFlag=value;
}
/**
  * 功  能：设置云台图像变焦倍数
  * 参  数：变焦倍数
  * 返回值：无
  */
void OtherDeviceControl::setVideoZoom(uint8_t value)
{
	if(value<32)
		videoZoom=value;
}

/**
  * 功  能：设置照明灯的亮灭状态
  * 参  数：控制数据
	* 参数值：false:照明灯熄灭
	*					true :照明灯点亮
  * 返回值：无
  */
void OtherDeviceControl::setFloodLight(bool value)
{
	floodLightFlag=value;
}

/**
  * 功  能：设置云台照明灯的亮灭状态
  * 参  数：控制数据
	* 参数值：false:云台照明灯熄灭
	*					true :云台照明灯点亮
  * 返回值：无
  */
void OtherDeviceControl::setheadLight(bool value)
{
	headLightFlag=value;
}

/**
  * 功  能：设置激光瞄准亮灭的状态
  * 参  数：控制数据
	* 参数值：false:激光瞄准灯熄灭
	*					true :激光瞄准灯点亮
  * 返回值：无
  */
void OtherDeviceControl::setLaserSight(bool value)
{
	laserSightFlag=value;
}
/**
  * 功  能：设置电源指示灯的颜色
  * 参  数：控制数据
	* 参数值：false:电源指示灯的颜色变红
	*					true :电源指示灯的颜色变绿
  * 返回值：无
  */
void OtherDeviceControl::setPowerPilotLamp(bool value)
{
	powerPilotLampFlag=value;
}

