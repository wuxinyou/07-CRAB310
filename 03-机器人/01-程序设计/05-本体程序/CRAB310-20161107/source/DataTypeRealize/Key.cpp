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
Key::Key(GPIO_TypeDef *port,unsigned int Pin)
{
	keyPort=port;
	keyPin=Pin;
	if(port==GPIOA)
	{ 	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	}
	else if(port==GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  
	}
	else if(port==GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
	}
	else if(port==GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
	}
	else if(port==GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  
	}
	else if(port==GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  
	}
	else if(port==GPIOG)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
	}
	initKey();
}

/**
  * 功  能：按键类的析构函数
  * 参  数：无
  * 返回值：无
  */
Key::~Key()
{
	keyPort=NULL;
}

/**
  * 功  能：初始化灯的端口
  * 参  数：无
  * 返回值：无
  */
void Key::initKey()
{
	STM32_GpioOneInit(keyPin,GPIO_Speed_50MHz,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL,keyPort);    
}

/**
  * 功  能：返回按键值
  * 参  数：无
  * 返回值：
	* true:按键按下
	* false:按键没有按下，或者弹起了
  */
bool Key::getValue()
{
	return !GPIO_ReadInputDataBit(keyPort,keyPin);
}

