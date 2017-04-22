/**
  ******************************************************************************
	*文件：SerialPort.cpp
	*作者：叶依顺
	*版本：2.0
	*日期：2014-01-02
	*概要：串口类的实现
	*
  ******************************************************************************  
	*/
#include "SerialPort.h"	

#define PORT_1 1
#define PORT_2 2
#define PORT_3 3
#define PORT_4 4
#define PORT_5 5

//根据不同的CPU型号做断言
#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2) || \
                                     ((PORT) == 3) || \
                                     ((PORT) == 4) || \
                                     ((PORT) == 5))
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2) || \
                                     ((PORT) == 3))
#endif

#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2))
#endif

//关于串口引脚和时钟等的配置宏

// #define USARTREMAP_1 //定义开启串口1重映射

#ifndef USARTREMAP_1 //串口1没有重映射

	#define USARTPORT_1 			GPIOA									//串口1所在端口
	#define USARTPIN_IN_1 		GPIO_Pin_10						//串口1输入引脚
	#define USARTPIN_OUT_1 	  GPIO_Pin_9						//串口1输出引脚
	#define USARTRCCPERIPH_1 	RCC_APB2Periph_GPIOA	//串口1所在引脚的时钟总线

#else 							//串口1开启重映射

	#define USARTPORT_1 			GPIOB									//串口1所在端口
	#define USARTPIN_IN_1 		GPIO_Pin_7						//串口1输入引脚
	#define USARTPIN_OUT_1 		GPIO_Pin_6						//串口1输出引脚
	#define USARTRCCPERIPH_1	RCC_APB2Periph_GPIOB	//串口1所在引脚的时钟总线
	
#endif

// #define USARTREMAP_2 //定义开启串口2重映射

#ifndef USARTREMAP_2 //串口2没有重映射 USART2_REMAP = 0

	#define USARTPORT_2 			GPIOA									//串口2所在端口
	#define USARTPIN_IN_2 		GPIO_Pin_3						//串口2输入引脚
	#define USARTPIN_OUT_2	  GPIO_Pin_2						//串口2输出引脚
	#define USARTRCCPERIPH_2 	RCC_APB2Periph_GPIOA	//串口2所在引脚的时钟总线

#else 							//串口2开启重映射 USART2_REMAP = 1

	#define USARTPORT_2 			GPIOD									//串口2所在端口
	#define USARTPIN_IN_2 		GPIO_Pin_6						//串口2输入引脚
	#define USARTPIN_OUT_2 		GPIO_Pin_5						//串口2输出引脚
	#define USARTRCCPERIPH_2	RCC_APB2Periph_GPIOD	//串口2所在引脚的时钟总线
	
#endif

//在100和144引脚分装的STM32F10X系列单片机上串口3有两种重映射

#define USARTREMAP_3_OFF 					//没有开启串口3重映射
// #define USARTREMAP_3_TO_PORTC	//串口重映射到PORTC上
// #define USARTREMAP_3_TO_PORTD	//串口重映射到PORTD上

#if !defined(USARTREMAP_3_OFF)&&!defined(USARTREMAP_3_TO_PORTC)&&!defined(USARTREMAP_3_TO_PORTD)
#error 串口3没有指定映射类型
#endif


#ifdef USARTREMAP_3_OFF //串口3没有重映射 

	#define USARTPORT_3 			GPIOB									//串口3所在端口
	#define USARTPIN_IN_3 		GPIO_Pin_11						//串口3输入引脚
	#define USARTPIN_OUT_3	  GPIO_Pin_10						//串口3输出引脚
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOB	//串口3所在引脚的时钟总线
#endif
							//串口3开启重映射
#ifdef USARTREMAP_3_TO_PORTC	//串口重映射到PORTC上
	#define USARTPORT_3 			GPIOC									//串口3所在端口
	#define USARTPIN_IN_3 		GPIO_Pin_11						//串口3输入引脚
	#define USARTPIN_OUT_3	  GPIO_Pin_10						//串口3输出引脚
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOC	//串口3所在引脚的时钟总线
#endif

#ifdef USARTREMAP_3_TO_PORTD	//串口重映射到PORTD上	
	#define USARTPORT_3 			GPIOD									//串口3所在端口
	#define USARTPIN_IN_3 		GPIO_Pin_9						//串口3输入引脚
	#define USARTPIN_OUT_3	  GPIO_Pin_8						//串口3输出引脚
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOD	//串口3所在引脚的时钟总线
#endif

//串口4和5没有重映射
	#define USARTPORT_4 			GPIOC									//串口4所在端口
	#define USARTPIN_IN_4 		GPIO_Pin_11						//串口4输入引脚
	#define USARTPIN_OUT_4	  GPIO_Pin_10						//串口4输出引脚
	#define USARTRCCPERIPH_4 	RCC_APB2Periph_GPIOC	//串口4所在引脚的时钟总线

	#define USARTPORT_5_IN 				GPIOD									//串口5输入引脚所在端口
	#define USARTPORT_5_OUT 			GPIOC									//串口5输出引脚所在端口
	#define USARTPIN_IN_5 				GPIO_Pin_2						//串口5输入引脚
	#define USARTPIN_OUT_5	  		GPIO_Pin_12						//串口5输出引脚
	#define USARTRCCPERIPH_5_IN 	RCC_APB2Periph_GPIOD	//串口5所在输入引脚的时钟总线
	#define USARTRCCPERIPH_5_OUT 	RCC_APB2Periph_GPIOC	//串口5所在输出引脚的时钟总线

#define USART_CR1_TXEIE_gm 	(uint16_t)(1<<7)

USART_data_t USART_data_1;
USART_data_t USART_data_2;
USART_data_t USART_data_3;
USART_data_t USART_data_4;
USART_data_t USART_data_5;
USART_data_t USART_data_6;

/**
  * 功  能：USART_data_t构造函数
  * 参  数：串口的寄存器
  * 返回值：无
  */
USART_data_t::USART_data_t()
{
	useRS485Flag=false;
	ctrTxPort=NULL;
	ctrTxPin=0;
	usart=NULL;
	buffer.RX_Tail = 0;
	buffer.RX_Head = 0;
	buffer.TX_Tail = 0;
	buffer.TX_Head = 0;
}

/**
  * 功  能：判断串口发送缓冲区是否有空间
  * 参  数：无
  * 返回值：
	* true: 缓冲区有空间，可以写
	* false: 缓冲区没有空间，不可以写
  */
bool USART_data_t::txBuffer_GetFreeStatus()
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = (buffer.TX_Head + 1) & TX_BUFFER_MASK;
	uint8_t tempTail = buffer.TX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**
  * 功  能：判断串口缓冲区数据是否发送完毕
  * 参  数：无
  * 返回值：
	* true: 没有发送完
	* false: 发送完毕
  */
bool USART_data_t::txBuffer_SendAll()
{
	uint8_t tempHead =  buffer.TX_Head;
	uint8_t tempTail =  buffer.TX_Tail;
	return (tempHead != tempTail);
}

/**
  * 功  能：向串口缓冲区写一个字节
  * 参  数：
	* data  :待写入的数据
  * 返回值：
	* true: 成功写入
	* false: 写入失败
  */
uint8_t USART_data_t::txBuffer_PutByte(uint8_t data)
{
// 	uint16_t tempCR1;
	uint8_t tempTX_Head;
	bool TXBuffer_FreeSpace;
	USART_Buffer_t * TXbufPtr;
	TXbufPtr = &buffer;
	TXBuffer_FreeSpace = txBuffer_GetFreeStatus();
	if(TXBuffer_FreeSpace)//串口缓冲区未满
	{
	  	tempTX_Head = TXbufPtr->TX_Head;
	  	TXbufPtr->TX[tempTX_Head]= data;
		/* Advance buffer head. */
		TXbufPtr->TX_Head = (tempTX_Head + 1) & TX_BUFFER_MASK;
		/* Enable DRE interrupt.开中断 */
		USART_ITConfig(usart, USART_IT_TXE, ENABLE); //	使能发送中断
	}
	return TXBuffer_FreeSpace;
}

/**
  * 功  能：判断接收缓冲区是否有数据
  * 参  数：无
  * 返回值：
	* true: 	有数据
	* false: 	无数据
  */
bool USART_data_t::rxBuffer_GetAvailableStatus()
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = buffer.RX_Head;
	uint8_t tempTail = buffer.RX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**
  * 功  能：从串口接收缓冲区读取一个字节
  * 参  数：无
  * 返回值：读取的字节
  */
uint8_t USART_data_t::rxBuffer_GetByte()
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;

	bufPtr = &buffer;
	ans = (bufPtr->RX[bufPtr->RX_Tail]);

	/* Advance buffer tail. */
	bufPtr->RX_Tail = (bufPtr->RX_Tail + 1) & RX_BUFFER_MASK;
	return ans;
}

/**
  * 功  能：从串口DR寄存器中接收一个数据写入接收缓冲区
  * 参  数：无
  * 返回值：
	* true:  接收缓冲区未满
	* false: 接收缓冲区满
  */
bool USART_data_t::rxComplete()
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;
	uint8_t tempRX_Head;
	uint8_t tempRX_Tail;
	uint8_t data;

	bufPtr = &buffer;
	/* Advance buffer head. */
	tempRX_Head = (bufPtr->RX_Head + 1) & RX_BUFFER_MASK;

	/* Check for overflow. */
	tempRX_Tail = bufPtr->RX_Tail;
	data = usart->DR;

	if (tempRX_Head == tempRX_Tail) {
	  	ans = 0;
	}else{
		ans = 1;
		buffer.RX[buffer.RX_Head] = data;
		buffer.RX_Head = tempRX_Head;
	}
	return ans;
}

/**
  * 功  能：向串口数据寄存器中写入一个数据
  * 参  数：无
  * 返回值：无
  */
void USART_data_t::dataRegEmpty()
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
		enableTX();
		data = bufPtr->TX[buffer.TX_Tail];
		usart->DR = data;
		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & TX_BUFFER_MASK;
	}
}

/**
  * 功  能：允许485发送
  * 参  数：无
  * 返回值：无
  */
void USART_data_t::enableTX(void)
{
	if(!useRS485Flag)
		return;
	else//使能发送
		GPIO_SetBits(ctrTxPort, ctrTxPin);
}

/**
  * 功  能：禁止485发送
  * 参  数：无
  * 返回值：无
  */
void USART_data_t::disabledTX(void)
{
	if(!useRS485Flag)
		return;
	else//失能发送
		GPIO_ResetBits(ctrTxPort, ctrTxPin);
}

/**
  * 功  能：SerialPort类的构造函数
  * 参  数：
	* s_port：串口号
	* s_baudrate：波特率
  * 返回值：无
  */
SerialPort::SerialPort(int s_port,int s_baudrate)
{
	assert_param(ISSERIALPORT(s_port));						//断言串口是否合法 1 2 3 4 5
	assert_param(IS_USART_BAUDRATE(s_baudrate));	//断言波特率是否合法
	port=s_port; 
	baudrate=s_baudrate;
	initUsart();//串口初始化
}

/**
  * 功  能：SerialPort类的析构函数
  * 参  数：
  * 返回值：无
  */
SerialPort::~SerialPort()
{
	close();	//stop 停止发送
	COM=NULL;
}

/**
  * 功  能：串口配置函数
  * 参  数：
	* USART_x：串口配置寄存器
	* Baudrate：波特率
	*	USART_Mode：串口模式 如发送接收等
  * 返回值：无
  */
void SerialPort::usartConfig(USART_TypeDef *USART_x, uint32_t Baudrate,uint16_t USART_Mode)
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

/**
  * 功  能：串口GPIO配置
  * 参  数：
	* usartPort：串口号
  * 返回值：无
  */
void SerialPort::usartGpioInit()
{
	int temPort=port;
	close();//失能串口
	switch(temPort)
	{
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE);//使能串口时钟
#ifndef USARTREMAP_1	
			GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);	//禁止串口管脚重映射
#else
			GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);		//串口管脚重映射
#endif
			STM32_GpioOneInit(USARTPIN_IN_1, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_1);	//浮空输入
			STM32_GpioOneInit(USARTPIN_OUT_1,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_1);				//推挽复用输出
			break;
		case 2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_AFIO, ENABLE);//使能串口时钟
#ifndef USARTREMAP_2	
			GPIO_PinRemapConfig(GPIO_Remap_USART2, DISABLE);	//禁止串口管脚重映射
#else
			GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);		//串口管脚重映射
#endif
			STM32_GpioOneInit(USARTPIN_IN_2, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_2);	//浮空输入
			STM32_GpioOneInit(USARTPIN_OUT_2,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_2);				//推挽复用输出
			break;
#endif
#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case 3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB2Periph_AFIO, ENABLE);//使能串口时钟
#ifdef USARTREMAP_3_OFF	
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);	//禁止串口3的部分重映像
			GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);		//禁止串口3的完全重映像
#endif
		
#ifdef USARTREMAP_3_TOPORTC
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//开启串口3的部分重映像
#endif
		
#ifdef USARTREMAP_3_TOPORTD
			GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);			//开启串口3的完全重映像
#endif
		
			STM32_GpioOneInit(USARTPIN_IN_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_3);	//浮空输入
			STM32_GpioOneInit(USARTPIN_OUT_3,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_3);				//推挽复用输出
			break;
#endif

#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case 4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4|RCC_APB2Periph_AFIO, ENABLE);//使能串口时钟
			STM32_GpioOneInit(USARTPIN_IN_4, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_4);	//浮空输入
			STM32_GpioOneInit(USARTPIN_OUT_4,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_4);				//推挽复用输出
			break;
		case 5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5|RCC_APB2Periph_AFIO, ENABLE);//使能串口时钟
			STM32_GpioOneInit(USARTPIN_IN_5, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_5_IN);	//浮空输入
			STM32_GpioOneInit(USARTPIN_OUT_5,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_5_OUT);				//推挽复用输出
			break;
#endif
	}
}
/**
  * 功  能：配置串口的优先级
  * 参  数：
	* Preemption：抢占优先级
	* Sub				：响应优先级
  * 返回值：无
  */
void SerialPort::setPriority(uint8_t Preemption,uint8_t Sub)
{
	uint8_t temPreemptionPriority = Preemption;
	uint8_t temSubPriority = Sub;
	setIRQPriority(USART_IRQn,temPreemptionPriority,temSubPriority);
}

/**
  * 功  能：串口的初始化
  * 参  数：
  * 返回值：无
  */
void SerialPort::initUsart()
{
	switch(port)
	{
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
		case PORT_1:
			COM=&USART_data_1;
			COM->usart=USART1;
			USART_IRQn=USART1_IRQn;
			break;
		case PORT_2:
			COM=&USART_data_2;
			COM->usart=USART2;
			USART_IRQn=USART2_IRQn;
			break;
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case PORT_3:
			COM=&USART_data_3;
			COM->usart=USART3;
			USART_IRQn=USART3_IRQn;
			break;
#endif
		
#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case PORT_4:
			COM=&USART_data_4;
			COM->usart=UART4;
			USART_IRQn=UART4_IRQn;
			break;
		case PORT_5:
			COM=&USART_data_5;
			COM->usart=UART5;
			USART_IRQn=UART5_IRQn;
			break;
#endif
		default: //串口号不符合规范
// 			while(1);
			break;
	}
		usartGpioInit();
		setIRQPriority(USART_IRQn,0X00,0X00);//配置优先级 ,默认的是最高优先级
		usartConfig(COM->usart, baudrate, USART_Mode_Tx|USART_Mode_Rx);//配置串口
		USART_ITConfig(COM->usart, USART_IT_RXNE, ENABLE);//使能接收中断
// 		USART_ITConfig(COM->usart, USART_IT_TC, ENABLE);	//使能发送完成中断
}

/**
  * 功  能：设置485通信方式的发送控制引脚
  * 参  数：
	*	port_ctrTx：控制引脚所在的端口号
	* pin_ctrTx ：控制引脚所在的引脚号
  * 返回值：无
  */
void SerialPort::setRS485CtrTx(GPIO_TypeDef* port_ctrTx,uint16_t pin_ctrTx)			//设置485控制引脚和端口等
{
	COM->useRS485Flag=true;			//设置串口属性是485属性
	COM->ctrTxPort=port_ctrTx;
	COM->ctrTxPin=pin_ctrTx;
	STM32_GpioOneInit(COM->ctrTxPin, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,COM->ctrTxPort);
}

/**
  * 功  能：获取串口的端口号
  * 参  数：无
  * 返回值：端口号
  */
int SerialPort::getPort()
{
	return port;
}

/**
  * 功  能：判定串口接收缓冲区是否有数据
  * 参  数：无
  * 返回值：
	*			true:有数据
  * 		false:无数据
  */
bool SerialPort::readAllow()
{
		return COM->rxBuffer_GetAvailableStatus();
}

/**
  * 功  能：从串口缓冲区中读取一个字节
  * 参  数：无
  * 返回值：读取的值
  */
uint8_t SerialPort::getChar(void)
{
	return COM->rxBuffer_GetByte();
}

/**
  * 功  能：写一个数据到串口发送缓冲区
  * 参  数：待写的数据
  * 返回值：
	*			true:写入成功
	*			false:写入失败
  */
bool SerialPort::putChar(uint8_t data)
{
	return COM->txBuffer_PutByte(data);
}

/**
  * 功  能：写一串数据到串口缓冲区
  * 参  数：
	*			data：数组的指针
	*			maxSize：待写的长度
  * 返回值：无
  */
void SerialPort::write(uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(!putChar(data[i]));
}

/**
  * 功  能：写一个字符串到串口缓冲区
  * 参  数：
	*			data：字符串指针
  * 返回值：无
  */
void SerialPort::writeLine(const char* data)
{
	while(*data)
	{
		while(!putChar(*data));
		data++;
	}
}

/**
  * 功  能：打开串口
  * 参  数：无
  * 返回值：无
  */
void SerialPort::open()						  //打开串口
{
	if(COM->usart==NULL)
		return;
	USART_Cmd(COM->usart, ENABLE);
}

/**
  * 功  能：关闭串口
  * 参  数：无
  * 返回值：无
  */
void SerialPort::close()							//关闭串口
{
	if(COM->usart==NULL)
		return;
	USART_Cmd(COM->usart, DISABLE);
}




//	以下是串口中断函数的实现
/**************************************注意事项********************************************

*串口3、4、5只支持一些特定的单片机类型，以下用宏控制定义了中断函数的有无
*另外，启动文件最好使用MDK自动生成的，工程中的配置Target Options->c/c++->Define
*输入框中填写响应的CPU类型宏否则会出现中断进不去的情况
*串口发送完成的中断不必要打开，该中断在多缓存发送时才有必要使用
*USART_IT_TXE标志清零是硬件自动清零的，不能用USART_ClearITPendingBit(USART3,USART_IT_TXE)清零
********************************************************************************************/

extern "C" {
	
/**************************** USART1 IRQHandler ********************************/
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
	
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    //	从USART_DR读一个字节
		USART_data_1.rxComplete();
  }  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	
  { 
		//	通过写USART_DR自动清除USART_IT_TXE标志位 
    //	写一个字节到USART_DR
		USART_data_1.dataRegEmpty();
  }                          
}

/**************************** USART2 IRQHandler ********************************/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    //	从USART_DR读一个字节
		USART_data_2.rxComplete();  
  }  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
		//	通过写USART_DR自动清除USART_IT_TXE标志位 
    //	写一个字节到USART_DR
		USART_data_2.dataRegEmpty(); 
  }
}
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
/**************************** USART3 IRQHandler ********************************/
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    //	从USART_DR读一个字节
		USART_data_3.rxComplete();  
  }  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 
		//	通过写USART_DR自动清除USART_IT_TXE标志位 
    //	写一个字节到USART_DR
		USART_data_3.dataRegEmpty();   
  }
}
#endif


#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)

/**************************** USART4 IRQHandler ********************************************/
void UART4_IRQHandler(void)
{	
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    //	从USART_DR读一个字节
		USART_data_4.rxComplete();		
  }  
  if(USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
  {
		//	通过写USART_DR自动清除USART_IT_TXE标志位 
    //	写一个字节到USART_DR
 		USART_data_4.dataRegEmpty();
  }
}


/**************************** USART5 IRQHandler ********************************/
void UART5_IRQHandler(void)
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    //	从USART_DR读一个字节
		USART_data_5.rxComplete();  
  }  
  if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
  {  
		//	通过写USART_DR自动清除USART_IT_TXE标志位 
    //	写一个字节到USART_DR
		USART_data_5.dataRegEmpty();   
  }
}
#endif
}

