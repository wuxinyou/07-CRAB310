/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：端口配置函数

*/

#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H	


#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx.h"
#define __GPIO_D_LIGHT_PIN	GPIO_Pin_13							//
#define __GPIO_D_LIGHT_PORT	GPIOD										//
#define __GPIO_W_LIGHT_PIN	GPIO_Pin_14							//
#define __GPIO_W_LIGHT_PORT	GPIOD										//  
#define __GPIO_RELAY_PIN		GPIO_Pin_3							//
#define __GPIO_RELAY_PORT		GPIOD										//  
#define __GPIO_POLED_PIN		GPIO_Pin_11							//
#define __GPIO_POLED_PORT		GPIOD										// 
#define __GPIO_ACH1_PIN			GPIO_Pin_0							//
#define __GPIO_ACH1_PORT		GPIOC										// 
#define __GPIO_ACH2_PIN			GPIO_Pin_1							//
#define __GPIO_ACH2_PORT		GPIOC										// 
#define __GPIO_ACH3_PIN			GPIO_Pin_2							//
#define __GPIO_ACH3_PORT		GPIOC										// 
	 
#define D_LIGHT_ON		GPIO_SetBits(__GPIO_D_LIGHT_PORT, __GPIO_D_LIGHT_PIN)	
#define D_LIGHT_OFF		GPIO_ResetBits(__GPIO_D_LIGHT_PORT, __GPIO_D_LIGHT_PIN) 
#define W_LIGHT_ON		GPIO_SetBits(__GPIO_W_LIGHT_PORT, __GPIO_W_LIGHT_PIN)	
#define W_LIGHT_OFF		GPIO_ResetBits(__GPIO_W_LIGHT_PORT, __GPIO_W_LIGHT_PIN) 
#define RELAY_ON			GPIO_SetBits(__GPIO_RELAY_PORT, __GPIO_RELAY_PIN)	
#define RELAY_OFF			GPIO_ResetBits(__GPIO_RELAY_PORT, __GPIO_RELAY_PIN) 
#define POLED_ON			GPIO_SetBits(__GPIO_POLED_PORT, __GPIO_POLED_PIN)	
#define POLED_OFF			GPIO_ResetBits(__GPIO_POLED_PORT, __GPIO_POLED_PIN) 
#define ACH1_ON				GPIO_SetBits(__GPIO_ACH1_PORT, __GPIO_ACH1_PIN)	
#define ACH1_OFF			GPIO_ResetBits(__GPIO_ACH1_PORT, __GPIO_ACH1_PIN) 
#define ACH2_ON				GPIO_SetBits(__GPIO_ACH2_PORT, __GPIO_ACH2_PIN)	
#define ACH2_OFF			GPIO_ResetBits(__GPIO_ACH2_PORT, __GPIO_ACH2_PIN) 
#define ACH3_ON				GPIO_SetBits(__GPIO_ACH3_PORT, __GPIO_ACH3_PIN)	
#define ACH3_OFF			GPIO_ResetBits(__GPIO_ACH3_PORT, __GPIO_ACH3_PIN) 
/******************************************************************************************/
void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	
				GPIOMode_TypeDef GPIO_Mode,	GPIOOType_TypeDef GPIO_OType,
				GPIOPuPd_TypeDef GPIO_PuPd,	GPIO_TypeDef* GPIO_PORT);

void STM32_GpioInit(void);
void STM32_TimerBaseInit(TIM_TypeDef* TIM, uint32_t TimPeriod, uint16_t TimPrescaler,
						uint16_t TimClockDivision,	uint16_t TimCounterMode,
						uint8_t TimRepetitionCounter);
void STM32_NvicInit(uint8_t NVIC_IRQChannel, uint8_t NVIC_IRQChannelPreemptionPriority,
					uint8_t NVIC_IRQChannelSubPriority, FunctionalState NVIC_IRQChannelCmd);
#ifdef __cplusplus
 }
#endif
#endif 




