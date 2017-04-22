/**
  ******************************************************************************
	*文件：LEDLighter.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：LED灯类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 
	
#include "LEDLighter.h"
LEDLighter::LEDLighter(GPIO_TypeDef *port,unsigned int Pin)
{
	lighterPort=port;
	lighterPin=Pin;
	if(port==GPIOA)
		portNumber=0;
	else if(port==GPIOB)
		portNumber=1;
	else if(port==GPIOC)
		portNumber=2;
	else if(port==GPIOD)
		portNumber=3;
	else if(port==GPIOE)
		portNumber=4;
	else if(port==GPIOF)
		portNumber=5;
	else if(port==GPIOG)
		portNumber=6;
	else if(port==GPIOH)
		portNumber=7;
	else if(port==GPIOI)
		portNumber=8;
	initLighter();
}

LEDLighter::~LEDLighter()
{
// 	delete lighterPort;
}

/**
  * 功  能：初始化灯的端口
  * 参  数：无
  * 返回值：无
  */
void LEDLighter::initLighter()
{
	RCC_AHB1PeriphClockCmd(((uint32_t)(0x01<<portNumber)), ENABLE);
	STM32_GpioOneInit(lighterPin,GPIO_Speed_2MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,lighterPort);	
}

/**
  * 功  能：翻转等的亮灭状态
  * 参  数：无
  * 返回值：无
  */
void LEDLighter::reverseLight()	//翻转灯的状态
{
	 GPIO_WriteBit(lighterPort, lighterPin, (BitAction)(1 - GPIO_ReadOutputDataBit(lighterPort, lighterPin)));
}

/**
  * 功  能：设置等的亮灭
  * 参  数：
	*			true:点亮
	*			false:熄灭
  * 返回值：无
  */
void LEDLighter::setLightStatus(bool light)
{
	if(light)
		GPIO_ResetBits(lighterPort, lighterPin);
	else
		GPIO_SetBits(lighterPort, lighterPin);
}
