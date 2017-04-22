#ifndef __STM32F4_IRQ_INIT_H
#define __STM32F4_IRQ_INIT_H
#include "CrabApp.h"
#include "WatchDag.h"

extern CrabApp *myApp;
// extern WatchDag *myDag;

#ifdef __cplusplus  
       extern "C" {  
#endif  
#include <stm32f4xx.h>
// #include "SerialPort.h"
				 
// #define STM32_NVIC_PriorityGroup		NVIC_PriorityGroup_2

// #define NVIC_PRIORITY_NULL			0X00
// #define NVIC_PRIORITY_HIGHEST		0X00
// #define NVIC_PRIORITY_HIGHER		0X01
// #define NVIC_PRIORITY_MIDDLE		0X02
// #define NVIC_PRIORITY_LOW			0X03
// #define NVIC_PRIORITY_LOWER			0X04	
// #define NVIC_PRIORITY_LOWEST		0X05	



// #define STM32_NVIC_USART1_PrePriority 	NVIC_PRIORITY_HIGHEST
// #define STM32_NVIC_USART2_PrePriority 	NVIC_PRIORITY_HIGHEST
// #define STM32_NVIC_USART3_PrePriority 	NVIC_PRIORITY_HIGHEST
// #define STM32_NVIC_USART4_PrePriority 	NVIC_PRIORITY_HIGHEST
// #define STM32_NVIC_USART5_PrePriority 	NVIC_PRIORITY_HIGHEST
// #define STM32_NVIC_USART6_PrePriority 	NVIC_PRIORITY_HIGHEST


// #define STM32_NVIC_TIM2_PrePriority		NVIC_PRIORITY_HIGHER
// #define STM32_NVIC_TIM3_PrePriority		NVIC_PRIORITY_LOW
// #define STM32_NVIC_TIM4_PrePriority		NVIC_PRIORITY_MIDDLE

// // #define STM32_NVIC_TIM2_PrePriority		NVIC_PRIORITY_HIGHEST
// // #define STM32_NVIC_TIM3_PrePriority		NVIC_PRIORITY_HIGHEST
// // #define STM32_NVIC_TIM4_PrePriority		NVIC_PRIORITY_HIGHEST


// #define STM32_NVIC_USART1_SubPriority 	NVIC_PRIORITY_HIGHEST 	
// #define STM32_NVIC_USART2_SubPriority 	NVIC_PRIORITY_HIGHEST 	
// #define STM32_NVIC_USART3_SubPriority 	NVIC_PRIORITY_HIGHEST 	
// #define STM32_NVIC_USART4_SubPriority 	NVIC_PRIORITY_HIGHEST 	
// #define STM32_NVIC_USART5_SubPriority 	NVIC_PRIORITY_HIGHEST 
// #define STM32_NVIC_USART6_SubPriority 	NVIC_PRIORITY_HIGHEST 

// #define STM32_NVIC_TIM2_SubPriority		NVIC_PRIORITY_HIGHER
// #define STM32_NVIC_TIM3_SubPriority		NVIC_PRIORITY_LOW
// #define STM32_NVIC_TIM4_SubPriority		NVIC_PRIORITY_MIDDLE
// // #define STM32_NVIC_TIM2_SubPriority		NVIC_PRIORITY_HIGHEST
// // #define STM32_NVIC_TIM3_SubPriority		NVIC_PRIORITY_HIGHEST
// // #define STM32_NVIC_TIM4_SubPriority		NVIC_PRIORITY_HIGHEST


// // extern void STM32_Usart1_InitNVIC(void);
// // extern void STM32_Usart2_InitNVIC(void);
// // extern void STM32_Usart3_InitNVIC(void);
// // extern void STM32_Usart4_InitNVIC(void);
// // extern void STM32_Usart5_InitNVIC(void);


#ifdef __cplusplus  
        }
// void initSerialPort();
#endif
#endif




