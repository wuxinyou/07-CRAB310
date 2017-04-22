/**
  ******************************************************************************
	*文件：main.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：主程序的入口
	*备注：
	*
  ******************************************************************************  
	*/ 
	
/* 宏定义-----------------------------------------------------------------------*/ 	

//看门狗只复位一次
// #define RESET_ONE



#ifdef __cplusplus  
       extern "C" {  
#endif  
	#include "stm32f4xx.h"  
	#include "system_stm32f4xx.h"

	#include "STM32F4_PriorityControl.h"
	#include <stdlib.h>
	#include <rt_heap.h>  //_init_alloc
	#include "CrabApp.h"
	#include "WatchDag.h"
	#include "STM32F4_SysTick.h"
	#include "LEDLighter.h" 
#ifdef __cplusplus  

//  #define HEAP_SIZE   (0x3000)              //堆内存池的长度3000*4=16K STM32的RAM总大小是32K
//  int32_t  heap_zone[HEAP_SIZE] = {0};       //堆内存数据全初始化为0
        }  
#endif 	
#define CLI()     __set_PRIMASK(1) //关闭总中断
#define SEI()     __set_PRIMASK(0) //打开总中断
				
CrabApp *myApp;
// WatchDag *myDag;
				
int main(void)
{ 
	//_init_alloc((int32_t)heap_zone, (int32_t)&heap_zone[HEAP_SIZE-1]); //初始化堆的起止地址，共分配16K的空间
	CLI();//关闭总中断
	setSystemPriorityGroup();		//系统中断优先级分组设置
	SysTick_DelayMs(5000);				//延时2秒，等待设备启动 
	SysTick_DelayMs(5000);				//延时2秒，等待设备启动 
// 	STM32_GpioInit();						//GPIO初始化
// 	LIGHT_OFF;									//前向照明灯关闭
// 	POW_ON;											//电源开启
	myApp=new CrabApp(); 				//初始化用户应用类
	SEI();											//打开总中断

 	myApp->openUserInterrupt();	//打开用户中断
// #ifdef RESET_ONE	
// 	if(WatchDag::getStatus()!=RESET)
// 	{
// 		WatchDag::clearFlag();
// 	}
// 	else
// 	{
// 		WatchDag::init();
// 	}	
// #else	
	//myApp->GPSPort->writeLine("Watch dog has run!\r\n");//测试看门狗
// 	WatchDag::init();
// #endif
	while(1)
	{  
	}
}

