/***********************************************************************************************
*文件名		：	STM32_GPIO.c
*描述		：	GPIO初始化
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
*函数1		：	STM32_GpioOneInit				//	单个引脚GPIO初始化
***********************************************************************************************/

#include "STM32_GPIO.h"

/**
*	@函数说明：	GPIO初始化
*	@参数：		GPIO_Pin，GPIO引脚 = (	GPIO_Pin_0~GPIO_Pin_15)
				GPIO_Speed，GPIO速度 = (	GPIO_Speed_10MHz, GPIO_Speed_2MHz, GPIO_Speed_50MHz)
				GPIOMode_TypeDef，GPIO模式=	(	GPIO_Mode_AIN , GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD, 
												GPIO_Mode_IPU, GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, 
												GPIO_Mode_AF_OD, GPIO_Mode_AF_PP)
				GPIO_TypeDef，GPIO端口 = (GPIOA~GPIOG)
*	@返回值： 	无
*	@备注： 		无
*/
void STM32_GpioOneInit(uint16_t GPIO_Pin,	GPIOSpeed_TypeDef GPIO_Speed,	\
				GPIOMode_TypeDef GPIO_Mode,	GPIO_TypeDef* GPIO_PORT)	
{	
    GPIO_InitTypeDef GPIO_InitStructure;
    
	if (GPIO_PORT==GPIOA)
	{
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
    else if (GPIO_PORT==GPIOB)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
    else if (GPIO_PORT==GPIOC)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if (GPIO_PORT==GPIOD)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
    else if (GPIO_PORT==GPIOE)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    }
    else if (GPIO_PORT==GPIOF)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    }
    else if (GPIO_PORT==GPIOG)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
    }
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin ;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
}





