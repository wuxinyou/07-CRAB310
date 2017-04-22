/**
******************************************************************************
*文件：Key.h
*版本：2.0
*日期：2013-06-17
*概要：按键类的头文件
*备注：
******************************************************************************  
*/ 
#ifndef _Key_H
	#define _Key_H
	
	#include "stdlib.h"
	#include "stdint.h"
	#include "STM32_GPIO.h"

	#define	KEY_MAX_TIMER	1						//按键状态计数，一般不需要修改
	#define KEY_PRESS_DOWN	0X00					//按键状态，按下为0
	#define KEY_PRESS_UP	0X01					//按键状态，抬起为1
		
	class Key
	{
		public:
			Key(GPIO_TypeDef *port=GPIOA, uint16_t Pin=GPIO_Pin_0, bool bLevel=false);
			~Key();
			uint8_t			FinalState;				//	按键最终状态
			void			getValue(void);			//	获取按键值
			
		private:
			void 			initKey(void);			//	按键初始化
			GPIO_TypeDef 	*KeyPort;				//	端口
			uint16_t		KeyPin;					//	引脚
			bool			KeyLevel;				    //	按键电平
			uint8_t			TrickCount;				//	触发时间
	};

#endif



