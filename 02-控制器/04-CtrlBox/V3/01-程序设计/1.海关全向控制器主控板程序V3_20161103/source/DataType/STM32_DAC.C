
/* Includes ------------------------------------------------------------------*/

#include "STM32_DAC.h"



//void STM32_DacInit(void)
//{
//	DAC_InitTypeDef	DAC_InitStructure;
//
//  /* System clocks configuration ---------------------------------------------*/
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
//	RCC_ClockCmdGpio_DAC;
//  
//  /* GPIO configuration ------------------------------------------------------*/
//	STM32_GpioOneInit(__GPIO_DAC1_PIN,GPIO_Speed_50MHz,GPIO_Mode_AIN,__GPIO_DAC1_PORT);
//	STM32_GpioOneInit(__GPIO_DAC2_PIN,GPIO_Speed_50MHz,GPIO_Mode_AIN,__GPIO_DAC2_PORT);
//
//
//  /* DAC configuration ----------------------------------------------*/
//  	DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software;					//软件触发
//	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	    	//禁止波形发生器
//	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;			//禁止输出缓冲
//	DAC_Init(DAC_Channel_1, &DAC_InitStructure);							//DAC1初始化
//	DAC_Init(DAC_Channel_2, &DAC_InitStructure);							//DAC2初始化
//
//	DAC_Cmd(DAC_Channel_1, ENABLE);			/* Enable DAC Channel1*/       
//	DAC_Cmd(DAC_Channel_2, ENABLE);			/* Enable DAC Channel2*/
//  	
//}
//
//void STM32_DacSetValue(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
//{
//	DAC_SetDualChannelData(DAC_Align, Data2, Data1);
//	DAC_DualSoftwareTriggerCmd(ENABLE);
//}
//
//
//
//	 
//
//
//
//
//
//
//
