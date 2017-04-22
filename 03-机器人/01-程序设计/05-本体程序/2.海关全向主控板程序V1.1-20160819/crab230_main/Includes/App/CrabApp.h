 /* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _CRAB_APP_H
#define _CRAB_APP_H

/* 头文件包含 ------------------------------------------------------------------*/
#include "MotorControl.h" 
#include "TerminalControl.h" 
#include "Timer.h"
#include "LEDLighter.h" 
#include "CamControl.h"
#include "VideoControl.h"
#include "Key.h"
#include "Mpu6050Control.h"
#ifdef __cplusplus  
extern "C"
{
#endif
	#include "STM32_Adc.h"
	#include "STM32F4_GpioInit.h"
 	#include "STM32F4_PwmOut.h" 
#ifdef __cplusplus
}
#endif
/* 类型定义 --------------------------------------------------------------------*/
//枚举模式ID
/* 宏定义-----------------------------------------------------------------------*/ 
//绝对值宏
#define ABS(X)			((X)>0?(X):(-(X)))
//二者绝对值谁大谁小宏
#define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
#define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))
//帧长度
#define TERMINAL_FRAME_LEN 10
//全向轮子数量
#define WHEEL_NUM 4
//速度档位数量
#define SPEED_KK 4
//速度档位数量
#define SPEED_MAX 8000
//自动模式设置 
#define MODE_AUTO_FINISH  	0x02 
#define MODE_AUTO 					0x01
#define MODE_MANUAL  				0x00

#define AUTO_RUN_SPEED 			1000
#define AUTO_TURN_SPEED 		100
//红外状态
#define INFRA_ON   		0x00
#define INFRA_OFF			0x01
#define KEYINDEX_MAX 	10
//4个电机地址的定义
#define LEFTUP_DDR  		0
#define LEFTDOWN_DDR		1
#define RIGHTUP_DDR			2
#define RIGHTDOWN_DDR		3
//默认的云台默认PWM
#define DEFAULT_PWM 		100
//接收无线信号超时时间
#define TICKET_MAX  		2000
//摇杆死区设置
#define MOVE_MID				0X80  //128
#define MOVE_MID1				0X66  //112
#define MOVE_MID2				0X98  //144
#define MOVE_DEADAREA 	25
//串口设置宏 
#define		WIRE_LESS_PORT_NUM			2
#define		WHEEL_PORT_NUM					3
#define		CAM_PORT_NUM						4
#define		VIDEO_PORT_NUM					5 
#define		MPU6050_PORT_NUM				6 

#define		WIRE_LESS_PORT_BAUD		9600
#define		WHEEL_PORT_BAUD				38400
#define		CAM_PORT_BAUD					9600
#define		VIDEO_PORT_BAUD				9600 
#define		MPU6050_PORT_BAUD			115200 
//电量显示间隔
#define POW_LED_TICK1  60
#define POW_LED_TICK2  30

class CrabApp
{
public:
	CrabApp();
	~CrabApp();
	void openUserInterrupt();
	void runOnTime2();								//运行在定时器TIM2中的函数
	void runOnTime3();								//运行在定时器TIM3中的函数
	void runOnTime4();								//运行在定时器TIM4中的函数 
private:
	int16_t *wheelspeed;
	uint8_t *fBTerminalData;
	Timer *t1;												//定时器1
	Timer *t2;												//定时器2
	Timer *t3;												//定时器3

	LEDLighter *led_1; 
	LEDLighter *led_2;
  LEDLighter *led_3;

	SerialPort *wireLessPort;				//和终端无线通信的串口
	SerialPort *wheelPort;					//和4个驱动轮的串口
	SerialPort *camPort;						//和行车相机通信的串口
	SerialPort *videoPort;					//和4画面切换板通信的串口
	SerialPort *mpu6050Port;					//和4画面切换板通信的串口

	TerminalControl *Terminal;								//终端通信的协议类变量
	Mpu6050Control *mpu6050;
	Key *infra;
  
	MotorControl *frontLeftMotor;							//左上电机
	MotorControl *rearLeftMotor;							//左下电机
	MotorControl *frontRightMotor;						//右上电机
	MotorControl *rearRightMotor;							//右下电机 
	
	ctrData *fBEctQuantity_1;									//反馈的电源电量1暂存
	ctrData *fBEctQuantity_2;									//反馈的电源电量2暂存
	
  uint8_t workmode;
	uint8_t workmodesta;
	uint8_t autotime;
	bool rockeysta;
	bool turnstartflag;
	uint8_t infrasta;
	int16_t robotangle;
	uint8_t camlenscommand;
  uint8_t zoomstatus;
	CamControl *driverCam;
	uint8_t videochannel;
	VideoControl *videocont;
 
	float leftbatvoltage;				//左电池电量
	float rightbatvoltage;				//右电池电量
 
 	int16_t pantitlepwm; 
	
	bool recflag;
private:
	
  	void resetvaule();
  	void disposeTerminalData();
  	void updateSendTerminalData();								//更新要发送到终端的数据
		void sendDriverMotorData();
		void sendCamData();
		void sendVideoChangeData();
  	void updateSendDriverData();									//更新要发送到所有设备的数据
		void lightcontrol(uint8_t* recdata);
		int16_t wheelspeedcal(int16_t speeddata,int16_t speedKK);
		int16_t setwheelspeed(int16_t *wheelsp,int16_t *speedref,int16_t speedK);
		void mecanumwheelcontrol(uint8_t* recdata);
		void cradlecontrol(uint8_t* recdata);
		void fpvchannelconf(uint8_t channel);
		void fpvchannelchange(uint8_t* recdata); 
		void radiochannelchange(uint8_t* recdata);
		void camlencontrol(uint8_t* recdata); 
		void videochanelcontrol(uint8_t* recdata);
		uint8_t workmodedetect(uint8_t* recdata);
		void autoruncontrol();
		uint8_t autoturncontrol();
		void infrascan();
		float subEctQuantity(float* leftbat,float* rightbat);
		void powerledshow(float batvaule);
};
#endif 









