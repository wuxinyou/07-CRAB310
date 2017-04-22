/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"  
#include "system_stm32f4xx.h"
#include "STM32F4_LedDisp.h"
#include "STM32F4_Config.h"
#include "STM32F4_GpioInit.h"
#include "STM32F4_UsartInit.h"
#include "STM32F4_TimInit.h" 
#include "XbotSysCtrl.h"
#include "XbotCtrlDriver.h"

#include "STM32F4_DriverInit.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	

int main(void)
{ 
// 	SystemInit();
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);

	
	STM32_LedDispInit();    				//ok
	STM32_GpioInit();
// 	_init_alloc(0x3000, 0x8000);
// 	if(false == XbotSysCtrlInit(&XBOT_SYS_CTRL_PARA))
// 		while(1);

// 	STM32_InitUsart1(38400);	//ok//机械臂
// 	STM32_InitUsart2(38400);	//ok//底盘3个电机与电源管理
// 	  STM32_InitUsart3(19200);	//ok//后舱GPS和主板IMU
// 		STM32_InitUsart4(19200);	//ok//有线
// 		s1=CreatSerialPort(4,19200);
// 		s2=CreatSerialPort(3,19200);

// 		if(xbotdatainit())
// 			LED1_OFF;
// 	STM32_InitUsart5(115200);	//ok//绝对编码器
// 		STM32_InitUsart5(38400);	//ok//绝对编码器
// 	STM32_InitUsart6(19200);	//ok//无线 
// 	
// 	
 	STM32_Tim2Init();		//初化TIM2,作为系统采样周期1ms
 	STM32_Tim3Init();		//初化TIM2,作为系统采样周期10ms
//	STM32_Tim4Init();		//初化TIM2,作为系统采样周期100ms
  
 	STM32_ENABLE_TIM2;
 	STM32_ENABLE_TIM3
//	STM32_ENABLE_TIM4;
 
// 	LIGHT_OFF;				//前向照明灯
// 	POW_ON;					//电源开启

	while(1)
	{  
	  
	}
}



// // #ifdef  USE_FULL_ASSERT

// // /**
// //   * @brief  Reports the name of the source file and the source line number
// //   *         where the assert_param error has occurred.
// //   * @param  file: pointer to the source file name
// //   * @param  line: assert_param error line source number
// //   * @retval None
// //   */
// // void assert_failed(uint8_t* file, uint32_t line)
// // { 
// //   /* User can add his own implementation to report the file name and line number,
// //      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

// //   /* Infinite loop */
// //   while (1)
// //   {
// //   }
// // }
// // #endif

// // /**
// //   * @}
// //   */ 

// // /**
// //   * @}
// //   */ 

// // /******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
// /* Includes ------------------------------------------------------------------*/

// #include "stm32f4xx.h"  
// #define __LED1_PIN	GPIO_Pin_0
// #define __LED2_PIN	GPIO_Pin_1
// #define __LED1_PORT	GPIOC
// #define __LED2_PORT	GPIOC

// void TIM4_IRQHandler(void)
// {
// 	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
// 	{
// 		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
// 		TIM_Cmd(TIM4, DISABLE);	
// 		GPIO_WriteBit(__LED1_PORT, __LED1_PIN, (BitAction)(1 - GPIO_ReadOutputDataBit(__LED1_PORT, __LED1_PIN)));
// 		TIM_Cmd(TIM4, ENABLE); 
// 	}	
// }		
// 	
// 	
// int main(void)
// {
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

// #ifdef __LED1_PIN	 
// 	 
//   GPIO_InitStructure.GPIO_Pin = __LED1_PIN;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//   GPIO_Init(__LED1_PORT, &GPIO_InitStructure);
// #endif
// #ifdef __LED2_PIN	 
// 	 
//   GPIO_InitStructure.GPIO_Pin = __LED2_PIN;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//   GPIO_Init(__LED2_PORT, &GPIO_InitStructure);
// #endif

// 	

// 	/* System Clocks Configuration */
// 	{		
// 		/* TIM2 clock enable */
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
// 	}
//   	/* NVIC Configuration */
// 	{	
// 		/* Enable the TIM2 global Interrupt */
// 		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
// 		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级 0
// 		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			 //响应优先级 2
// 		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
// 		NVIC_Init(&NVIC_InitStructure);
// 	}

// 	/* ---------------------------------------------------------------
// 	TIM2 Configuration: Output Compare Timing Mode:
// 	Frequency=(SYSCLK/(Prescaler+1)) /(Period+1)
// 	APB1 = 72/4=18MHz
// 	TIM2 counter clock at 10 KHz
// 	CC1 update rate = TIM2 counter clock / CCR1_Val = 100 Hz
// 	
// 	--------------------------------------------------------------- */
// 	TIM_TimeBaseStructure.TIM_Period = 9999;
// // 	TIM_TimeBaseStructure.TIM_Prescaler = (SYS_FREQ_TIM2_7/SYS_FREQ_1KHz)-1;
// 	
// 	TIM_TimeBaseStructure.TIM_Prescaler = 8399;
// 	
// 	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

//  	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
// 	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
// 	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
// 	
// 	TIM_Cmd(TIM4, DISABLE);
// 	TIM_Cmd(TIM4, ENABLE);
// //	LIGHT_OFF;				//前向照明灯
// //	POW_ON;					//电源开启

// 	while(1)
// 	{  
// 	  
// 	}
// }
