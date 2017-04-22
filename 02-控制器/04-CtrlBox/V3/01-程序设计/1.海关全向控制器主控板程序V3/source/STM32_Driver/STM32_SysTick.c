/***********************************************************************************************
*文件名		：	STM32_SysTick.c
*描述		：	SysTick初始化(查询延时)
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
*函数1		：	SysTick_Init					//	SysTick 初始化，只需外部调用1次
*函数2		：	SysTick_DelayUs					//	SysTick us延时 <=798915
*函数3		：	SysTick_DelayXms				//	SysTick ms延时 <=1864，只被SysTick_DelayMs调用
*函数4		：	SysTick_DelayMs					//	SysTick ms延时 <=2^32-1
***********************************************************************************************/

#include "STM32_SysTick.h"

static uint8_t  fac_us=0;						//	us延时倍乘数			   
static uint16_t fac_ms=0;						//	ms延时倍乘数
static void SysTick_DelayXms(uint16_t xms);		//	ms延时函数，只被SysTick_DelayMs调用

/**
*	@函数说明：	SysTick初始化
*	@参数：		无
*	@返回值： 	无
*	@备注： 			
*/
void SysTick_Init(void)   
{ 
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//	SYSTICK的时钟固定为AHB时钟的1/8
	fac_us=SystemCoreClock/8000000;				//	每个us需要的systick时钟数  
	fac_ms=(uint16_t)fac_us*1000;				//	每个ms需要的systick时钟数   
} 

/**
*	@函数说明：	us延时
*	@参数：		nus，要延时的us数，不要大于798915(最大值即2^24/fac_us@fac_us=21)
*	@返回值： 	无
*	@备注： 		无		
*/
void SysTick_DelayUs(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//	时间加载	  		 
	SysTick->VAL=0x00;        					//	清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//	开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//	等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//	关闭计数器
	SysTick->VAL =0X00;      					//	清空计数器	 
}

/**
*	@函数说明：	ms延时，只被SysTick_DelayMs调用
*	@参数：		xms，要延时的ms数，不要大于1864，只被SysTick_DelayMs调用
*	@返回值： 	无
*	@备注：		无 			
*/
static	void SysTick_DelayXms(uint16_t xms)
{	 		  	  
	uint32_t temp;

	SysTick->LOAD=(uint32_t)xms*fac_ms;			//	时间加载(LOAD为24bit)
	SysTick->VAL =0x00;							//	清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//	开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//	等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//	关闭计数器
	SysTick->VAL =0X00;       					//	清空计数器	  	    
} 

/**
*	@函数说明：	ms延时，只被SysTick_DelayMs调用
*	@参数：		nms，要延时的ms数，不要大于2^32-1
*	@返回值： 	无
*	@备注： 		无		
*/
#define	DELAY_SCALE	1000						//	DELAY_SCALE不能超过1864
void SysTick_DelayMs(uint32_t nms)
{	
	uint32_t repeat=nms/DELAY_SCALE;															
	uint16_t remain=nms%DELAY_SCALE;
    
	while(repeat)
	{
		SysTick_DelayXms(DELAY_SCALE);
		repeat--;
	}

    if (remain)
    {
        SysTick_DelayXms(remain);
    }       
}

