/**
******************************************************************************
*文件：IoOut.cpp
*作者：孟浩
*版本：1.0
*日期：2015-03-09
*概要：IoOut类的实现
*备注：
******************************************************************************  
*/ 
	
#include "IoOut.h"
  
/**
*	@函数说明：  IoOut构造函数
*	@参数：		port	=	[GPIOA(默认),GPIOB,GPIOC,GPIOD,GPIOB,GPIOE,GPIOF,GPIOG]
*				Pin		=	[GPIO_Pin_0(默认)~GPIO_Pin_15]
*				bLevel	=	[false(默认)，true]
*	@返回值： 	无
*	@备注： 			
*/
IoOut::IoOut(GPIO_TypeDef *port, uint16_t pin, bool bLevel)
{
	ioOutPort=port;
	ioOutPin=pin;
	ioOutLevel = bLevel;
	
	initIo();
}


IoOut::~IoOut()
{
// 	delete ioOutPort;
}

/**
*	@函数说明：  初始化闭IO
*	@参数：		无
*	@返回值： 	无
*	@备注： 		PD0、PD1只工作在2MHz模式下
*/
void IoOut::initIo()
{
	//	PD0、PD1只工作在2MHz模式下
	if(ioOutPort==GPIOD&&(ioOutPin==GPIO_Pin_0||ioOutPin==GPIO_Pin_1))
		STM32_GpioOneInit(ioOutPin,GPIO_Speed_50MHz,GPIO_Mode_Out_PP,ioOutPort);	//推挽输出
	else
		STM32_GpioOneInit(ioOutPin,GPIO_Speed_10MHz,GPIO_Mode_Out_PP,ioOutPort);	//推挽输出
	
	setOff();
}

/**
*	@函数说明：  翻转Io的状态
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
void IoOut::reverseState()	
{
	 GPIO_WriteBit(ioOutPort, ioOutPin, (BitAction)(1 - GPIO_ReadOutputDataBit(ioOutPort, ioOutPin)));
}

/**
*	@函数说明：  开启IO
*	@参数：		无
*	@返回值： 	无
*	@备注： 		ioOutLevel为true时高电平有效，反之低电平有效
*/
void IoOut::setOn()
{
	if(ioOutLevel)
		GPIO_SetBits(ioOutPort, ioOutPin);
	else
		GPIO_ResetBits(ioOutPort, ioOutPin);
}	

/**
*	@函数说明：  关闭IO
*	@参数：		无
*	@返回值： 	无
*	@备注： 		ioOutLevel为true时低电平有效，反之高电平有效
*/
void IoOut::setOff()
{
	if(ioOutLevel)
		GPIO_ResetBits(ioOutPort, ioOutPin);
	else
		GPIO_SetBits(ioOutPort, ioOutPin);
}	

