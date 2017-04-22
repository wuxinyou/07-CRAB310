/**
  ******************************************************************************
	*文件：PowerControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电源管理协议的实现
	*备注：关机命令和开机命令暂时没用到
	*
  ******************************************************************************  
	*/ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "PowerControl.h"
#include "STM32F4_GpioInit.h"
/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 
#define SW_ST_ON	   	1
#define SW_ST_OFF	   	0 
#define NOTSURE_MCU   2
#define SWCTRL_MAX_TIMER   100        //定义最大比较值
#define TURNOFF_BUT GPIO_ReadInputDataBit(__GPIO_IN1_PORT, __GPIO_IN1_PIN)

//PowerControl类构造函数
PowerControl::PowerControl(SerialPort * p):BaseControl(p)
{
	addr=0X03;
	command|=0X30;
	powerDown=false;
	powerReadState=false;
}

//PowerControl类析构函数
PowerControl::~PowerControl()
{
	
}
//a4 00 01 00 00 a5
/**
  * 功  能：发送关机命令到电源控制板，返回OK
  * 参  数：无
  * 返回值：无
  * 
  */
void PowerControl::sendPowerOffCommand()								//发送关机命令
{
	command&=0xf0;
	command|=0X01;
	data->DATA_16=0x2222;
	sendCommand();	//命令内容设置完毕，发送命令
}

/**
  * 功  能：发送开机命令到电源控制板，返回OK
  * 参  数：无
  * 返回值：无
  * 
  */
void PowerControl::sendPowerOnCommand()							//发送开机命令
{
	command&=0xf0;
	command|=0X01;
	data->DATA_16=0x1111;
	sendCommand();	//命令内容设置完毕，发送命令
}

/**
  * 功  能：发送开关机命令到电源控制板，返回OK
  * 参  数：无
  * 返回值：无
  * 
  */
void PowerControl::sendPowerOnOffCommand()						//发送开关机命令
{
	if(powerDown)
	{
// 		sendPowerOffCommand();								//发送关机命令
		POW_OFF;
	}
	else
	{
// 		sendPowerOnCommand();									//发送开机命令
		POW_ON;		
	}
}
/**
  * 功  能：发送电池电量获取指令到电源控制板
  * 参  数：电池编号
	* 参数值：0x00:电池1
	*					0x01:电池2
	*					0x02:电池3
	*					0x03:电池4
  * 返回值：无
  */
void PowerControl::sendGetEctQuantityCommand(int8_t batteryNum)					//发送电量读取命令
{
	command&=0xf0;
	command|=0X02;
	data->DATA_16=0x0000;
	data->DATA_8[0]=batteryNum;
// 	data->DATA_8[1]=(batteryNum<<6);
	sendCommand();	//命令内容设置完毕，发送命令
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}
/**
  * 功  能：发送温度获取指令到电源控制板
  * 参  数：电机编号
	* 参数值：0x00:电机1
	*					0x01:电机2
	*					0x02:电机3
  * 返回值：无
  */
void PowerControl::sendGetTemperatureCommand(uint8_t motorNum)					//发送温度读取命令
{
	command&=0xf0;
	command|=0X03;
	data->DATA_16=0x0000;
	data->DATA_8[0]=motorNum;
	data->DATA_8[1]=0;
	sendCommand();	//命令内容设置完毕，发送命令
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * 功  能：发送温度获取指令到电源控制板
  * 参  数：电机编号
	* 参数值：0x00:电机1
	*					0x01:电机2
	*					0x02:电机3
  * 返回值：无
  */
void PowerControl::sendGetTempCommand(int8_t moterNum)									//发送温度读取命令
{
	command&=0xf0;
	command|=0X03;
	data->DATA_16=0x0000;
	data->DATA_8[1]=(moterNum<<6);
	sendCommand();	//命令内容设置完毕，发送命令
}

/**
  * 功  能：检测电源按键是否按下
  * 参  数：无
  * 返回值：
	*  	true: 按下
  * 	false:没按下
  */
bool PowerControl::checkPowerKey()								//检测关机按键
{
	static unsigned char SwTimerTick = 0;
	static unsigned char SwPreState= NOTSURE_MCU;		//表示前一时刻按键状态,默认情况下没有按键按下 2
	unsigned char SwReadState=0;											//定义一个中间变量，起到传参的作用

	SwReadState = TURNOFF_BUT; 											//读取八位PA口数据 0 or 1
	if(SwPreState != SwReadState)
	{
		if(SwTimerTick>SWCTRL_MAX_TIMER)
		{
			SwPreState = SwReadState;
			if(SwPreState == SW_ST_OFF)
			{   
        powerReadState = true;
				//LED1_ON;
			}
			else
			{  
        powerReadState = false;    
				//LED1_OFF;
			}
		}
		else
		{
			SwTimerTick++;
    }	
	}
	else
	{
    SwTimerTick=0;
  }
	return powerReadState;
}




