/**
  ******************************************************************************
	*文件：Protocol.h
	*作者：孟浩
	*版本：1.0
	*日期：2015-05-28
	*概要：与核心板、左按键板、右按键板通信
	*备注：
	*
  ******************************************************************************  
  */ 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _PROTOCOL_H
	#define _PROTOCOL_H

	/* 头文件包含 ------------------------------------------------------------------*/
	#include "SerialPort.h"
	#include "DataChain.h"
	#include "IoOut.h"
	
	
	#define COM_BOT_ID 					0x00
	#define COM_CTR_ID 					0x01
	#define COM_PAD_ID 					0x02
	
	#define	COMN1_485_PIN				GPIO_Pin_8
	#define	COMN1_485_PORT				GPIOA
	
	#define COMN1_SEND_LENGTH 			12
	#define COMN1_SEND_DATA_LENGTH 		COMN1_SEND_LENGTH-3
	#define COMN1_SEND_HEAD 			0xA6
	#define COMN1_RECEIVE_LENGTH 		12
	#define COMN1_RECEIVE_HEAD 			0xA7


	#define	COMN2_485_PIN				GPIO_Pin_8
	#define	COMN2_485_PORT				GPIOA
	
	#define COMN2_SEND_LENGTH 			12
	#define COMN2_SEND_DATA_LENGTH 		COMN2_SEND_LENGTH-3
	#define COMN2_SEND_HEAD 			0xA4
	#define COMN2_RECEIVE_LENGTH 		12
	#define COMN2_RECEIVE_HEAD 			0xA5

	class Protocol
	{
		public:
			Protocol(SerialPort *comNum);							//	构造函数
			Protocol(SerialPort *comNum1,SerialPort *comNum2);		//	构造函数
			~Protocol();											//	析构函数
			
			void		com1st_Init();								//	com1st初始化
			void 		com1st_UpdateSendBuf(uint8_t* );			//	com1st更新数据 
			void 		com1st_Send();								//	com1st发送数据
			bool 		com1st_Receive();							//	com1st接收数据
			uint8_t* 	com1st_GetData();							//	获取com1st接收到的数据
			
			void		com2nd_Init();								//	com2nd_初始化
			void 		com2nd_UpdateSendBuf(uint8_t* );			//	com2nd_更新数据 
			void 		com2nd_Send();								//	com2nd_发送数据
			bool 		com2nd_Receive();							//	com2nd_接收数据
			uint8_t* 	com2nd_GetData();							//	获取com2nd_接收到的数据
		
			SerialPort 	*com1st;									//	com1st端口
			SerialPort 	*com2nd;									//	com2nd_端口
		private:
			
			uint8_t		*com1st_SendBuf;							//	com1st发送数组
			uint8_t		*com1st_ReceiveBuf;							//	com1st接收数组
			RingChain 	*com1st_ReceiveChain;						//	com1st接收数据链表					
			
			uint8_t		*com2nd_SendBuf;							//	com2nd_发送数组
			uint8_t		*com2nd_ReceiveBuf;							//	com2nd_接收数组
			RingChain 	*com2nd_ReceiveChain;						//	com2nd_接收数据链表		
	};

#endif

