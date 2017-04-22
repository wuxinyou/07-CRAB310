/**
  ******************************************************************************
	*文件：MotorControl.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电机协议类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 



/* 头文件包含 ------------------------------------------------------------------*/
#include "MotorControl.h"

/* 类型定义 --------------------------------------------------------------------*/
/* 宏定义-----------------------------------------------------------------------*/ 

//绝对值宏
#define ABS(X)			((X)>0?(X):(-(X)))

//运行到指定位置的角度误差范围（±2度）
#define ANGLE_ALLOWANCE 	50 

//减速临界位

#define ANGLE_SLOW_START	700
#define ANGLE_SLOW_GO			450
#define ANGLE_SLOW_DOWN		200



//构造函数
MotorControl::MotorControl(SerialPort * p):BaseControl(p)
{
	feedSpeed=0;								//需要设置的速度暂存	
	referSpeedMax=0;						//需要设置的参考最大速度
	referSpeedMin=0;						//需要设置的参考最小速度	
	feedPWMSpeed=0;
	feedAngle=0;								//需要设置的角度暂存
	feedZeroAngle=0;						//需要设置的零位角度暂存
	feedAngleMaxSpeed=0;				//需要设置的角度暂存

	feedMaxSpeed=0;							//需要设置的最大速度暂存
	feedCodedDiscLineNum=0;			//需要设置码盘线数暂存
	feedReductionRatio=0;				//需要设置减速比暂存
	feedAcceleration=0;			  	//需要设置加速度暂存
	feedDeceleration=0;			 	 	//需要设置减速度暂存
	feedCurrent=0;			  			//需要设置电流暂存
	feedContinuousCurrent=0;		//需要设置电流持续值暂存
	feedPeakCurrent=0;					//需要设置电流峰值暂存
	
	feedSpeed=0;								//需要设置的速度暂存	
	referSpeedMax=0;						//需要设置的参考最大速度
	referSpeedMin=0;						//需要设置的参考最小速度
	uspeedTime=0;								//u指令启动的时间参数
	resetUspeedTime();
}

//析构函数
MotorControl::~MotorControl()
{
// 	char* sss="电机协议类析构成功！\r\n";
// 	port->writeLine(sss);
}

/**
  * 功  能：发送速度控制指令到电机驱动器
  * 参  数：CommandType 命令的编号，既控制的类型
	* 参数值：0x01:设置速度，带回传，返回角度值
	*					0x02:设置速度，返回OK
	*					0x03:开环设置速度，返回OK
	*					0x04:设置最高速度 返回OK
	*					0x05:设置码盘线数 返回OK
	*					0x06:设置总减速比 返回OK
	*					0x07:设置加速度 返回OK
	*					0x08:设置减速度 返回OK
	*					0x09:读取速度 返回速度
	*					0x0a:读取温度 返回温度
	*					0x0b:保存设置 返回OK
	*					0x0c:使能运动 返回角度
  * 返回值：
  * 
  */
void MotorControl::sendSpeedCommand(int8_t CommandType)		//发送速度命令 参数：命令编号（命令的类型）
{
	if(CommandType<0x01||CommandType>0x0c) 									//检测参数范围
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=tem;
	switch(tem)
	{
		case 0x01:																					//设置速度，带回传，返回角度值
		case 0x02:																					//设置速度，返回OK
			data->DATA_16=feedSpeed;
			break;
		case 0x03:																					//开环设置速度(PWM控制)，返回OK
			data->DATA_16=feedPWMSpeed;
			break;
		case 0x04:																					//设置最高速度 返回OK
			data->DATA_16=feedMaxSpeed;
			break;
		case 0x05:																					//设置码盘线数 返回OK
			data->DATA_16=feedCodedDiscLineNum;
			break;
		case 0x06:																					//设置总减速比 返回OK
			data->DATA_16=feedReductionRatio;	
			break;
		case 0x07:																					//设置加速度 返回OK
			data->DATA_16=feedAcceleration;
			break;
		case 0x08:																					//设置减速度 返回OK
			data->DATA_16=feedDeceleration;
			break;
		case 0x09:																					//读取速度 返回速度
		case 0x0a:																					//读取温度 返回温度
		case 0x0b:																					//保存设置 返回OK
		case 0x0c:																					//使能运动 返回角度
			data->DATA_16=0x0000;
			break;
		default:
			break;
	}
	sendCommand();	//命令内容设置完毕，发送命令
	numCounter++;
	if(numCounter>21)
	{
		numCounter=21;
	}
}


/**
  * 功  能：发送电流控制指令到电机驱动器
  * 参  数：CommandType 命令的编号，既控制的类型
	* 参数值：0x01:设置电流，返回OK
	*					0x02:电流零点开启，返回OK
	*					0x03:电流调零，返回OK
	*					0x04:正向电流校准开启，返回OK
	*					0x05:正向电流校准，返回OK
	*					0x06:反向电流校准开启，返回OK
	*					0x07:反向电流校准，返回OK
	*					0x08:电流校准存储，返回OK
	*					0x09:设置持续电流，返回OK
	*					0x0a:设置峰值电流，返回0K
	*					0x0b:读取电流，返回电流
  * 返回值：无
  * 
  */
void MotorControl::sendCurrentCommand(int8_t CommandType)	//发送电流命令 参数：命令编号（命令的类型）
{
	if(CommandType<0x01||CommandType>0x0b) //检测参数范围
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=0x10;												//命令控制位置为电流发送
	command|=tem;
	switch(tem)
	{
		case 0x01:																					//设置电流，返回OK
			data->DATA_16=feedCurrent;
			break;
		case 0x02:																					//电流零点开启，返回OK
		case 0x03:																					//电流调零，返回OK
		case 0x04:																					//正向电流校准开启，返回OK
		case 0x05:																					//正向电流校准，返回OK
		case 0x06:																					//反向电流校准开启，返回OK
		case 0x07:																					//反向电流校准，返回OK
		case 0x08:																					//电流校准存储，返回OK
			data->DATA_16=0x0000;
			break;			
		case 0x09:																					//设置持续电流，返回OK
			data->DATA_16=feedContinuousCurrent;
			break;
		case 0x0a:																					//设置峰值电流，返回0K
			data->DATA_16=feedPeakCurrent;
			break;
		case 0x0b:																					//读取电流，返回电流
			data->DATA_16=0x0000;
			break;
		default:
			break;
	}
	sendCommand();	//命令内容设置完毕，发送命令
}


/**
  * 功  能：发送角度控制指令到电机驱动器
  * 参  数：CommandType 命令的编号，既控制的类型
	* 参数值：0x01:运行到响应的角度，返回0K
	*					0x02:设置限位失效，返回0K
	*					0x03:设置最大限位，返回0K
	*					0x04:设置最小限位，返回0K
	*					0x05:设置当前的角度值为参考值，返回0K 老版本0x06
	*					0x06:保存当前角度，返回0K	 老版本0x07
	*					0x07:读取角度，返回角度 老版本0x08
	*					0x08:设置位置运动的最大速度，返回0K  老版本0x09
  * 返回值：
  * 
  */
void MotorControl::sendAngleCommand(int8_t CommandType)		//发送角度命令 参数：命令编号（命令的类型）
{
	if(CommandType<0x01||CommandType>0x09) //检测参数范围 //此处新版协议需要修改成0x08****************
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=0x20;												//命令控制位置为角度发送
	command|=tem;
	if(tem==0x01)
	{
		data->DATA_16=feedAngle;
	}
	else if(tem==0x06)
	{
		data->DATA_16=feedZeroAngle;
	}
	else if(tem==0x09)									//此处新版协议需要修改成0x08**********************************
	{
		data->DATA_16=feedAngleMaxSpeed;
	}
	else
	{
		data->DATA_16=0x0000;
	}
	sendCommand();	//命令内容设置完毕，发送命令
}

/**
  * 功  能：设置速度
  * 参  数：速度的参考值
  * 返回值：无
  * 
  */
void MotorControl::setSpeed(int16_t value)
{
	int16_t temValue=value;
	if(temValue>0&&temValue<200)
	{
		temValue=200;
	}
	else if(temValue<0&&temValue>-200)
	{
		temValue=-200;
	}
	feedSpeed=temValue;
}

void MotorControl::setSpeed_1(int16_t value)
{
	int16_t temValue=value;
	feedSpeed=temValue;
}
/**
  * 功  能：根据角度差和时间差设置速度
  * 参  数：
					subA:			角度差
					sunT:			时间差
					sunMAXT:	时间差的最大值
  * 返回值：无
  * 
  */
void MotorControl::setSpeedFromSubAngle(int64_t subA,int64_t sunT,int64_t sunMaxT)
{
	if(ABS(subA)>ANGLE_ALLOWANCE)//误差在 ±0.5 度
	{
		
		if(ABS(subA)>ANGLE_SLOW_START) 
			setSpeed((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));	  //一级速度 最大速度 
		else if(ABS(subA)>ANGLE_SLOW_GO) 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*18*sunT/sunMaxT));//二级速度 最大速度的9/10
		else if(ABS(subA)>ANGLE_SLOW_DOWN) 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*15*sunT/sunMaxT));	//三级速度 最大速度的3/4
		else															 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*5*sunT/sunMaxT));		//四级速度 最大速度的1/2
	}
	else																													//角度到达位置 置速度0
	{
		resetSpeed();
	}
}
/**
  * 功  能：根据角度差和时间差设置速度 该函数没有限制
  * 参  数：
					subA:			角度差
					sunT:			时间差
					sunMAXT:	时间差的最大值
  * 返回值：无
  * 
  */
void MotorControl::setSpeedFromSubAngle_1(int64_t subA,int64_t sunT,int64_t sunMaxT)
{
	if(ABS(subA)>5)//误差在 ±0.5 度
	{
			setSpeed_1((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));	  //一级速度 最大速度 
	}
	else																													//角度到达位置 置速度0
	{
		resetSpeed();
	}
}
/**
  * 功  能：回调方式实现 根据角度差设置速度
  * 参  数：
	*				fun：			回调函数指针
	*				subA:			角度差
	*				sunT:			时间差
	*				sunMAXT:	时间差的最大值
  * 返回值：无
  * 
  */
void MotorControl::setSpeedFromSubAngle(setSpeedFun fun,int64_t subA,int64_t sunT,int64_t sunMaxT)	//根据角度差设置速度
{
	if(ABS(subA)>ANGLE_ALLOWANCE)//误差在 ±0.5 度
	{
// 		setSpeed((int16_t)(((int)referSpeedMin)*5*sunT/sunMaxT));		//四级速度 最大速度的1/2
		if(ABS(subA)>ANGLE_SLOW_START)//角度差10度以上
			fun((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));
		else if(ABS(subA)>ANGLE_SLOW_GO)//4.5-10
			fun((int16_t)(((int64_t)referSpeedMin)*18*sunT/sunMaxT));
		else if(ABS(subA)>ANGLE_SLOW_DOWN)//2.0-4.5
			fun((int16_t)(((int64_t)referSpeedMin)*15*sunT/sunMaxT));
		else
			fun((int16_t)(((int64_t)referSpeedMin)*5*sunT/sunMaxT));
	}
	else								//速度置0
	{
		resetSpeed();
	}
}

/**
  * 功  能：更新U指令时间，用于自动实现电机的释放
  * 参  数：无
  * 返回值：无
  * 
  */
void MotorControl::updateUspeedTime()										//更新U指令时间
{
	
	if(feedSpeed==0)
		uspeedTime++;
	else
	{
		feedPWMSpeed=0;
		uspeedTime=0;
	}
	if(uspeedTime>3500)                                //非零U指令持续时间3500-UO_TIME_MAX=3秒
	{
		uspeedTime=UO_TIME_MAX;
		feedPWMSpeed=0;
	}
}

/**
  * 功  能：发送速度命令 可以根据超时参数自动判断V 和 u
  * 参  数：无
  * 返回值：无
  * 
  */
void MotorControl::sendSpeedCommand()
{
	if(uspeedTime<UO_TIME_MAX)
		sendSpeedCommand(0x01);
	else
		sendSpeedCommand(0x03);
}





