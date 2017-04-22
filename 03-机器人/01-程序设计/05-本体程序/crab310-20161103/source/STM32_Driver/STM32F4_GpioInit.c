/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：端口配置函数

*/

#include "STM32F4_GpioInit.h"
#include "STM32F4_UsartDriver.h"
void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIOOType_TypeDef GPIO_OType,
				GPIOPuPd_TypeDef GPIO_PuPd,	GPIO_TypeDef* GPIO_PORT)	
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode; 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType;
//  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd;
  	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
}
void STM32_GpioInit(void)
{ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
// 	STM32_GpioOneInit(__GPIO_UART1E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART1E_PORT);  
// 	STM32_GpioOneInit(__GPIO_UART2E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART2E_PORT); 
// 	STM32_GpioOneInit(__GPIO_UART3E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART3E_PORT); 
// 	STM32_GpioOneInit(__GPIO_UART4E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART4E_PORT);
// 	STM32_GpioOneInit(__GPIO_UART5E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART5E_PORT); 
// 	STM32_GpioOneInit(__GPIO_UART6E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART6E_PORT); 
// 	STM32_GpioOneInit(__GPIO_IN1_PIN,GPIO_Speed_50MHz,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_IN1_PORT); 
// 	STM32_GpioOneInit(__GPIO_5VCT_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_5VCT_PORT); 
// 	STM32_GpioOneInit(__GPIO_LIGHT_PIN,GPIO_Speed_50MHz,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_LIGHT_PORT);
	
}


void STM32_TimerBaseInit(TIM_TypeDef* TIM, uint32_t TimPeriod, uint16_t TimPrescaler,
						uint16_t TimClockDivision,	uint16_t TimCounterMode,
						uint8_t TimRepetitionCounter)
{
		TIM_TimeBaseInitTypeDef TIM_BaseInitStructure; 
		TIM_DeInit(TIM); 
		TIM_BaseInitStructure.TIM_Period = TimPeriod;   /* Time base configuration */
		TIM_BaseInitStructure.TIM_Prescaler = TimPrescaler;
		TIM_BaseInitStructure.TIM_ClockDivision = TimClockDivision;
		TIM_BaseInitStructure.TIM_CounterMode = TimCounterMode;
		TIM_TimeBaseInit(TIM, &TIM_BaseInitStructure);
}


void STM32_NvicInit(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority,
					uint8_t NVIC_IRQChannelSubPriority, FunctionalState NVIC_IRQChannelCmd)
{
		NVIC_InitTypeDef NVIC_InitStructure;  
		NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = NVIC_IRQChannelCmd;
		NVIC_Init(&NVIC_InitStructure);
}





