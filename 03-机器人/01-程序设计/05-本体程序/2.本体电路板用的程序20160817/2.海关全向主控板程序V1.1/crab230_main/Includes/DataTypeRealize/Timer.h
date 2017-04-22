/**
**********************************************************************************************************************
*
*
*
*
*
**********************************************************************************************************************
*/
#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus  
extern "C"
{
#endif
	#include <stdlib.h>			 
	#include "STM32F4_PriorityControl.h"
#ifdef __cplusplus
}
#endif
#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:
	Timer(TIM_TypeDef *);
	~Timer();
	void setTimeOut(int);					//定时时间长度 单位MS
	void start();
	void stop();
	static void start(TIM_TypeDef*);
	static void stop(TIM_TypeDef*);
	static ITStatus getITStatus(TIM_TypeDef*);
	static void clearITPendingBit(TIM_TypeDef*);
	void setPriority(uint8_t,uint8_t);

private:
	int Tim_IRQn;
	uint8_t RepetitionCounter; 	//重复次数
	uint32_t Period;						//周期
	uint16_t Prescaler;				 	//预分屏
	TIM_TypeDef* TimX;       		//定时器寄存器
	uint8_t PreemptionPriority; //抢占优先级
	uint8_t SubPriority;        //响应优先级

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif



