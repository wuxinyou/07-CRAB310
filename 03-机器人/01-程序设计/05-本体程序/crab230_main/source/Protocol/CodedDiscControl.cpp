/**
  ******************************************************************************
	*文件：CodedDiscControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：码盘协议类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "CodedDiscControl.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/

//发送的命令数组
static uint8_t getCodeDiscComm[6]={0xaa, 0xbb, 0x01, 0xcc, 0xcc, 0xcc};

//构造函数
CodedDiscControl::CodedDiscControl(SerialPort * p)
{
	port=p;
	cylinder=new CodeDiscData();
	angle=new CodeDiscData();
	ADCangle=0;
}

//析构函数
CodedDiscControl::~CodedDiscControl()
{
	delete cylinder;
	delete angle;
}
/**
  * 功  能：重设计数器数值为0
  * 参  数：无
  * 返回值：无
  * 
  */
void CodedDiscControl::resetNumCounter()
{
	numCounter=0;
}
/**
  * 功  能：设置错误编号
  * 参  数：错误号
  * 返回值：无
  * 
  */
void CodedDiscControl::setErrorFlag(uint8_t value)
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
void CodedDiscControl::setErrorFlag_1(uint8_t value)
{
	if(errorFlag<0x08)
		errorFlag=value;
}
/**
  * 功  能：发送查询码盘角度命令
  * 参  数：无
  * 返回值：无
  * 
  */
void CodedDiscControl::sendCodeDiscCommand()				//发送查询码盘角度命令
{
	port->write(getCodeDiscComm,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * 功  能：接收码盘数据
  * 参  数：无
  * 返回值：接收成功帧的标志
	*					true:成功接收到一帧
  * 				false:单前帧没接收完
  */
bool CodedDiscControl::reciveData()
{
	//帧头 aa bb 01
	bool readFlag=false;
	static bool headFlag=false;
	static uint8_t head[3]={0,0,0};
	static uint8_t index=0;
	while (port->readAllow()&&(readFlag==false))
	{
		if(headFlag)//帧头接收到
		{
			if(index==0)
			{
				cylinder->DATA_8[1]=0;
				cylinder->DATA_8[0]=port->getChar();
			}
			else if(index==1)
				angle->DATA_8[1]=port->getChar();
			else if(index==2)
				angle->DATA_8[0]=port->getChar();
			
			index++;
			if(index>2)
			{
				readFlag=true;
				index=0;
				headFlag=false;
			}
		}
		else//帧头没收到
		{
			head[2]=head[1];
			head[1]=head[0];
			head[0]=port->getChar();
			if(head[0]==0x01&&head[1]==0xbb&&head[2]==0xaa)
			{
				headFlag=true;
			}
		}
	}
	return readFlag;
}
uint16_t CodedDiscControl::getADCAngle()
{
	ADCangle=getADCValue()&0x0fff;
	return ADCangle;
}

void CodedDiscControl::initADC()
{
	Adc1DmaInit();
	ADC_SoftwareStartConv(ADC1);
}









