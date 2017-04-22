/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：使用前需要先配置TX与RX端口，以及复用情况

*/

#ifndef __STM32F4_USART_H
#define __STM32F4_USART_H

#include "stm32f4xx.h"
#include "STM32F4_UsartDriver.h"
#include "STM32F4_PriorityControl.h"
// #include "MySysDefine.h"
#include "STM32F4_GpioInit.h"
#include "stm32f4xx_usart.h"


#define USE_DRIVER_USART1
#define USE_DRIVER_USART2
#define USE_DRIVER_USART3
#define USE_DRIVER_USART4
#define USE_DRIVER_USART5

/****************** USART1 端口初始化****************************/
#define GPIO_PinRemapConfig_USART1	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,	GPIO_AF_USART1);\
																		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, 	GPIO_AF_USART1)
																		
#define RCC_ClockCmdGpio_USART1			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)

#define STM32_GpioInit_USART1				STM32_GpioOneInit(GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP,	GPIO_PuPd_UP,	GPIOA);\
																		STM32_GpioOneInit(GPIO_Pin_10,  GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP,	GPIO_PuPd_UP,	GPIOA)

/****************** USART2 端口初始化****************************/
#define GPIO_PinRemapConfig_USART2	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,	GPIO_AF_USART2);\
																		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, 	GPIO_AF_USART2)	
																		
#define RCC_ClockCmdGpio_USART2			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)	
#define STM32_GpioInit_USART2				STM32_GpioOneInit(GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOD);\
																		STM32_GpioOneInit(GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOD)	

/****************** USART3 端口初始化****************************/
#define GPIO_PinRemapConfig_USART3	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,	GPIO_AF_USART3);\
																		GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, 	GPIO_AF_USART3)	
																		
#define RCC_ClockCmdGpio_USART3			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)	;	

#define STM32_GpioInit_USART3				STM32_GpioOneInit(GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOD);\
																		STM32_GpioOneInit(GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOD)										;

/****************** USART4 端口初始化****************************/
#define GPIO_PinRemapConfig_USART4	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10,	GPIO_AF_UART4);\
																		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, 	GPIO_AF_UART4)
																		
#define RCC_ClockCmdGpio_USART4			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)

#define STM32_GpioInit_USART4				STM32_GpioOneInit(GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_NOPULL,	GPIOC);\
																		STM32_GpioOneInit(GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_NOPULL,	GPIOC)	

/****************** USART5 端口初始化****************************/
#define GPIO_PinRemapConfig_USART5	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12,	GPIO_AF_UART5);\
																		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, 	GPIO_AF_UART5)
																		
#define RCC_ClockCmdGpio_USART5			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);\
																		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
																		
#define STM32_GpioInit_USART5				STM32_GpioOneInit(GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOC);\
																		STM32_GpioOneInit(GPIO_Pin_2, GPIO_Speed_50MHz,GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOD)	

/****************** USART6 端口初始化****************************/
#define GPIO_PinRemapConfig_USART6	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,	GPIO_AF_USART6);\
																		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, 	GPIO_AF_USART6)
																		
#define RCC_ClockCmdGpio_USART6			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)


#define STM32_GpioInit_USART6				STM32_GpioOneInit(GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOC);\
																		STM32_GpioOneInit(GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF,	GPIO_OType_PP, 	GPIO_PuPd_UP,	GPIOC)

extern void STM32_InitUsart1(u32 Baudrate);
extern void STM32_InitUsart2(u32 Baudrate);
extern void STM32_InitUsart3(u32 Baudrate);
extern void STM32_InitUsart4(u32 Baudrate);
extern void STM32_InitUsart5(u32 Baudrate);
extern void STM32_InitUsart6(u32 Baudrate);


extern USART_data_t USART_data_1;
extern USART_data_t USART_data_2;
extern USART_data_t USART_data_3;
extern USART_data_t USART_data_4;
extern USART_data_t USART_data_5;
extern USART_data_t USART_data_6;



#endif

