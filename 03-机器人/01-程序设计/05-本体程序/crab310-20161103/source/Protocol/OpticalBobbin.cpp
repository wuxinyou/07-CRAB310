/**
  ******************************************************************************
	*文件：OpticalBobbin.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-28
	*概要：光纤线缆盘设备的控制协议类的实现
	*备注：
  ******************************************************************************  
  */ 


/* 头文件包含 ------------------------------------------------------------------*/
#include "OpticalBobbin.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 

OpticalBobbin::OpticalBobbin(SerialPort * p):BaseControl(p)
{
	addr=0X0A;
	command=0X00;

	wireLength=0;		//线长，指留在盘中的线长
	speed=0;				//自动线缆盘的放线速度
	leftSpeed=0;		//右电机速度
	rightSpeed=0;		//右电机速度
	workStatus=0;		//线缆盘的控制状态
}
//OtherDeviceControl类析构函数
OpticalBobbin::~OpticalBobbin()
{
	
}

void OpticalBobbin::sendOpticalBobbinCommand()
{
	command&=0X00;
	command|=workStatus;
// 	data->DATA_16=0X00;
	data->DATA_8[0]=rightSpeed;
	data->DATA_8[1]=leftSpeed;
	sendCommand();
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}



