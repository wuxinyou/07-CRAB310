
/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：配置定时器的时间

*/
#include "STM32F4_SysTick.h"

uint32_t SysTick_TimingDelay;

void STM32_SysTickInit()   
{   
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}  
} 

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void SysTick_Delay(__IO uint32_t nTime)
{ 
  SysTick_TimingDelay = nTime;

  while(SysTick_TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void SysTick_TimingDelay_Decrement(void)
{
  if (SysTick_TimingDelay != 0x00)
  { 
    SysTick_TimingDelay--;
  }
} 


void SysTick_DelayUs(unsigned int time)
{    
   unsigned int i=0;  
   while(time--)
   {
      i=10;  		//尹工用的17 
      while(i--) ;    
   }
}

 

void SysTick_DelayMs(unsigned int time)
{    
   unsigned int i=0;  
   while(time--)
   {
      i=12000; 		 //尹工用的18000
      while(i--) ;    
   }
}



