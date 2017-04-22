/**
  ******************************************************************************
	*文件：Timer.h
	*版本：2.0
	*日期：2013-06-17
	*概要：定时器类的头文件
	*备注：
  ******************************************************************************  
	*/ 
#ifndef _TIMER_H
#define _TIMER_H

#include <stdlib.h>			 
#include "stm32f10x.h"
#include "STM32_Priority.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:
	Timer(TIM_TypeDef *tim=TIM2,int timeNum=100);
	~Timer();
	
	void start();
	void stop();
	static void start(TIM_TypeDef*);
	static void stop(TIM_TypeDef*);
	static ITStatus getITStatus(TIM_TypeDef*);
	static void clearITPendingBit(TIM_TypeDef*);
	void setPriority(uint8_t,uint8_t);					//配置优先级
	void setTimeOut(int);								//定时时间长度 单位MS

private:
	int Tim_IRQn;										//中断号
	TIM_TypeDef* TimX;       							//定时器寄存器
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif



