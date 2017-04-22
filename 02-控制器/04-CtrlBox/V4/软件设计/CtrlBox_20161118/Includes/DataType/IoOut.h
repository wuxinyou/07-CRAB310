/**
******************************************************************************
*文件：Key.cpp
*作者：孟浩
*版本：1.0
*日期：2015-03-09
*概要：Key类的头文件
*备注：
******************************************************************************  
*/ 
#ifndef _IO_OUT_H
	#define _IO_OUT_H

	#include  "STM32_GPIO.h"

	class IoOut
	{
		public:
			IoOut(GPIO_TypeDef *port=GPIOA, uint16_t pin=GPIO_Pin_0, bool bLevel=false);
			~IoOut();

			void 			setOn();		
			void 			setOff();	
			void 			reverseState();	//翻转Io的状态
			
		private:
			void 			initIo();
			GPIO_TypeDef 	*ioOutPort; 
			uint16_t 		ioOutPin;	
			uint8_t 		ioOutLevel;						
	};

#endif



