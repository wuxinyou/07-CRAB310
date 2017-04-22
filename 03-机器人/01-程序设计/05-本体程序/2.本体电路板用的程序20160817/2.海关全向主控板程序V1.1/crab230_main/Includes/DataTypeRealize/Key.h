/**
  ******************************************************************************
	*文件：Key.h
	*版本：2.0
	*日期：2013-06-17
	*概要：按键类的头文件
	*备注：
	*
  ******************************************************************************  
	*/ 
#ifndef _KEY_H
#define _KEY_H

#include <stdlib.h>
// 	#include <stdbool.h>	
#include "stm32f4xx_gpio.h"
#include "STM32F4_GpioInit.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Key
{
public:
	Key(GPIO_TypeDef *port,unsigned int Pin);
	~Key();
	bool getValue(void);//获取按键是否按下 ,按下为true，没按下为false
private:
	void initKey();
	GPIO_TypeDef *keyPort;
	unsigned int keyPin;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif



