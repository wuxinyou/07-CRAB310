/***********************************************************************************************
*文件名		：	STM32_SysTick.h
*描述		：	SysTick初始化，us、ms延时函数声明
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
***********************************************************************************************/

#ifndef __STM32_SYSTICK_H
	#define __STM32_SYSTICK_H
	#ifdef __cplusplus
		extern "C" {
	#endif
			
	#include "stm32f10x.h"

	void SysTick_Init(void); 				//	SysTick初始化
	void SysTick_DelayUs(uint32_t nus);		//	us延时
	void SysTick_DelayMs(uint32_t nms);		//	ms延时

	#ifdef __cplusplus
		}
	#endif
#endif

