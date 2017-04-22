/* 	版本信息：	V1.01
	创建时间：	2012－08－01
	最后修改：	2012－09－10

	备注：使用前需要先配置RS485端口的使能情况与引脚情况

*/
/* Includes ------------------------------------------------------------------*/

#include "STM32F4_UsartInit.h"


/*! USART data struct used in example. */
USART_data_t USART_data_1;
USART_data_t USART_data_2;
USART_data_t USART_data_3;
USART_data_t USART_data_4;
USART_data_t USART_data_5;
USART_data_t USART_data_6;


void STM32_Usart_InitNVIC(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,
					uint8_t NVIC_IRQChannelSubPriority)
{	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the USART Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel 	= NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/* USART1 configured as follow:*/
//115200,8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
void STM32_Usart_InitConfig(USART_TypeDef *USART_x, u32 Baudrate,uint16_t USART_Mode)
{
	USART_InitTypeDef USART_InitStructure;

	//将结构体设置为缺省状态
  USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode;

	/* Configure USART1 */
	USART_Init(USART_x, &USART_InitStructure);
}

/*****************************************************************************/

/*****************************STM32 USART1 初始化****************************/
void STM32_InitUsart1(u32 Baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InterruptDriver_Initialize(&USART_data_1,USART1);

	USART_Cmd(USART1, DISABLE);

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_ClockCmdGpio_USART1;	 
	GPIO_PinRemapConfig_USART1;
	STM32_GpioInit_USART1;

#ifdef USART1_RS485
	RCC_ClockCmdGpio_USART1_RS485;
// 	STM32_GpioOneInit(__GPIO_UART1E_PIN, GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_UART1E_PORT);
#endif

//	/* USART configured as follow:*/
//	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
//	STM32_Usart_InitConfig(USART1, Baudrate, USART_Mode_Tx|USART_Mode_Rx);
		

	//将结构体设置为缺省状态
   	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

	/* Configure USART1 */
	USART_Init(USART1, &USART_InitStructure);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART1_IRQn,STM32_NVIC_USART1_PrePriority,
				STM32_NVIC_USART1_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
// 	USART_Cmd(USART1, ENABLE);
}

/*****************************************************************************/

/*****************************STM32 USART2 初始化****************************/
void STM32_InitUsart2(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_2,USART2);

	USART_Cmd(USART2, DISABLE);

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_ClockCmdGpio_USART2;	 
	GPIO_PinRemapConfig_USART2;
	STM32_GpioInit_USART2;
	
#ifdef USART2_RS485
	RCC_ClockCmdGpio_USART2_RS485;
// 	STM32_GpioOneInit(__GPIO_UART2E_PIN, GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_UART2E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(USART2, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART2_IRQn,STM32_NVIC_USART2_PrePriority,
				STM32_NVIC_USART2_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
// 	USART_Cmd(USART2, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART3 初始化****************************/
void STM32_InitUsart3(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_3,USART3);

	USART_Cmd(USART3, DISABLE);

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_ClockCmdGpio_USART3;	 
	GPIO_PinRemapConfig_USART3;
	STM32_GpioInit_USART3;  

#ifdef USART3_RS485
	RCC_ClockCmdGpio_USART3_RS485;
	
 	STM32_GpioOneInit(__GPIO_UART3E_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART3E_PORT); 
#endif
 

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(USART3, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART3_IRQn,STM32_NVIC_USART3_PrePriority,
				STM32_NVIC_USART3_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
// 	USART_Cmd(USART3, ENABLE);
}

/*****************************************************************************/

/*****************************STM32 USART4 初始化****************************/

void STM32_InitUsart4(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_4,UART4);//ok

	USART_Cmd(UART4, DISABLE);//ok

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); //ok
	RCC_ClockCmdGpio_USART4;	 														//ok
	GPIO_PinRemapConfig_USART4;														//ok
	STM32_GpioInit_USART4;																//ok

#ifdef USART4_RS485
	RCC_ClockCmdGpio_USART4_RS485;
// 	STM32_GpioOneInit(__GPIO_UART4E_PIN, GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_NOPULL,__GPIO_UART4E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(UART4, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(UART4_IRQn,STM32_NVIC_USART4_PrePriority,
				STM32_NVIC_USART4_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_ITConfig(UART4, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
// 	USART_Cmd(UART4, ENABLE);

}

/*****************************************************************************/

/*****************************STM32 USART5 初始化****************************/
void STM32_InitUsart5(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_5,UART5);

	USART_Cmd(UART5, DISABLE);

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	RCC_ClockCmdGpio_USART5;	 
	GPIO_PinRemapConfig_USART5;
	STM32_GpioInit_USART5;       
	
#ifdef USART5_RS485
	RCC_ClockCmdGpio_USART5_RS485;
// 	STM32_GpioOneInit(__GPIO_UART5E_PIN, GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_UART5E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(UART5, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(UART5_IRQn,STM32_NVIC_USART5_PrePriority,
				STM32_NVIC_USART5_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	USART_ITConfig(UART5, USART_IT_TC, ENABLE);

	/* Enable the USARTy */
// 	USART_Cmd(UART5, ENABLE);
}

/*****************************************************************************/

/*****************************STM32 USART6 初始化****************************/
void STM32_InitUsart6(u32 Baudrate)
{
	USART_InterruptDriver_Initialize(&USART_data_6,USART6);

	USART_Cmd(USART6, DISABLE);

	/* System Clocks Configuration * Configure the GPIO ports * the USART Pins Software Remapping */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE); //开启USART6时钟
	RCC_ClockCmdGpio_USART6;	 														 //开启GPIOC时钟
	GPIO_PinRemapConfig_USART6;
	STM32_GpioInit_USART6;       
	
#ifdef USART6_RS485
	RCC_ClockCmdGpio_USART6_RS485;
// 	STM32_GpioOneInit(__GPIO_UART6E_PIN, GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_UART6E_PORT);
#endif

	/* USART configured as follow:*/
	//8 Bits,One Stop Bit,No parity,transmit enabled,Receive enabled
	STM32_Usart_InitConfig(USART6, Baudrate, USART_Mode_Tx|USART_Mode_Rx);

	/* USART InitNVIC as follow:*/
	STM32_Usart_InitNVIC(USART6_IRQn,STM32_NVIC_USART6_PrePriority,
				STM32_NVIC_USART6_SubPriority);

	/* Enable USARTy Receive and Transmit interrupts */
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART6, USART_IT_TC, ENABLE);
	/* Enable the USARTy */
// 	USART_Cmd(USART6, ENABLE);

}









