
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __STM32F4_PWMOUT_H
#define __STM32F4_PWMOUT_H

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif
#include <stm32f4xx.h> 
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h" 
#include "STM32F4_GpioInit.h"
  

#define TIMER8_PWM_FREQ      	200   //1MHz/(20000-1+1) = 50Hz  20000us 一个单位为 2us 0.5ms==500us 1.5ms==1500us
#define TIMER8_PWM_PRECALER  	83     //分屏,TIM1CLK = (168MHz)/(167+1) = 1MHz   

 
#define TIMER9_PWM_FREQ      	20000   //1MHz/(20000-1+1) = 50Hz  20000us 一个单位为 2us 0.5ms==500us 1.5ms==1500us,2.5
#define TIMER9_PWM_PRECALER  	167     //分屏,TIM1CLK = (168MHz)/(167+1) = 1MHz   

#define PPMOUT_MINVALUE 			900
#define PPMOUT_MAXVALUE 			2000     //

#define PPMOUT_CHANNEL_NUM		8
#define PPMOUT_CHANNEL_1			0X00
#define PPMOUT_CHANNEL_2			0X01
#define PPMOUT_CHANNEL_3			0X02
#define PPMOUT_CHANNEL_4			0X03
#define PPMOUT_CHANNEL_5			0X04
#define PPMOUT_CHANNEL_6			0X05
#define PPMOUT_CHANNEL_7			0X06
#define PPMOUT_CHANNEL_8			0X07


#define PPMOUT_CTRL_PWM_VAL_MAX	10000

#define Constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))	
#define CheckDeadIn(amt,low,high) ((amt)<(low)?(false):((amt)>(high)?(false):(true)))
/*************************************************************************************************************************
** 														对外数据与函数接口
*************************************************************************************************************************/
 

void STM32_Timer8InitAsPwm(void);
void STM32_SetPwmVal(int16_t PwmVal);
void STM32_Timer9InitAsPwm(void); 
void ServoControl(int16_t servosp);
 
#ifdef __cplusplus
 }
#endif
#endif
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
