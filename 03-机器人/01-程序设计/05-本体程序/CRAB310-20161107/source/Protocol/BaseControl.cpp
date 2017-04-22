/**
  ******************************************************************************
	*文件：BaseControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电机及其他设备的协议的基类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 
	
	
/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 

//接收数组
uint8_t BaseControl::reciveBuf[PORT_AMOUNT][COMMAMD_LEN] ={0x00}; //分配内存到栈

//接收链表
RingChain* BaseControl::reciveChin[]={new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN),\
																			new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN),\
																			new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN)};
//构造函数
BaseControl::BaseControl(SerialPort *temPort)
{
	port=temPort;
	data=new ctrData();
	frameHeader=0XA4;
	addr=0X00;
	command=0X00;
	data->DATA_8[0]=0X00;
	data->DATA_8[1]=0X00;
	numCounter=0;
	errorFlag=0;
}

//析构函数
BaseControl::~BaseControl()
{
	for(int i=0;i<PORT_AMOUNT;i++)
		delete reciveChin[i];
	delete data;
}

/**
  * 功  能：发送命令
  * 参  数：无
  * 返回值：无
  * 
  */
void BaseControl::sendCommand()
{
	while(!port->putChar(frameHeader));
	while(!port->putChar(addr));
	while(!port->putChar(command));
	while(!port->putChar(data->DATA_8[1]));//先发高位
	while(!port->putChar(data->DATA_8[0]));//后发低位
	while(!port->putChar(subChecksum()));
}
/**
  * 功  能：重设计数器数值为0
  * 参  数：无
  * 返回值：无
  * 
  */
void BaseControl::resetNumCounter()
{
	numCounter=0;
}
/**
  * 功  能：设置错误编号
  * 参  数：错误号
  * 返回值：无
  * 
  */
void BaseControl::setErrorFlag(uint8_t value)
{
	if(value==0&&errorFlag>0x00&&errorFlag<0x08)
		return;
	errorFlag=value;
}
/**
  * 功  能：设置错误编号 用于软件自身的一些警告设置
  * 参  数：错误号
  * 返回值：无
  * 
  */
void BaseControl::setErrorFlag_1(uint8_t value)
{
	if(errorFlag<0x08)
		errorFlag=value;
}
/**
  * 功  能：接收函数
  * 参  数：接收的串口号
  * 返回值：无
  * 
  */
bool BaseControl::reciveData(SerialPort *temPort)
{
	uint8_t checkSum=0;
	bool readFlag=false;
	uint8_t arrayNum=temPort->getPort()-1;
	while (temPort->readAllow()&&(readFlag==false))
	{
		BaseControl::reciveChin[arrayNum]->setData(temPort->getChar());
		BaseControl::reciveChin[arrayNum]->next();
		if(reciveChin[arrayNum]->getData()==0XA4)//检测帧头	
		{	
			checkSum+=0XA4;
			reciveChin[arrayNum]->next();
			
			checkSum+=reciveChin[arrayNum]->getData();//地址
			reciveChin[arrayNum]->next();
			
			if((reciveChin[arrayNum]->getData()&0X40)==0x40)//方向位正确
			{
				for(int i=0;i<COMMAMD_LEN-3;i++)
				{
				   checkSum+=reciveChin[arrayNum]->getData();
				   reciveChin[arrayNum]->next();
				}
				if(checkSum==reciveChin[arrayNum]->getData())//校验和正确
				{
					//将数据存入数组
					for(int i=0;i<COMMAMD_LEN;i++)
					{
					   reciveChin[arrayNum]->next();
					   reciveBuf[arrayNum][i]=reciveChin[arrayNum]->getData();
					}
					readFlag=true;
				}
				reciveChin[arrayNum]->next();
			}
			else
			{
				reciveChin[arrayNum]->previous();//跳至上个节点	
				reciveChin[arrayNum]->previous();//跳至上个节点	
			}			
		 	checkSum=0;
		}
	}
	return 	readFlag;
}

/**
  * 功  能：计算校验和
  * 参  数：无
  * 返回值：无
  * 
  */
uint8_t BaseControl::subChecksum()
{
	uint8_t checksum=0;
	checksum+=frameHeader;
	checksum+=addr;
	checksum+=command;
	checksum+=data->DATA_8[1];
	checksum+=data->DATA_8[0];
	return checksum;
}






