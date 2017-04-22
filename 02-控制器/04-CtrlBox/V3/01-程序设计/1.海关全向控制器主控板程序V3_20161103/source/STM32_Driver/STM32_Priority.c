/***********************************************************************************************
*文件名		：	STM32_Priority.c
*描述		：	NVIC分组、设置中断优先级
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
*函数1		：	setSystemPriorityGroup				//	NVIC分组
*函数2		：	setIRQPriority						//	设置中断优先级
***********************************************************************************************/

#include "STM32_Priority.h"

/**
*	@函数说明：  NVIC分组
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
void	setSystemPriorityGroup(void)
{
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);
}

/**
*	@函数说明：  设置中断优先级
*	@参数：		NVIC_IRQChannel：中断号
				NVIC_IRQChannelPreemptionPriority：抢占优先级
				NVIC_IRQChannelSubPriority：响应优先级
*	@返回值： 	无
*	@备注： 		无
*/
void	setIRQPriority(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel 	= NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


