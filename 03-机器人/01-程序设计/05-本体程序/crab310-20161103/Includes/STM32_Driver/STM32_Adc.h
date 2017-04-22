#ifndef __STM32_ADC_H
#define __STM32_ADC_H	

#include <stm32f4xx.h>  
#include <stdio.h>

 
#define ADC1_DR_Address  ((uint32_t)0X4001204C)
		 
#define STM32_ADC_CHANNEL_N	6		   
#define STM32_ADC_CACHEL_M	30
//各ADC采样通道的位置
#define ADC_SW			0
#define ADC_ANGLE 	1
#define ADC_BAT1		2
#define ADC_BAT2		3 
//电源电压采集电阻分压
#ifndef V_REG
#define V_REG					3.3
#endif
#ifndef VIN_R1
#define VIN_R1				20000.0
#endif
#ifndef VIN_R2
#define VIN_R2				1000.0
#endif


void Adc1DmaInit(void);
void StartAdcConvert(void);
float getbatvolt(uint8_t channel);
#endif


