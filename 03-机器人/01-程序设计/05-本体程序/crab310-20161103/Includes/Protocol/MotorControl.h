/**
  ******************************************************************************
	*文件：MotorControl.h
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：电机协议类的头文件
	*备注：
	*
  ******************************************************************************  
	*/ 
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "BaseControl.h"     //协议的基类

/* 类型定义 --------------------------------------------------------------------*/
typedef uint8_t(*setSpeedFun)(int16_t);
/* 宏定义-----------------------------------------------------------------------*/ 
//U0指令发送的临界时间
#define UO_TIME_MAX				500


class MotorControl : public BaseControl
{
public:
	MotorControl(SerialPort * p);
	virtual ~MotorControl();

	void updateUspeedTime();										//更新U指令时间
	void sendSpeedCommand();										//发送速度命令 可以根据超时参数自动判断V 和 u

	void sendSpeedCommand(int8_t);							//发送速度命令 参数：命令编号（命令的类型）
	void sendCurrentCommand(int8_t);						//发送电流命令 参数：命令编号（命令的类型）
	void sendAngleCommand(int8_t);							//发送角度命令 参数：命令编号（命令的类型）

	void setSpeedFromSubAngle(int64_t,int64_t,int64_t);			//根据角度差设置速度
	void setSpeedFromSubAngle_1(int64_t,int64_t,int64_t);			//根据角度差设置速度
	void setSpeed(int16_t);
	void setSpeed_1(int16_t);
	void setPWMSpeed(int16_t value){feedPWMSpeed=value;}

	void setAngle(int16_t value)								{feedAngle=value;}
	void setZeroAngle(int16_t value)						{feedZeroAngle=value;}
	void setAngleMaxSpeed(int16_t value)				{feedAngleMaxSpeed=value;}

	void setMaxSpeed(int16_t value)							{feedMaxSpeed=value;}
	void setCodedDiscLineNum(int16_t value)			{feedCodedDiscLineNum=value;}
	void setReductionRatio(int16_t value)				{feedReductionRatio=value;}
	void setAcceleration(int16_t value)					{feedAcceleration=value;}
	void setDeceleration(int16_t value)					{feedDeceleration=value;}
	void setCurrent(int16_t value)							{feedCurrent=value;}
	void setContinuousCurrent(int16_t value)		{feedContinuousCurrent=value;}
	void setPeakCurrent(int16_t value)					{feedPeakCurrent=value;}
	void setReferSpeedMax(int16_t value)				{referSpeedMax=value;}
	void setReferSpeedMin(int16_t value)				{referSpeedMin=value;}
	void resetUspeedTime(){uspeedTime=UO_TIME_MAX;}
	int16_t getSpeed(){return feedSpeed;}
	int16_t getPWMSpeed(){return feedPWMSpeed;}
	int16_t getPWMSpeedTime(){return uspeedTime;}
	void setReferMaxSpeed(bool direction)
	{
		if(direction)
			feedSpeed=referSpeedMin;
		else
			feedSpeed=-referSpeedMin;
	}
	
	
// 						{feedSpeed=(direction?referSpeedMax:(-referSpeedMax));}
	void setReferMinSpeed(bool direction)						{feedSpeed=(direction?referSpeedMin:(-referSpeedMin));}
	
	void resetSpeed(){feedSpeed=0;}
  void setSpeedFromSubAngle(setSpeedFun,int64_t,int64_t,int64_t);	//根据角度差设置速度
protected:
	int16_t uspeedTime;								//u指令启动的时间参数
	int16_t feedAngle;								//需要设置的角度暂存
	int16_t feedZeroAngle;						//需要设置的零位角度暂存
	int16_t feedAngleMaxSpeed;				//需要设置的角度暂存
	int16_t feedSpeed;								//需要设置的速度暂存
	int16_t feedPWMSpeed;							//需要设置PWM占空比参数
	int16_t feedMaxSpeed;							//需要设置的最大速度暂存
	int16_t feedCodedDiscLineNum;			//需要设置码盘线数暂存
	int16_t feedReductionRatio;				//需要设置减速比暂存
	int16_t feedAcceleration;			  	//需要设置加速度暂存
	int16_t feedDeceleration;			 	 	//需要设置减速度暂存
	int16_t feedCurrent;			  			//需要设置电流暂存
	int16_t feedContinuousCurrent;		//需要设置电流持续值暂存
	int16_t feedPeakCurrent;					//需要设置电流峰值暂存	

	int16_t referSpeedMax;						//需要设置的参考最大速度
	int16_t referSpeedMin;						//需要设置的参考最小速度
};
#endif  /*_MOTOR_CONTROL_H */


