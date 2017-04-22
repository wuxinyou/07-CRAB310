
/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：配置定时器的时间

*/
#ifndef __STM32_SYSTICK_H
#define __STM32_SYSTICK_H
#ifdef __cplusplus  
       extern "C" {  
#endif  
#include "stm32f4xx.h"

extern void STM32_SysTickInit(void); 

extern void SysTick_Delay(__IO uint32_t nTime);
extern void SysTick_TimingDelay_Decrement(void);
extern void SysTick_DelayUs(unsigned int time);
extern void SysTick_DelayMs(unsigned int time);
#ifdef __cplusplus  
        }  
#endif 	
#endif

