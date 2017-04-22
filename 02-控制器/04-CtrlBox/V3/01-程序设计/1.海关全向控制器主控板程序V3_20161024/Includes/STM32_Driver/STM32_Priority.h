/***********************************************************************************************
*文件名		：	STM32_Priority.h
*描述		：	NVIC函数声明，中断优先级宏定义
*作者		：	叶依顺
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
***********************************************************************************************/

#ifndef _STM32_PRIORITY_H
	#define _STM32_PRIORITY_H
	
	#include <stm32f10x.h>
	#ifdef __cplusplus
		extern "C" {
	#endif

	#include <stdint.h>	

	//中断分组2 4个响应级别 4个抢占级别
	#define STM32_NVIC_PriorityGroup		NVIC_PriorityGroup_2

	#define NVIC_PRIORITY_NULL				0X00 
	#define NVIC_PRIORITY_HIGHEST			0X00
	#define NVIC_PRIORITY_HIGHER			0X01
	#define NVIC_PRIORITY_MIDDLE			0X02
	#define NVIC_PRIORITY_LOW				  0X03 
	#define NVIC_PRIORITY_LOWER				0X04	
	#define NVIC_PRIORITY_LOWEST			0X05	

	#define STM32_NVIC_USART1_PrePriority 	NVIC_PRIORITY_HIGHEST
	#define STM32_NVIC_USART2_PrePriority 	NVIC_PRIORITY_HIGHEST
	#define STM32_NVIC_USART3_PrePriority 	NVIC_PRIORITY_HIGHEST
	#define STM32_NVIC_USART4_PrePriority 	NVIC_PRIORITY_HIGHEST
	#define STM32_NVIC_USART5_PrePriority 	NVIC_PRIORITY_HIGHEST
	#define STM32_NVIC_USART6_PrePriority 	NVIC_PRIORITY_HIGHEST

	#define STM32_NVIC_TIM2_PrePriority			NVIC_PRIORITY_HIGHER
	#define STM32_NVIC_TIM3_PrePriority			NVIC_PRIORITY_LOW
	#define STM32_NVIC_TIM4_PrePriority			NVIC_PRIORITY_MIDDLE

	#define STM32_NVIC_USART1_SubPriority 	NVIC_PRIORITY_HIGHEST 	
	#define STM32_NVIC_USART2_SubPriority 	NVIC_PRIORITY_HIGHEST 	
	#define STM32_NVIC_USART3_SubPriority 	NVIC_PRIORITY_HIGHEST 	
	#define STM32_NVIC_USART4_SubPriority 	NVIC_PRIORITY_HIGHEST 	
	#define STM32_NVIC_USART5_SubPriority 	NVIC_PRIORITY_HIGHEST 
	#define STM32_NVIC_USART6_SubPriority 	NVIC_PRIORITY_HIGHEST 

	#define STM32_NVIC_TIM2_SubPriority			NVIC_PRIORITY_HIGHER
	#define STM32_NVIC_TIM3_SubPriority			NVIC_PRIORITY_LOW
	#define STM32_NVIC_TIM4_SubPriority			NVIC_PRIORITY_MIDDLE

	void	setSystemPriorityGroup(void);
	void	setIRQPriority(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority);
	
	#ifdef __cplusplus
		}
	#endif
#endif

