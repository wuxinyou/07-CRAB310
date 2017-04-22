

#ifndef __STM32_DAC_H
#define __STM32_DAC_H	

#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_gpio.h"
#include "STM32_GpioInit.h"


#define __GPIO_DAC1_PIN			GPIO_Pin_4	
#define __GPIO_DAC2_PIN			GPIO_Pin_5
#define __GPIO_DAC1_PORT		GPIOA	
#define __GPIO_DAC2_PORT		GPIOA	

#define RCC_ClockCmdGpio_DAC	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE)	
	   
extern void STM32_DacInit(void);
extern void STM32_DacSetValue(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);

	  
#endif 


