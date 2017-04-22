/**
  ******************************************************************************
	*文件：WatchDag.c
	*作者：叶依顺
	*版本：2.0
	*日期：2013-06-17
	*概要：独立看门狗类的实现
	*备注：
	*
  ******************************************************************************  
	*/ 
	
#include "WatchDag.h"
WatchDag::WatchDag()
{
// 	/*使能对寄存器IWDG_PR和IWDG_RLR的写操作*/
// 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
// 	/*设置IWDG时钟为LSI经32分频，则IWDG计数器时钟=32KHz(LSI)/32=1kHz*/
// 	IWDG_SetPrescaler(IWDG_Prescaler_32);
// 	IWDG_SetReload(1000);								//设置IWDG计数值为349
// 	IWDG_ReloadCounter();								//重载IWDG计数值
// 	IWDG_Enable();											//启动IWDG
}
WatchDag::~WatchDag()
{

}

void WatchDag::init()
{
	/*使能对寄存器IWDG_PR和IWDG_RLR的写操作*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/*设置IWDG时钟为LSI经32分频，则IWDG计数器时钟=32KHz(LSI)/32=1kHz*/
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(2000);								//设置IWDG计数值为2秒
	IWDG_ReloadCounter();								//重载IWDG计数值
	IWDG_Enable();											//启动IWDG
}
void WatchDag::feedDog()							//重新设置IWDG
{
	IWDG_ReloadCounter();								//重载IWDG计数值
}
bool WatchDag::getStatus()
{
	return RCC_GetFlagStatus(RCC_FLAG_IWDGRST);
}














































