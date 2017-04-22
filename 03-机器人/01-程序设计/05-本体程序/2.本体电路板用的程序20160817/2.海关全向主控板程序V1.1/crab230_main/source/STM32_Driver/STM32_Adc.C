#include "STM32_Adc.h"


int16_t AD_Value[STM32_ADC_CHANNEL_N*STM32_ADC_CACHEL_M][STM32_ADC_CHANNEL_N];   //AD???
int16_t After_filter[STM32_ADC_CHANNEL_N];   //AD??? 

void Adc1DmaChannelConfig(void)
{ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles);  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_480Cycles);  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_480Cycles);  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 4, ADC_SampleTime_480Cycles);  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_480Cycles);  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 6, ADC_SampleTime_480Cycles);  
	
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);  //if not have this function , can't get new value 
	  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);  //make enable ADC1 WITH DMA2 
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

}
void Adc1DmaStrinit(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
  /* ADC1 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;          //if used multi channels set enable
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;  //software trig,need function to start:ADC_SoftwareStartConv(ADC3); others: extern trig or timer trig
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;             //right align
  ADC_InitStructure.ADC_NbrOfConversion = STM32_ADC_CHANNEL_N;   //when have 7 channels analoy need to conv,set =7
  ADC_Init(ADC1, &ADC_InitStructure); 
}
void Adc1DmaCominit(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;   //if doubul ADC channels need to  synchronous, set dependent.
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles; //ADC_delay_between_2_sampling_phases 
  ADC_CommonInit(&ADC_CommonInitStructure);
}
void Adc1DmaGpioConfig(void)
{ 
  GPIO_InitTypeDef      GPIO_InitStructure;
		// config GPIO
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
}
void Adc1DmaConfig(void)
{
  DMA_InitTypeDef       DMA_InitStructure;
	
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(ADC1_DR_Address);  //ADC1 DATA ADDRESS ADC1->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&AD_Value;    			 //DMA memory base address
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = STM32_ADC_CHANNEL_N*STM32_ADC_CACHEL_M;														 //设置BUFF长度
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //periphera inc mode: when have multi peripheras need to use DMA
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //need  continue visit
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
}
void Adc1DmaInit(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA, ENABLE);  //DMA2,GPIO use AHB1 BUS 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);                         //ADC use APB2 BUS
	Adc1DmaConfig();
	Adc1DmaGpioConfig();
	Adc1DmaCominit();
	Adc1DmaStrinit();
	Adc1DmaChannelConfig(); 
	StartAdcConvert();
}
void StartAdcConvert(void)
{
	ADC_SoftwareStartConv(ADC1);
}
//????:(????) 
void FilteAdcVaule(void)
{
   int32_t sum = 0;
   uint8_t count,i;
   for(i=0;i<STM32_ADC_CHANNEL_N;i++)
   {
      for ( count=0;count<STM32_ADC_CACHEL_M;count++)
      {
         sum += AD_Value[count][i];
      }
      After_filter[i]=sum/STM32_ADC_CACHEL_M;
      sum=0;
   } 
}
  
int16_t getbatvolt(uint8_t channel)
{
	float batvolt=0;
	FilteAdcVaule();
	batvolt = (float)After_filter[channel];  
	batvolt = ((V_REG / 4095.0) * (float)batvolt * ((VIN_R1 + VIN_R2) / VIN_R2));
	batvolt /=0.2;
  return (int16_t)(batvolt+0.8);//0.6V 是补偿
}
