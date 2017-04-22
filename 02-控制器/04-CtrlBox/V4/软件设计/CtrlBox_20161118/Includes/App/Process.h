/**
  ******************************************************************************
	*文件：Process.h
	*作者：孟浩
	*版本：2.0
	*日期：
	*概要：
	*备注：
	*
  ******************************************************************************  
	*/ 
	
/* 定义防止递归包含的控制宏----------------------------------------------------*/
#ifndef _PROCESS_H
	#define _PROCESS_H

	/* 头文件包含 ------------------------------------------------------------------*/
	#include "DataTypeConvertion.h"
	#include "stm32f10x.h"
	#include "Protocol.h"
	#include "SerialPort.h"
	#include "Timer.h"
	#include "IoOut.h"
	#include "Key.h"
	#include "STM32_SysTick.h"
	#include "STM32_ADC.h" 
	#include "stdint.h"
	
	
/* 引脚定义--------------------------------------------------------------------*/
#define	USE_PERIPH
#ifdef	USE_PERIPH
//<引脚端口定义>
	#define	TESTLED_PORT			  GPIOA
	#define	TESTLED_PIN				GPIO_Pin_6
	//<放大，缩小，加速，减速 引脚定义>
	#define KEY1_PORT           GPIOA
	#define KEY1_PIN            GPIO_Pin_10
	#define KEY2_PORT           GPIOA
	#define KEY2_PIN            GPIO_Pin_9
	#define KEY3_PORT           GPIOB
	#define KEY3_PIN            GPIO_Pin_15
	#define KEY4_PORT           GPIOA
	#define KEY4_PIN            GPIO_Pin_8
	//</放大，缩小，加速，减速 引脚定义>
	//<车灯，观测灯，自动模式，画面切换 引脚定义>
	#define KEY5_PORT           GPIOB
	#define KEY5_PIN            GPIO_Pin_5
	#define KEY6_PORT           GPIOB
	#define KEY6_PIN            GPIO_Pin_4
	#define KEY7_PORT           GPIOB
	#define KEY7_PIN            GPIO_Pin_3
	#define KEY8_PORT           GPIOA
	#define KEY8_PIN            GPIO_Pin_15
	//</车灯，观测灯，自动模式，画面切换 引脚定义>
	//<电源指示灯 引脚定义>
	#define POWLED1_PORT           GPIOB
	#define POWLED1_PIN            GPIO_Pin_14
	#define POWLED2_PORT           GPIOB
	#define POWLED2_PIN            GPIO_Pin_13
	#define POWLED3_PORT           GPIOB
	#define POWLED3_PIN            GPIO_Pin_12
	#define POWLED4_PORT           GPIOB
	#define POWLED4_PIN            GPIO_Pin_2	
	//</电源指示灯 引脚定义>
	//<控制 引脚定义>
	#define PADDET_PORT           GPIOA
	#define PADDET_PIN            GPIO_Pin_12
	#define CTRLBTPOW_PORT           GPIOA
	#define CTRLBTPOW_PIN            GPIO_Pin_11
	#define CTRLVIDEOPOW_PORT           GPIOB
	#define CTRLVIDEOPOW_PIN            GPIO_Pin_6
	#define CTRLPOW_PORT           GPIOB
	#define CTRLPOW_PIN            GPIO_Pin_7
	
	//</控制 引脚定义>
	
	
	/*
	#define	POWER_LED1R_PORT		GPIOA
	#define	POWER_LED1R_PIN			GPIO_Pin_15
	#define	POWER_LED1B_PORT		GPIOB
	#define	POWER_LED1B_PIN			GPIO_Pin_3
	#define	POWER_LED2R_PORT		GPIOB
	#define	POWER_LED2R_PIN			GPIO_Pin_4
	#define	POWER_LED2B_PORT		GPIOB
	#define	POWER_LED2B_PIN			GPIO_Pin_5
	#define	POWER_LED3R_PORT		GPIOB
	#define	POWER_LED3R_PIN			GPIO_Pin_6
	#define	POWER_LED3B_PORT		GPIOB
	#define	POWER_LED3B_PIN			GPIO_Pin_7
	#define	POWER_LED4R_PORT		GPIOB
	#define	POWER_LED4R_PIN			GPIO_Pin_8
	#define	POWER_LED4B_PORT		GPIOB
	#define	POWER_LED4B_PIN			GPIO_Pin_9
	#define	POWER_CTR_PORT			GPIOB
	#define	POWER_CTR_PIN			GPIO_Pin_1
	#define	DIG_SET_PORT			GPIOB
	#define	DIG_SET_PIN				GPIO_Pin_12
	#define	VEDIO_CH1_PORT			GPIOB
	#define	VEDIO_CH1_PIN			GPIO_Pin_13
	#define	VEDIO_CH2_PORT			GPIOB
	#define	VEDIO_CH2_PIN			GPIO_Pin_14
	#define	VEDIO_CH3_PORT			GPIOB
	#define	VEDIO_CH3_PIN			GPIO_Pin_15
	#define	BT_SET_PORT				GPIOA
	#define	BT_SET_PIN				GPIO_Pin_12
	#define	VBT_CTR_PORT			GPIOB
	#define	VBT_CTR_PIN				GPIO_Pin_2
	
	*/
	
//</引脚端口定义>
	
//<AD 相关定义>
	/* AD顺序定义--------------------------------------------------------------------*/
	#define	NUM_KEY_POWER			0										//	电源关机按键
	#define	NUM_POWER			   	1										//	电源电压
	
	#define NUM_ctrLeftX			3										//  全向左右运动控制
	#define NUM_ctrLeftY			2										//	全向前后运动控制
	
	#define	NUM_ctrRightY			5										//	云台控制
	#define NUM_ctrRightX			4										//	原地左右旋转




	
	#define	LEFT1	0
	#define	LEFT2	1
	#define	LEFT3	2
	#define	LEFT4	3
	#define	RIGHT1	0
	#define	RIGHT2	1
	#define	RIGHT3	2
	#define	RIGHT4	3
	//</AD 相关定义>

#endif
	
	#define	TIM2_DELAY_TIME		10
	#define	TIM3_DELAY_TIME		50
	#define	TIM4_DELAY_TIME		50
	
	#define LEFT_KEY_NUM		4
	#define RIGHT_KEY_NUM	4
	/* 类的声明 --------------------------------------------------------------------*/
	class Process
	{
		public:
						Process();
						~Process();
			void 		runOnTime2(void);							//	运行在定时器TIM2中的函数
			void 		runOnTime3(void);							//	运行在定时器TIM3中的函数
			void 		runOnTime4(void);							//	运行在定时器TIM4中的函数
			void 		openPeriph(void);							//	打开用外设		
		
		private:
			uint8_t		ctrBatVal;									//	从主控板获得控制器电池电量，发送给pad
			uint8_t		ctrData1, ctrStatus1, ctrStatus2;			//	从主控板获得控制数据，发送给pad
			uint8_t		ctrBotData1, ctrBotData2;					//	从主控板获得控制数据，发送给本体
			uint8_t		ctrLeftX, ctrLeftY, ctrRightX, ctrRightY;	//	从主控板获得摇杆数据,发送给本体			
			uint8_t		ctrChannel;									//	从本体获得数据，更新控制器通道后返回给pad

			bool		padOffState;								//	从pad获得数据，pad关机状态
			uint8_t		padChannel;									//	从pad获得数据，通道号
			
			uint8_t		botLeftBatVal, botRightBatVal;				//	从本体获得数据，本体电池电量
			uint8_t		botAngle;									//	从本体获得数据，本体角度
			uint8_t		botMode;									//	从本体获得数据，本体模式
			uint8_t		botIR;										//	从本体获得数据，本体红外
			uint8_t		botChannel;									//	从本体获得数据，本体通道号
		
			SerialPort 	*comToPad,*comToRobot;             //
			Protocol 	*protocol;
			Timer		*t2,*t3,*t4;								//	定时器2,定时器3,定时器4			
			IoOut 		*testLed;									//	测试指示灯		
/*		
			IoOut		*powerLed1R, *powerLed1B;					//	电源指示灯1
			IoOut		*powerLed2R, *powerLed2B;					//	电源指示灯2
			IoOut		*powerLed3R, *powerLed3B;					//	电源指示灯3
			IoOut		*powerLed4R, *powerLed4B;					//	电源指示灯4
			IoOut		*powerCtr;									//	电源控制	
			IoOut		*vbtCtr;									//	视频采集卡、蓝牙电源控制
			IoOut		*digSet;									//	数传配置引脚
			IoOut		*vedioCh1, *vedioCh2, *vedioCh3;			//	图传配置引脚
			IoOut		*BtSet;										//	蓝牙控制引脚
			IoOut		*spareIo1, *spareIo2;						//	预留引脚		
		*/
			// Key			*keys[NUM_KEY];							//	按键	
			//<8个按键实例声明>
			Key     *zoomInKey,*zoomOutKey;
			Key     *speedUpKey,*speedDownKey;
			Key     *vehicleLedKey,*observeLedKey;
			Key     *autoModeKey,*pictureSwitchKey;
			//<Pad检测实例声明>
			Key     *padDetector;
			//3个电源控制IO
			IoOut   *blueToothPowCtrl;
			IoOut   *videoCardPowCtrl;
			IoOut   *systemPowCtrl;
			//4个电源指示灯IO
			IoOut   *powerLed1,*powerLed2,*powerLed3,*powerLed4;
			
	
			bool		ctrFlag_Auto;								//	自动模式
			bool		ctrFlag_InterruptAuto;						//	自动模式被打断
			bool		ctrFlag_WorkAuto;							//	自动模式完成标志
			bool		ctrFlag_PowerOn;							//	上电准备好
			bool		ctrFlag_PowerLedOff;						//	电源指示灯灭灯
			bool		ctrFlag_PadInsert;							//	Pad插入标志
			/*
			bool		leftAdKey[LEFT_AD_KEY_NUM];					//	左侧AD按键数值
			bool		rightAdKey[RIGHT_AD_KEY_NUM];				//	右侧AD按键数值
			*/
			uint8_t		count_PowerOff;								//	关机倒计时					
			uint8_t		com1st_DataToSend[COMN1_SEND_DATA_LENGTH];	//	com1st需要发送的数据
			uint8_t		com2nd_DataToSend[COMN2_SEND_DATA_LENGTH];	//	com2nd需要发送的数据		
			

			void	    initAllData(void);							//	全部数据初始化，包括标志位
			void			initGPIO(void);							  	//	初始化IO
			void	    initADs(void);								//	初始化AD通道
			void	    initUsarts(void);							//	初始化串口
			void	    initTimers(void);							//	初始化定时器		
			
			void	  getKeyValue(void);							//	获取按键值
// 			void		getAdKeyValue(void);						//	获取AD按键值
			void		getBatValue(void);							//	获取电压值
			void		getJoyStickValue(void);						//	获取摇杆数据	
			
			void    detectPad();                    //检测Pad
			void    detectPowerSwitch();            //检测电源开关
			
			void		dealPadData(void);							//	处理主控数据
			void		dealBotData(void);							//	处理本体数据
			void		dealKeyValue(void);							//	处理按键控制数据
			void		setPowerLed(void);							//	设置电源指示灯
			void		setPowerState(bool);						//	设置电源状态
			
// 			void		setChannel(uint8_t);						//	设置通道
// 			void		setVedioCh(uint8_t);						//	设置图传通道
// 			void		setDataCh(uint8_t);							//	设置数传通道			

			void		setComToPadData(void);						  	//	设置Com1需要发送的数据
			void		setComToRobotData(void);							//	设置Com2需要发送的数据
			
			void		enable_SWD_disable_Jtag(void);				//	使能SWD，关闭JTAG
			void		testWithUsart(void);						//	通过串口测试数据
	};
	
#endif 
/*--------------------------------- End of Process.h -----------------------------*/
