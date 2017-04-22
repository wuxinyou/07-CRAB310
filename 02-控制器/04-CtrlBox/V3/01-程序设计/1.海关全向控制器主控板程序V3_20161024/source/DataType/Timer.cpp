/**
  ******************************************************************************
	*文件：Timer.c
	*版本：2.0
	*日期：2013-06-17
	*概要：定时器类的实现
  ******************************************************************************  
	*/ 
#include "Timer.h"

//判断TIM中断是否存在的宏
#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM4
#endif

#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM5
#define ENABLE_TIM6
#endif

#if defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM7
#endif

#if defined(STM32F10X_HD_VL)
#define ENABLE_TIM12
#define ENABLE_TIM13
#define ENABLE_TIM14
#endif

//定时器系数 该系数和系统时钟有关 当系统时钟重设后 修改该宏，同时修改成员函数setTimeOut，保证能够被 TIME_COEFFICIENT 整除
#define TIME_COEFFICIENT 72000

/**
  * 功  能：定时器类的构造函数
  * 参  数：
	* 	TIMX：定时器的控制寄存器
  * 返回值：无
  */
Timer::Timer(TIM_TypeDef *TIMX,int timeNum)//默认定时时间1ms 抢占和响应优先级都为最高
{
	TimX=TIMX;
	if(TimX==TIM2)
	{
		Tim_IRQn=TIM2_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}

	else if(TimX==TIM3)
	{
		Tim_IRQn=TIM3_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(TimX==TIM4)
	{
#ifdef ENABLE_TIM4
		Tim_IRQn=TIM4_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM5)
	{
#ifdef ENABLE_TIM5
		Tim_IRQn=TIM5_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM6)
	{
#ifdef ENABLE_TIM6
		Tim_IRQn=TIM6_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM7)
	{
#ifdef ENABLE_TIM7
		Tim_IRQn=TIM7_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
#else
		return;
#endif
	}

	else if(TimX==TIM12)
	{
#ifdef ENABLE_TIM12
		Tim_IRQn=TIM12_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM13)
	{
#ifdef ENABLE_TIM13
		Tim_IRQn=TIM13_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM14)
	{
#ifdef ENABLE_TIM14
		Tim_IRQn=TIM14_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
#else
		return;
#endif
	}
	else
		return;

	setTimeOut(timeNum);
	setPriority(0X00,0X00);//设置默认优先级为最高
	stop();
}

/**
  * 功  能：定时器类的析构函数
  * 参  数：无
  * 返回值：无
  */
Timer::~Timer()
{
	stop();
	delete TimX;
}

/**
  * 功  能：设置定时器的优先级
  * 参  数：
	*			Preemption：抢占优先级
	*			Sub				：响应优先级
  * 返回值：无
  */
void Timer::setPriority(uint8_t Preemption,uint8_t Sub)
{
	uint8_t temPreemptionPriority = Preemption;
	uint8_t temSubPriority = Sub;
	setIRQPriority(Tim_IRQn,temPreemptionPriority,temSubPriority);
}

/**
  * 功  能：设置定时器溢出响应时间
  * 参  数：待设定的时间
  * 返回值：无
	* 备  注：定时时间计算((1+TIM_Prescaler )/74M)*(1+TIM_Period )=((1+7299)/72M)*(1+9999)=1秒 
  */
void Timer::setTimeOut(int interval_ms)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	uint8_t RepetitionCounter=0x00; 	//重复次数
	uint32_t Period=0x00;						//周期
	uint16_t Prescaler=0x00;				 	//预分屏
	if(interval_ms<1)
		return;
	if(interval_ms>0&&interval_ms<5)//1-5 ms
	{
		Prescaler=224;
	}	
	else if(interval_ms>4&&interval_ms<10)//5-10 ms
	{
		Prescaler=449;
	}			
	else if(interval_ms>9&&interval_ms<50)//10-50ms
	{
		Prescaler=899;
	}		
	else if(interval_ms>49&&interval_ms<100)//50-100ms
	{
		Prescaler=1799;
	}			
	else if(interval_ms>99&&interval_ms<500)//100-500ms
	{
		Prescaler=3599;
	}			
	else if(interval_ms>499&&interval_ms<3000)//500-1000ms
	{
		Prescaler=7199;
	}
	else if(interval_ms>2999&&interval_ms<5000)//1-5s
	{
		Prescaler=14399;
	}	
	else //>5s
	{
		Prescaler=35999;
	}	
	
	Period=(TIME_COEFFICIENT*interval_ms)/(1+Prescaler)-1;

	TIM_TimeBaseStructure.TIM_Period =(uint16_t)Period;
	TIM_TimeBaseStructure.TIM_Prescaler =(uint16_t)Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision =(uint16_t)TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =(uint16_t)TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter =(uint8_t)RepetitionCounter;

	TIM_TimeBaseInit(TimX, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TimX, TIM_FLAG_Update);						//清除定时器中断标志
	TIM_ITConfig(TimX, TIM_IT_Update, ENABLE);
}


/**
  * 功  能：打开定时器
  * 参  数：无
  * 返回值：无
  */
void Timer::start()
{
	TIM_Cmd(TimX, ENABLE);
}

/**
  * 功  能：停止定时器
  * 参  数：无
  * 返回值：无
  */
void Timer::stop()
{
	TIM_Cmd(TimX, DISABLE);
}

/**
  * 功  能：打开定时器
  * 参  数：定时器的寄存器
  * 返回值：无
  */
void Timer::start(TIM_TypeDef* Tx)
{
	TIM_TypeDef *temTX=Tx;
	TIM_Cmd(temTX, ENABLE);
}

/**
  * 功  能：停止定时器
  * 参  数：定时器的寄存器
  * 返回值：无
  */
void Timer::stop(TIM_TypeDef* Tx)
{
	TIM_TypeDef *temTX=Tx;
	TIM_Cmd(temTX, DISABLE);
}

/**
  * 功  能：获取定时器的工作状态
  * 参  数：定时器的寄存器
  * 返回值：无
  */
ITStatus Timer::getITStatus(TIM_TypeDef* Tx)
{
	TIM_TypeDef* temTx=Tx;
	return TIM_GetITStatus(temTx, TIM_IT_Update);
}

/**
  * 功  能：清除中断标志位
  * 参  数：定时器的寄存器
  * 返回值：无
  */
void Timer::clearITPendingBit(TIM_TypeDef* Tx)
{
	TIM_TypeDef* temTx=Tx;
	TIM_ClearITPendingBit(temTx , TIM_FLAG_Update);
}

