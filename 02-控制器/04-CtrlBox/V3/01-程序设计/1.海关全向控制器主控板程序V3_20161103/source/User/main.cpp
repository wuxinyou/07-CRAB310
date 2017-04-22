/**
  ******************************************************************************
	*文件：main.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：主程序的入口
	*备注：
	*
  ******************************************************************************  
	*/ 
	
/* 宏定义-----------------------------------------------------------------------*/ 	

#include "Process.h"

#define CLI()     __set_PRIMASK(1) 							//	关闭总中断
#define SEI()     __set_PRIMASK(0) 							//	打开总中断

#define	__LEDSYS_PORT	GPIOA								//	系统指示灯端口
#define	__LEDSYS_PIN	GPIO_Pin_11							//	系统指示灯引脚号
//全局变量
Process *process;
IoOut *ledSys;

int main(void)
{ 
	CLI();
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);		//	中断优先级分组
	SysTick_Init();											//	SysTick初始化
	SysTick_DelayMs(20);								
	ledSys = new IoOut(__LEDSYS_PORT,__LEDSYS_PIN);
	ledSys->setOn();
	process = new Process();
	process->openPeriph();

	SEI();
	
	while(1)
	{  	
//		SysTick_DelayMs(1000);
//		ledSys->reverseState();
	}
}

/**/
extern "C" {
	void TIM2_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM2)!= RESET) 
		{
			Timer::clearITPendingBit(TIM2);
			Timer::stop(TIM2);
				process->runOnTime2();
			Timer::start(TIM2);
		}
	}
	void TIM3_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM3)!= RESET) 
		{
			Timer::clearITPendingBit(TIM3);
			Timer::stop(TIM3);
				process->runOnTime3();
			Timer::start(TIM3);
		}
	}
	void TIM4_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM4)!= RESET) 
		{
			Timer::clearITPendingBit(TIM4);
			Timer::stop(TIM4);
				process->runOnTime4();
			Timer::start(TIM4);
		}
	}

	/**
	  * @函数说明：  	该中断函数处理NMI异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当NMI出现故障时,异常指示灯ledSys关闭
	  */
	void NMI_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @函数说明：  	该中断函数处理硬故障异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当硬件出现故障时,异常指示灯ledSys以200毫秒的频率闪烁
	  */
	void HardFault_Handler(void)
	{
		/* 当产生硬件错误异常时进入死循环 */
	  while (1)
	  {
			SysTick_DelayMs(100);
			ledSys->reverseState();
	  }
	}

	/**
	  * @函数说明：  	该中断函数处理内存管理异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当内存管理出现故障时,异常指示灯ledSys以500毫秒的频率闪烁
	  */
	void MemManage_Handler(void)
	{
	  /* 当产生内存管理异常时进入死循环 */
		ledSys->setOff();
	  while (1)
	  {
			SysTick_DelayMs(500);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @函数说明：  	该中断函数处理总线故障异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当总线出现故障时,异常指示灯ledSys以1秒的频率闪烁
	  */
	void BusFault_Handler(void)
	{
	  /* 当产生总线异常时进入死循环 */
	  while (1)
	  {
			SysTick_DelayMs(1000);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @函数说明：  	该中断函数处理使用故障异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当使用出现故障时,异常指示灯ledSys以2秒的频率闪烁
	  */
	void UsageFault_Handler(void)
	{
	  /* 当产生使用错误异常时进入死循环 */
	  while (1)
	  {
			SysTick_DelayMs(2000);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @函数说明：  	该中断函数处理SVCcall故障异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当SVCcall出现故障时,异常指示灯ledSys熄灭
	  */
	void SVC_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @函数说明：  	该中断函数处理调试监视故障异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当调试监视出现故障时,异常指示灯ledSys熄灭
	  */
	void DebugMon_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @函数说明：  	该中断函数处理PendSVC异常
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			当PendSVC出现故障时,异常指示灯ledSys熄灭
	  */
	void PendSV_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @函数说明：  	该中断函数处理系统1ms时钟
	  * @参数：			无
	  * @返回值： 		无
	  *	@备注： 			该中断不受CLI()影响，开关系统总中断对其没有影响
	  */
	void SysTick_Handler(void)
	{
		  
	}

}



