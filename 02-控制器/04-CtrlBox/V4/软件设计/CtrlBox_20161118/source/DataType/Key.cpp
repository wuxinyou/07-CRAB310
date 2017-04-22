/**
  ******************************************************************************
	*文件：Key.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：按键类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 
#include "Key.h"

/**
  * 功  能：按键类的构造函数
  * 参  数：
	* 	port：按键引脚所在的GPIO端口
	*		Pin : 按键引脚号
  * 返回值：无
  */
Key::Key(GPIO_TypeDef *port,uint16_t Pin, bool bLevel)
{
	TrickCount	= 0;
	KeyPort		= port;
	KeyPin		= Pin;
	KeyLevel	= bLevel;
	FinalState	= KEY_PRESS_UP;
	
	initKey();
}

/**
  * 功  能：按键类的析构函数
  * 参  数：无
  * 返回值：无
  */
Key::~Key()
{
	KeyPort=NULL;
}

/**
  * 功  能：初始化灯的端口
  * 参  数：无
  * 返回值：无
  */
void Key::initKey()
{
	STM32_GpioOneInit(KeyPin,GPIO_Speed_2MHz,GPIO_Mode_IPU,KeyPort);	//上拉输入GPIO_Mode_IPU
}

/**
  * 功  能：返回按键值
  * 参  数：无
  * 返回值：无
  */
void Key::getValue()
{
	uint8_t TempState;//临时变量，存储当前读到的IO电平
	if(KeyLevel)
		TempState = !GPIO_ReadInputDataBit(KeyPort,KeyPin);
	else
		TempState = GPIO_ReadInputDataBit(KeyPort,KeyPin);
	
	if(FinalState!=TempState)//IO电平变化
	{
		TrickCount++;//TimerTick自加
		if(TrickCount>KEY_MAX_TIMER)//超过规定时间电平仍然不一样
		{
			FinalState=TempState;//更新IO电平
			TrickCount=0;//将时间重新设为0
		}
	}
	else//IO电平不变化
	{
		TrickCount=0;
	}
}

