/**
  ******************************************************************************
	*文件：STM32F4_IRQ_INIT.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：定时器中断函数的实现
	*备注：
	*
  ******************************************************************************  
	*/ 
//定时器函数

#include "STM32F4_IRQ_INIT.H"
// #include "LEDLighter.h"

// static LEDLighter *led = new LEDLighter(GPIOC,GPIO_Pin_0);//默认点亮

extern "C" {
//1ms 触发一次
/******************************  TIM2_IRQHandler *************************************/
void TIM2_IRQHandler(void)
{ 
// 	static int index=0;
	if (Timer::getITStatus(TIM2)!= RESET) 
	{
		Timer::clearITPendingBit(TIM2);
		Timer::stop(TIM2);	
		myApp->runOnTime2();
		Timer::start(TIM2);
	}
}

//10ms触发一次
/******************************  TIM3_IRQHandler *************************************/
void TIM3_IRQHandler(void)
{
	if (Timer::getITStatus(TIM3)!= RESET)
	{ 
		Timer::clearITPendingBit(TIM3);
		Timer::stop(TIM3);
		myApp->runOnTime3();
		Timer::start(TIM3);
	}
 
}

//100ms触发一次
/******************************  TIM4_IRQHandler *************************************/

void TIM4_IRQHandler(void)
{
	if (Timer::getITStatus(TIM4)!= RESET)
	{
		Timer::clearITPendingBit(TIM4);
		Timer::stop(TIM4);
		myApp->runOnTime4();
// 		WatchDag::feedDog();	//喂狗 每100MS喂狗一次 超时值为2000毫秒
		Timer::start(TIM4);
	}	
}

}

