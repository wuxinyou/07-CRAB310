/* 头文件包含 ------------------------------------------------------------------*/
#include "CrabApp.h"
#include <stdlib.h>
#include "STM32F4_SysTick.h"
#include <math.h>
/* 类型定义 --------------------------------------------------------------------*/
//20160807改变成新协议
CrabApp::CrabApp()
{ 
	STM32_GpioInit();
	STM32_GpioOneInit(__GPIO_D_LIGHT_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_D_LIGHT_PORT); 
	STM32_GpioOneInit(__GPIO_W_LIGHT_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_W_LIGHT_PORT); 
	STM32_GpioOneInit(__GPIO_RELAY_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_RELAY_PORT);  
	STM32_GpioOneInit(__GPIO_POLED_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_POLED_PORT);  
	STM32_GpioOneInit(__GPIO_ACH1_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_ACH1_PORT);  
	STM32_GpioOneInit(__GPIO_ACH2_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_ACH2_PORT);  
	STM32_GpioOneInit(__GPIO_ACH3_PIN,GPIO_Speed_50MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,__GPIO_ACH3_PORT);  
	
	fpvchannelconf(0);
	
	led_1 = new LEDLighter(GPIOE,GPIO_Pin_11);	//默认点亮
	led_2 = new LEDLighter(GPIOE,GPIO_Pin_12);	//默认点亮
	led_3 = new LEDLighter(GPIOE,GPIO_Pin_13);	//默认点亮
	
	led_1->setLightOn();
	led_2->setLightOn();
	led_3->setLightOn();
	POLED_ON;
	SysTick_DelayMs(2000);											//延时2秒，等待设备启动
	SysTick_DelayMs(2000);											//延时2秒，等待设备启动
	led_1->setLightOff();
	led_2->setLightOff();
	led_3->setLightOff();
	
	//定时器初始化
	t1=new Timer(TIM2);
	t1->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);
	t1->setTimeOut(1);

	t2=new Timer(TIM3);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	t2->setTimeOut(15);

	t3=new Timer(TIM4);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
	t3->setTimeOut(100); 
	
 	infra	=	new Key(GPIOC,GPIO_Pin_4);//
 
 	wireLessPort 	=	new SerialPort(WIRE_LESS_PORT_NUM,WIRE_LESS_PORT_BAUD);		//和终端无线通信的串口 
	wheelPort 		=	new SerialPort(WHEEL_PORT_NUM,WHEEL_PORT_BAUD);						//和4个驱动轮的串口
	camPort 			=	new SerialPort(CAM_PORT_NUM,CAM_PORT_BAUD);								//和行车相机通信的串口
	videoPort 		=	new SerialPort(VIDEO_PORT_NUM,VIDEO_PORT_BAUD);						//和4画面切换板通信的串口
 	mpu6050Port		=	new SerialPort(MPU6050_PORT_NUM,MPU6050_PORT_BAUD);				//和MPU6050的通信串口
 
	frontLeftMotor 	= new MotorControl(wheelPort);
	rearLeftMotor 	= new MotorControl(wheelPort);
	frontRightMotor = new MotorControl(wheelPort);
	rearRightMotor 	= new MotorControl(wheelPort);

	
	//设备地址设定
	frontLeftMotor->setAddr(LEFTUP_DDR);
	rearLeftMotor->setAddr(LEFTDOWN_DDR);
	frontRightMotor->setAddr(RIGHTUP_DDR);
	rearRightMotor->setAddr(RIGHTDOWN_DDR);
	
 	mpu6050  	= new Mpu6050Control(mpu6050Port);
 	Terminal 	= new TerminalControl(wireLessPort);
	driverCam = new CamControl(camPort);
	videocont = new VideoControl(videoPort);
	 
	wheelspeed = new int16_t[WHEEL_NUM];
	for(int i=0;i<WHEEL_NUM;i++)
		wheelspeed[i]=0x00;
		
	fBTerminalData=	new uint8_t[TERMINAL_FRAME_LEN]; 													//终端反馈数据暂存
	for(int i=0;i<TERMINAL_FRAME_LEN;i++)
		fBTerminalData[i]=0;
	
	fBEctQuantity_1=		new ctrData();				//反馈的电源电量暂存
	fBEctQuantity_2=		new ctrData();				//反馈的电源电量暂存
	
	workmode 				= MODE_MANUAL;
	workmodesta			= MODE_MANUAL;
	autotime				= 0;
	rockeyXsta				= false;
	rockeyYsta				= false;																		//摇杆工作状态，用于自动模式判断
	turnstartflag		= false;
	infrasta 				= 0;
	robotangle			=	0;
	camlenscommand 	= 0;
	videochannel 		= VIDEO_1;
	zoomstatus 			= 0;
	pantitlepwm 		= 0;
	Adc1DmaInit();
	STM32_Timer9InitAsPwm();
	ServoControl(0);
	D_LIGHT_OFF;
	W_LIGHT_OFF;
	RELAY_ON; 
	recflag = false;
}
 

CrabApp::~CrabApp()
{
	delete t1;
	delete t2;
	delete t3;
	delete wireLessPort;
	delete wheelPort;
	delete camPort;
	delete videoPort;
	delete mpu6050Port;
	delete frontLeftMotor;
	delete rearLeftMotor;
	delete frontRightMotor;
	delete rearRightMotor;
	
	delete driverCam;
	delete videocont;
	delete Terminal;
	
}
/**
  * 功  能：运行在定时器2中的函数，主要作用是解析和更新各个设备的数据
  * 参  数：无
  * 返回值：无
  * 
  */

void CrabApp::openUserInterrupt()
{
  wireLessPort->open();
	wheelPort->open();
	camPort->open();
	videoPort->open();
 	mpu6050Port->open();
	
 	t1->start();
	t2->start();
 	t3->start();
}
/**
  * 功  能：运行在定时器2中的函数，主要作用是解析和更新各个设备的数据,中断时间1ms
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::runOnTime2()
{ 
	static uint16_t ticket=0,recteck=0;
	if(Terminal->reciveData())								//检测终端控制数据，如果成功接收一帧，则反馈数据并处理数据
	{ 
 		led_1->reverseLight();
		disposeTerminalData();									//处理终端的数据
// 		updateSendTerminalData();								//更新要发送到终端的数据 
// 		Terminal->sendcommand();								//发送数据到终端 
 
		ticket = 0;
	}
	else 
	{ 
		if(ticket>=TICKET_MAX)
		{
			ticket = 0;
			resetvaule();
		}
		else
		{
			ticket++;
		}
	} 
	frontLeftMotor->updateUspeedTime();
	rearLeftMotor->updateUspeedTime();
	frontRightMotor->updateUspeedTime();
	rearRightMotor->updateUspeedTime();	
	 
 	//偏航角度获取
  if(mpu6050->dealrecData())
	{
		led_3->reverseLight();
		robotangle = mpu6050->getRoatAngle();
	} 
} 
/**
  * 功  能：运行在定时器2中的函数，中断10ms
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::runOnTime3()
{    
	infrascan();  																										//红外状态获取
	if((rockeyYsta == false)&&(rockeyXsta==false))																					//摇杆处在中位的时候
	{
		leftbatvoltage 	= getbatvolt(ADC_BAT1);													//左电池电压
		rightbatvoltage = getbatvolt(ADC_BAT2);													//右电池电压  
		powerledshow(subEctQuantity(&leftbatvoltage,&rightbatvoltage));	//电压电量显示 
	}
	ServoControl(pantitlepwm);																			//舵机控制 
	updateSendDriverData();																					//更新要发送到所有设备的数据 
} 
/**
  * 功  能：运行在定时器2中的函数，主要作用是解析和更新各个设备的数据,时间100ms
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::runOnTime4()
{  
} 
/**
  * 功  能：复位所有数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::resetvaule()		
{ 
	int16_t buf[4]={0}; 
	setwheelspeed(wheelspeed,buf,1);//4个电机停止
	pantitlepwm = 0;								//舵机回到初始点							
	W_LIGHT_OFF;										//两个灯关闭
	D_LIGHT_OFF;
}
// /**
//   * 功  能：电池电压数据处理，滤波
//   * 参  数：无
//   * 返回值：无
//   * 
//   */
// uint8_t CrabApp::workmodedetect(uint8_t* recdata)
// { 
// }
/**
  * 功  能：工作模式判断
  * 参  数：无
  * 返回值：无
  * 
  */
uint8_t CrabApp::workmodedetect(uint8_t* recdata)
{
	static uint8_t index=0;
	uint8_t tempmode; 
	tempmode  	= (recdata[8]>>4)&0x03;
	if(index==0)
	{ 
		if(tempmode == 0x01)
		{
			workmode = MODE_AUTO;
			index++;
		}
	}
	else if(index==1)
	{
		if(workmode == MODE_AUTO_FINISH)
		{ 
			if(tempmode == 0x00)
			{
				workmode = MODE_MANUAL; 
				index = 0;
			}
		}
		else if((rockeyYsta==true)||(rockeyXsta==true))		//摇杆不处在中位
		{
			workmode = MODE_MANUAL; 
			index = 0;
		} 
	}  
}
/**
  * 功  能：自动转弯
  * 参  数：无
  * 返回值：无
  * 
  */
uint8_t CrabApp::autoturncontrol()
{
	uint8_t turnsta=0;
	static uint8_t initstart=0;
	static int16_t initialangle=0;
	if(turnstartflag==true)//初始启动的角度,往左转角度减小
	{
		if(initstart==0)
		{
			initialangle = robotangle; 
			initstart=1;
		}
	} 
	
	int16_t tempangle=0;
	tempangle = robotangle - initialangle;
	if(ABS(tempangle)>=180)
	{
		turnsta = 1;
	} 
	return turnsta;
}
/**
  * 功  能：自动模式
  * 参  数：无
  * 返回值：无
  * 待解决问题：
  *1:转弯时候角度换算。2:启动转弯时角度换算。3:
  */
void CrabApp::autoruncontrol()
{ 
	int16_t buf[4]={0};
	int16_t speed=0;
	static uint8_t lastinfrasta=0; 
	static uint32_t timetick=0; 
	if(workmode==MODE_AUTO)
	{	
		if(autotime==0)
			speed = -AUTO_RUN_SPEED;
		else 	if(autotime==1)
			speed = AUTO_RUN_SPEED;
		
		if(lastinfrasta == 0)						//先判断启动时的红外状态
		{
			if(infrasta==INFRA_OFF)				//在车体外面
			{ 
				lastinfrasta = 1;
			}
			else if(infrasta==INFRA_ON)		//在车体里面
			{ 
				lastinfrasta = 2;
			}  
		}
		else if(lastinfrasta==1)				//车体外面继续查看红外状态
		{
			if(infrasta==INFRA_OFF)			
			{ 
				lastinfrasta = 1;
			}
			else if(infrasta==INFRA_ON)
			{ 
				lastinfrasta = 2;
			}  
		}
		else if(lastinfrasta==2)			 
		{
      if(infrasta==INFRA_OFF)					//从车底出来了，后退沿着原路线退到初始地点
			{ 
				lastinfrasta = 3;	
			}
			else if(infrasta==INFRA_ON)			//还是在车底里面
			{ 
				lastinfrasta = 2;
			}  
		}
		else if(lastinfrasta==3)					
		{ 
			switch(autotime)
			{
				case 0:
					autotime = 1;
					lastinfrasta = 0;
				break;
				case 1:
					autotime = 0;
					lastinfrasta = 0;
					workmode = MODE_AUTO_FINISH;	  
				break;
				default:
					lastinfrasta = 0;
					workmode = MODE_MANUAL;	  
				break;
			} 
		}  
		timetick++;
		buf[0]=speed;	buf[1]=speed;	buf[2]=-speed;	buf[3]=-speed;
		setwheelspeed(wheelspeed,buf,1);
	}
	else
	{
		autotime = 0;
		lastinfrasta = 0;
		timetick = 0;
	} 
}
/**
  * 功  能：处理终端的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::disposeTerminalData()					
{
	uint8_t* temData=Terminal->getReciveData();	//获取终端反馈的数据 并暂存
	lightcontrol(temData);  										//灯控制
	workmodedetect(temData);										//工作模式的判定
	autoruncontrol();														//自动模式的控制				
	mecanumwheelcontrol(temData); 							//4个轮子速度分配
	cradlecontrol(temData);											//舵机速度
	camlencontrol(temData); 										//变焦控制
// 	fpvchannelchange(temData);								//图传通道，暂时没有，焊接隔离芯片图像会不稳定
	videochanelcontrol(temData);   							//画面切换
}
/**
  * 功  能：更新要发送到终端的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::updateSendTerminalData()
{
	uint8_t temBuf[12]={0XA5,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
	temBuf[3] = uint8_t((leftbatvoltage*10)/2);						//1unit = 0.2V
	temBuf[4] = uint8_t((rightbatvoltage*10)/2);					//1unit = 0.2V
	temBuf[5] = robotangle/2;															//1unit = 2°
	temBuf[6] = (workmode&0x03)<<6|(infrasta&0x03)<<4;		//

  Terminal->updateSendBuf(temBuf); 
}
/**
  * 功  能：发送数据到4个电机
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::sendDriverMotorData()					
{
	static uint8_t index=0;
	switch(index)
	{
		case 0:
			frontLeftMotor->setSpeed_1(-wheelspeed[LEFTUP_DDR]);
			frontLeftMotor->sendSpeedCommand(0x02);

		break;
		case 1:
			rearLeftMotor->setSpeed_1(-wheelspeed[LEFTDOWN_DDR]);
			rearLeftMotor->sendSpeedCommand(0x02);
		break;
		case 2: 
			frontRightMotor->setSpeed_1(-wheelspeed[RIGHTUP_DDR]);
			frontRightMotor->sendSpeedCommand(0x02);

		break;
		case 3:
			rearRightMotor->setSpeed_1(-wheelspeed[RIGHTDOWN_DDR]); 
			rearRightMotor->sendSpeedCommand(0x02);
		break;
		default:break; 
	}   
	index++;
	index &=0x03; 
}
/**
  * 功  能：发送行车相机数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::sendCamData()					
{
	static uint8_t count1=0,count2=0,startflag=0;
	if(count1++>=200)
	{ 
		startflag = 1; 
	}  
	if(startflag)
	{
		if(count2++>20)
		{
			count2 = 0;
			driverCam->sendZoomCommand(camlenscommand);
		} 
	}
}
/**
  * 功  能：发送四画面数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::sendVideoChangeData()					
{
	static uint8_t count=0;
	if(count++>=20)
	{
		count = 0;
		videocont->sendVideoChannel(videochannel);
	}
}
/**
  * 功  能：更新要发送到所有设备的数据
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::updateSendDriverData()					
{
	sendDriverMotorData();				//四个电机
	sendCamData();								//行车相机变焦
	sendVideoChangeData();				//四画面切换
}
/**
  * 功  能：接收控制信息，控制灯的开启关闭
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::lightcontrol(uint8_t* recdata)
{ 
	uint8_t tempdata = 0;
	uint8_t driverlightBut=0,watchlightBut=0;
	uint8_t cnt=7;
	tempdata = recdata[cnt++];
	driverlightBut = ((tempdata&0x80)>>7); 

	if(driverlightBut == 0x01)//行车灯开启
	{
		D_LIGHT_ON; 
	}
	else  
	{
		D_LIGHT_OFF; 
	}

	watchlightBut = ((tempdata&0x40)>>6); 
	if(watchlightBut == 0x01)//观测灯开启
	{
		W_LIGHT_ON; 
	}
	else  
	{
		W_LIGHT_OFF;
	} 
}

/**
  * 功  能：速度转化
  * 参  数：无
  * 返回值：无
  * 
  */
int16_t CrabApp::wheelspeedcal(int16_t speeddata,int16_t speedK)
{
	int tempdata=0; 
	
	tempdata =speeddata*30;
	tempdata =(tempdata*speedK); 
	if(tempdata>=SPEED_MAX)
		tempdata = SPEED_MAX;
	if(tempdata<=(-SPEED_MAX))
		tempdata = -SPEED_MAX;
	return (int16_t)tempdata;
}
/**
  * 功  能：4个轮子速度设定
  * 参  数：无
  * 返回值：无
  * 
  */
int16_t CrabApp::setwheelspeed(int16_t *wheelsp,int16_t *speedref,int16_t speedK)
{ 
	for(uint8_t i=0;i<4;i++)
	wheelsp[i] = wheelspeedcal(speedref[i],speedK);
}

/**
  * 功  能：麦克纳姆轮控制
  * 参  数：无
  * 返回值：无
  * 
  */


void CrabApp::mecanumwheelcontrol(uint8_t* recdata)
{   
	int16_t leftrocketAdx=0,leftrocketAdy=0,rightrocketAdx=0;
	int16_t frontLeft=0,rearLeft=0,frontRight=0,rearRight=0;
	volatile int16_t speedKK=0; 
	uint8_t cnt=3,tempdata=0;
	int16_t buf[4]={0};
  
	leftrocketAdx  	= (int16_t)recdata[cnt++]; 
	leftrocketAdy  	= (int16_t)recdata[cnt++]; 
	rightrocketAdx  = (int16_t)recdata[cnt++];  
   
	speedKK = ((recdata[7]&0x30)>>4)+1;	//4个速度档位 
	
	if(leftrocketAdx<(MOVE_MID-MOVE_DEADAREA))
	{
		leftrocketAdx = leftrocketAdx-(MOVE_MID-MOVE_DEADAREA);
		rockeyXsta = true;
	}
	else if(leftrocketAdx<(MOVE_MID+MOVE_DEADAREA))
	{
		leftrocketAdx = 0x00;
		rockeyXsta = false;
	}
	else
	{
		leftrocketAdx = leftrocketAdx-(MOVE_MID+MOVE_DEADAREA);
		rockeyXsta = true;
	}
	
	if(leftrocketAdy<(MOVE_MID-MOVE_DEADAREA))
	{
		leftrocketAdy = leftrocketAdy-(MOVE_MID-MOVE_DEADAREA);
		rockeyYsta = true;
	}
	else if(leftrocketAdy<(MOVE_MID+MOVE_DEADAREA))
	{
		leftrocketAdy = 0x00;
		rockeyYsta = false;
	}
	else
	{
		leftrocketAdy = leftrocketAdy-(MOVE_MID+MOVE_DEADAREA);
		rockeyYsta = true;
	}
	
	if(rightrocketAdx<(MOVE_MID-(MOVE_DEADAREA+5)))
		rightrocketAdx = rightrocketAdx-(MOVE_MID-(MOVE_DEADAREA+5));
	else if(rightrocketAdx<(MOVE_MID+(MOVE_DEADAREA+5)))
		rightrocketAdx = 0x00;
	else
		rightrocketAdx = rightrocketAdx-(MOVE_MID+(MOVE_DEADAREA+5));
	 
	leftrocketAdx 	+= (MOVE_DEADAREA*leftrocketAdx)/MOVE_MID;
	leftrocketAdy 	+= (MOVE_DEADAREA*leftrocketAdy)/MOVE_MID;  
	
	int16_t spkkk = 5-speedKK;
	
	frontLeft 	= -leftrocketAdy - leftrocketAdx  - rightrocketAdx/spkkk;
	rearLeft 		= -leftrocketAdy + leftrocketAdx- rightrocketAdx/spkkk;
	frontRight 	= leftrocketAdy - leftrocketAdx- rightrocketAdx/spkkk;
	rearRight 	= leftrocketAdy + leftrocketAdx - rightrocketAdx/spkkk; 
	
 	if(workmode!=MODE_AUTO) 
	{ 
		buf[0] = frontLeft;		buf[1] = rearLeft;		buf[2] = frontRight;		buf[3] = rearRight;
		setwheelspeed(wheelspeed,buf,speedKK); 
	} 
}
/**
  * 功  能：云台控制,转化为PWM
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::cradlecontrol(uint8_t* recdata)
{
	int16_t rightrocketAdy = 0; 

	rightrocketAdy  = (int16_t)(recdata[6]);  
	
	if(rightrocketAdy<MOVE_MID1)
		rightrocketAdy = rightrocketAdy-MOVE_MID1;
	else if(rightrocketAdy<MOVE_MID2)
		rightrocketAdy = 0x00;
	else
		rightrocketAdy = rightrocketAdy-MOVE_MID2; 
	
	pantitlepwm = 	rightrocketAdy;
}
/**
  * 功  能：图传通道配置
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::fpvchannelconf(uint8_t channel)
{ 
 switch(channel)
	{
		case 0:
			ACH1_OFF;ACH2_OFF;ACH3_OFF;
		break;
		case 1:
			ACH1_ON;ACH2_OFF;ACH3_OFF;
		break;
		case 2:
			ACH1_OFF;ACH2_ON;ACH3_OFF;
		break;
		case 3:
			ACH1_ON;ACH2_ON;ACH3_OFF;
		break;
		default:break;				
	}
} 
/**
  * 功  能：图传通道改变
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::fpvchannelchange(uint8_t* recdata)
{
	int16_t channel = 0;

	channel  	= recdata[8]&0x0F; 
	fpvchannelconf(channel);
}
/**
  * 功  能：数传通道改变
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::radiochannelchange(uint8_t* recdata)
{
	int16_t channel = 0;

	channel  	= recdata[8]&0x0F; 
	fpvchannelconf(channel);
}

/**
  * 功  能：相机变焦
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::camlencontrol(uint8_t* recdata)
{
	int16_t lenscom = 0;

	lenscom  	= recdata[7]&0x03;
	if(lenscom == 0x01)
		camlenscommand = CAM_TELE;
	else if(lenscom == 0x02)
		camlenscommand = CAM_WIDE;
	else  
		camlenscommand = CAM_STOP;
}
/**
  * 功  能：四画面通道切换
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::videochanelcontrol(uint8_t* recdata)
{
	int16_t channel = 0;

	channel = (recdata[7]>>2)&0x03;
 
	if(channel == 0x01)
		videochannel = VIDEO_1;//行车
	else if(channel == 0x02)
		videochannel = VIDEO_2;//观测
	else  if(channel == 0x03)
		videochannel = VIDEO_12;//2画面
} 
/**
  * 功  能：扫描红外
  * 参  数：无
  * 返回值：无
  * 
  */
void CrabApp::infrascan()
{ 
	static unsigned char SwTimerTick = 0;
	static unsigned char SwPreState= 0;		
	unsigned char SwReadState;							

	SwReadState = infra->getValue();  
	if(SwPreState != SwReadState)
	{
		if(SwTimerTick>KEYINDEX_MAX)
		{
			SwPreState = SwReadState;
			if(SwPreState == 1)
			{   
         infrasta = INFRA_OFF; 
			}
			else
			{  
         infrasta = INFRA_ON; 
			}
		}
		else
		{
			SwTimerTick++;
    }	
	}
	else
	{
    SwTimerTick=0;
  }	 
	
	if(infrasta==INFRA_OFF)
	{
		led_2->setLightOff();
	}
	else
	{
		led_2->setLightOn();
	}  
} 
/**
  * 功  能：计算本体电压
  * 参  数：无
  * 返回值：本体电压
  * 
  */
float CrabApp::subEctQuantity(float* leftbat,float* rightbat)
{
	uint8_t index=0;
	float temSubEctQuantity=0; 
	if(*leftbat>10.0)
	{
		index++;
		temSubEctQuantity+=*leftbat;
	}
	if(*rightbat>10.0)
	{
		index++;
		temSubEctQuantity+=*rightbat;
	} 
	if(index==0)
		temSubEctQuantity=0;
	else
		temSubEctQuantity/=index;
	return (float)temSubEctQuantity;
}   
/**
  * 功  能：本体电压电源指示灯
  * 参  数：无
  * 返回值：
  * 
  */
void CrabApp::powerledshow(float batvaule)
{
  static uint8_t lighttick=0;
  static uint16_t powledtick=0;
	if(batvaule<24.50)
  {  
		powledtick++;
    if(powledtick>=POW_LED_TICK2)
    {  
      if((lighttick++)%2)
      {POLED_ON;}
      else 
      {POLED_OFF;}  
      powledtick = 0;
    } 
  }  
	else	if(batvaule<26.50)
  {    
    powledtick++;
    if(powledtick>=POW_LED_TICK1)
    {  
      if((lighttick++)%2)
      {POLED_ON;}
      else 
      {POLED_OFF;}  
      powledtick = 0;
    } 
  }  
	else  if(batvaule>=26.50)
  { 
    POLED_ON;  
		powledtick = 0;
		lighttick  = 0;
  }
}


