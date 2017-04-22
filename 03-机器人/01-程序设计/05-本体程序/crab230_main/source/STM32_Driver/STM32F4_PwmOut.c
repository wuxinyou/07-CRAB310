#include "STM32F4_PwmOut.h" 
 
///////////////////////////////Timer4初始化为PWM输出部分开始//////////////////////////////////////////////////////
void STM32_Timer8PwmOcInit(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;  
	TIM_OCInitStructure.TIM_OCMode 	=  TIM_OCMode_PWM1;  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
 	TIM_OC2Init(TIM8, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
 	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM8, ENABLE); 
}
void STM32_Timer8InitAsPwm(void)
{ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	STM32_GpioOneInit(GPIO_Pin_6|GPIO_Pin_7, GPIO_Speed_100MHz, 
					GPIO_Mode_AF, GPIO_OType_PP,GPIO_PuPd_UP,GPIOC);
	
	STM32_TimerBaseInit(TIM8, TIMER8_PWM_FREQ-1, TIMER8_PWM_PRECALER, 
					TIM_CKD_DIV1,TIM_CounterMode_Up, 0x00);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8); 	 
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8); 	
	
	STM32_Timer8PwmOcInit(); 	
	TIM_Cmd(TIM8, ENABLE);  
	TIM_CtrlPWMOutputs(TIM8, ENABLE);  	
}
void STM32_SetPwmVal(int16_t PwmVal)
{ 	
	int16_t duty = 0;
	if(PwmVal>TIMER8_PWM_FREQ||PwmVal<-TIMER8_PWM_FREQ)
		return; 
// 	if (PwmVal>0) {
// 		// +
// 		TIM_SelectOCxM(TIM8, TIM_Channel_1, TIM_OCMode_PWM1);
// 		TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Enable); 

// 		// -
// 		TIM_SelectOCxM(TIM8, TIM_Channel_2, TIM_OCMode_Inactive);
// 		TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCx_Enable); 
// 	} else {
// 		// +
// 		TIM_SelectOCxM(TIM8, TIM_Channel_2, TIM_OCMode_PWM1);
// 		TIM_CCxCmd(TIM8, TIM_Channel_2, TIM_CCx_Enable); 

// 		// -
// 		TIM_SelectOCxM(TIM8, TIM_Channel_1, TIM_OCMode_Inactive);
// 		TIM_CCxCmd(TIM8, TIM_Channel_1, TIM_CCx_Enable); 
// 	}
// 	TIM8->CCR1 = PwmVal;
// 	TIM8->CCR2 = PwmVal;

	duty = (TIMER8_PWM_FREQ + PwmVal) >> 1; 
	TIM8->CCR1 = duty;
	TIM8->CCR2 = TIMER8_PWM_FREQ - duty;
}
///////////////////////////////Timer9初始化为PWM输出部分开始//////////////////////////////////////////////////////
void STM32_Timer9PwmOcInit(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;  
	TIM_OCInitStructure.TIM_OCMode 	=  TIM_OCMode_PWM1;  
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_High; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	
	TIM_OC1Init(TIM9, &TIM_OCInitStructure); 
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM9, ENABLE); 
}
void STM32_Timer9InitAsPwm(void)
{ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	
	STM32_GpioOneInit(GPIO_Pin_5, GPIO_Speed_100MHz, 
					GPIO_Mode_AF, GPIO_OType_PP,GPIO_PuPd_UP,GPIOE);
	
	STM32_TimerBaseInit(TIM9, TIMER9_PWM_FREQ-1, TIMER9_PWM_PRECALER, 
					TIM_CKD_DIV1,TIM_CounterMode_Up, 0x00);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9); 	 	
	
	STM32_Timer9PwmOcInit(); 	
	TIM_Cmd(TIM9, ENABLE);  
	TIM_CtrlPWMOutputs(TIM9, ENABLE);  	
}
void STM32_PPMOutSetPPMVal(uint8_t Channel,int16_t PwmVal)
{
	PwmVal = Constrain(PwmVal, PPMOUT_MINVALUE, PPMOUT_MAXVALUE);		//输出范围限制
 
	switch(Channel)
	{
		case PPMOUT_CHANNEL_1:
			 TIM9->CCR1 = TIMER9_PWM_FREQ-PwmVal;break;
		case PPMOUT_CHANNEL_2:
			 TIM9->CCR2 = PwmVal;break;
		case PPMOUT_CHANNEL_3:
			 TIM9->CCR3 = PwmVal;break;
		case PPMOUT_CHANNEL_4:
			 TIM9->CCR4 = PwmVal;break;
		default:break; 
	}	 
}

void ServoControl(int16_t servosp)
{
	static int16_t servovaule=PPMOUT_MAXVALUE; 
	float step=0;  
	
	step = servosp/50;
	servovaule += step; 
	if(servovaule>=PPMOUT_MAXVALUE)
		servovaule = PPMOUT_MAXVALUE;
	else if(servovaule<=PPMOUT_MINVALUE)
		servovaule = PPMOUT_MINVALUE;
	
	STM32_PPMOutSetPPMVal(PPMOUT_CHANNEL_1,servovaule); 
}
 
/////////////////////////////////////Timer9初始化为PWM输出部分结束////////////////////////////////////////////////
