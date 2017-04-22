/***********************************************************************************************
*文件名		：	STM32_ADC.h
*描述		：	ADC1初始化(DMA传输)
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
***********************************************************************************************/

#ifndef __STM32_ADC_H
	#define __STM32_ADC_H	
	
	#ifdef __cplusplus
	 extern "C" {
	#endif
	
			 
	#include "stm32f10x_adc.h"
	#include "stm32f10x_dma.h"
	#include "STM32_GPIO.h"
	
	#define ADC_CHANNEL_N	9	   					//	通道数，使用多个通道时需要修改此定义
	#define ADC_CACHEL_M	10 						//	每个通道缓存数，用于均值滤波
	
	extern	uint16_t AD_Filter[];	//	ADC1-DMA初始化后，此数组可直接用
	void	ADC1_DMA_Init(void);	//	ADC1-DMA初始化，初始化之后即开始转换

	#ifdef __cplusplus
	 }
	#endif

#endif 
