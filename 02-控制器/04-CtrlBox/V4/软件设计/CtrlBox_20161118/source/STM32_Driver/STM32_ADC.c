/***********************************************************************************************
*文件名		：	STM32_ADC.c
*描述		：	ADC1初始化，均值滤波
*作者		：	不详
*创建日期	：	不详
*修改日期	：	20160104
*修改人 		：	孟浩
*修改原因	：	整理代码，添加注释
*版本 		：	2.0
*历史版本	：	不详
*函数1		：	ADC1_DMA_Init					//	ADC1 初始化(DMA传输)，只需外部调用1次
*函数2		：	ADC1_GPIO_Config				//	静态函数，ADC1 GPIO初始化，根据硬件适当修改
*函数3		：	ADC1_Config						//	静态函数，ADC1 配置，根据硬件适当修改
*函数4		：	ADC1_DMA_Config					//	静态函数，ADC1 DMA初始化，无需修改
*函数5		：	ADC_MeanFilter					//	静态函数，ADC1 均值滤波，无需修改
*函数6		：	DMA1_Channel1_IRQHandler		//	DMA1 Channel1中断函数，无需修改
***********************************************************************************************/

#include "STM32_ADC.h" 

#define ADC1_DR_Address	((uint32_t)0x4001244C)	//	ADC1数据寄存器地址


uint16_t AD_Filter[ADC_CHANNEL_N];   			//	AD滤波后各通道存放数据
uint16_t AD_Cache[ADC_CACHEL_M][ADC_CHANNEL_N];	//	全部AD各通道缓存采样值

// 以下4个函数仅在本文件内调用
static  void 	ADC1_GPIO_Config(void);			//	ADC1 GPIO配置   
static  void 	ADC1_Config(void);				//	ADC1 配置
static  void 	ADC1_DMA_Config(void);			//	ADC1 DMA配置
static	void 	ADC_MeanFilter(void);			//	ADC  均值滤波

/**
*	@函数说明：	ADC1初始化(DMA传输)
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
void 	ADC1_DMA_Init(void)
{
	ADC1_GPIO_Config(); 						//	GPIO配置
	ADC1_DMA_Config();  						//	ADC1-DMA配置
	ADC1_Config();  							//	ADC1配置
	ADC_Cmd(ADC1, ENABLE); 						//	使能ADC1(使能后，开启转换还需要开启软件触发)
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 				//	ADC软件触发启动  
}

/**
*	@函数说明：	ADC1 GPIO配置(模拟输入)，根据硬件适当修改
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
static	void	ADC1_GPIO_Config(void)
{
	STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	配置AD_PowKey通道
	STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	配置AD_Pow通道
	
	STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOB);	//	配置AD1通道
	STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOB);	//	配置AD2通道
	STM32_GpioOneInit(GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	配置AD3通道
	STM32_GpioOneInit(GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	配置AD4通道

}

/**
*	@函数说明：	ADC1配置DMA，修改通道时，不需要修改此函数
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
static	void	ADC1_DMA_Config(void)   
{   
    DMA_InitTypeDef DMA_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
     
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);      //	开启 DMA 时钟
    DMA_DeInit(DMA1_Channel1);
		
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Cache;   
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   

    //	如此设置，使序列1结果放在AD_Cache[0]，序列2结果放在AD_Cache[1]    
    DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_N*ADC_CACHEL_M;   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;   
    //	循环模式开启，Buffer写满后，自动回到初始地址开始传输    
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;   
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);   
    
	//	DMA 中断配置
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); //	使能DMA传输完成中断   
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);          //	使能DMA中断 
	
	//	配置完成后，启动DMA通道    
    DMA_Cmd(DMA1_Channel1, ENABLE);
} 

/**
*	@函数说明：	ADC1配置(时钟不能超过14MHz)，根据硬件适当修改
*				修改通道时，需要添加并修改ADC_RegularChannelConfig函数
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
static	void	ADC1_Config(void)   
{   
    ADC_InitTypeDef ADC_InitStructure;   
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);						//	ADCCLK = PCLK2/4 = 9MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//	开启 ADC1 时钟
	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 		//	转换模式为独立模式 
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   			//	使用多通道时需要开启
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  	//	连续转换开启    
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//	没有外部触发 
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//	数据右对齐 
    ADC_InitStructure.ADC_NbrOfChannel = ADC_CHANNEL_N;     //	通道数    
    ADC_Init(ADC1, &ADC_InitStructure);   					//	写入寄存器
       
    ADC_TempSensorVrefintCmd(DISABLE);    					//	使用片内温度传感器时才需开启   
     
	//	输入参数：ADC1，通道(ADC_Channel_0~ADC_Channel_17)，转换顺序(1~16)，采样时间  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 6, ADC_SampleTime_55Cycles5);

   
    ADC_DMACmd(ADC1, ENABLE);								//	开启ADC的DMA支持(要实现DMA，还需单独配置DMA通道等参数)    
	ADC_Cmd(ADC1, ENABLE);      							//	使能ADC1   
	
    ADC_ResetCalibration(ADC1);								//	ADC自动校准，开机后需执行一次，保证精度 
    while(ADC_GetResetCalibrationStatus(ADC1));    
    ADC_StartCalibration(ADC1);    
    while(ADC_GetCalibrationStatus(ADC1)){};  				//	ADC自动校准结束   
	
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 				//	ADC软件触发启动    
}  

/**
*	@函数说明：	ADC均值滤波，修改通道时，不需要修改此函数
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
static	void	ADC_MeanFilter(void)
{
	int32_t sum = 0;
	uint8_t channelNum,cacheNum;
	for(channelNum=0; channelNum<ADC_CHANNEL_N; channelNum++)
	{
		for ( cacheNum=0;cacheNum<ADC_CACHEL_M;cacheNum++)
		{
			sum += AD_Cache[cacheNum][channelNum];
		}
		AD_Filter[channelNum]=sum/ADC_CACHEL_M;
		sum=0;
	} 
}

/**
*	@函数说明：	DMA1通道1中断处理函数，均值滤波，修改通道时，不需要修改此函数
*	@参数：		无
*	@返回值： 	无
*	@备注： 		无
*/
void	DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{ 
		ADC_MeanFilter(); 
		DMA_ClearITPendingBit(DMA1_IT_TC1); //清除全部中断标志    
    }
}

 








