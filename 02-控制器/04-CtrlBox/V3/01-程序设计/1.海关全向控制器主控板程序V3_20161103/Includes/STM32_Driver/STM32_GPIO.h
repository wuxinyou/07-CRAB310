/***********************************************************************************************
*文件名		：	STM32_GPIO.h
*描述		  ：	GPIO初始化函数声明
*作者		  ：	叶依顺
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
***********************************************************************************************/

#ifndef __STM32_GPIO_H
	#define __STM32_GPIO_H	
	
	#ifdef __cplusplus
		extern "C" {
	#endif
		 
	#include "stm32f10x.h"
			
	void STM32_GpioOneInit(uint16_t, GPIOSpeed_TypeDef, GPIOMode_TypeDef, GPIO_TypeDef*);
		 
	#ifdef __cplusplus
		}
	#endif
#endif





