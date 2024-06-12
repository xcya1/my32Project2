#include "EXTI.h"


//GPIOE的P4作为外部中断口，按下KEY1端口电平变低电平触发中断

void Exti_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);   //开启EXTI的外设时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;        //端口不要重复初始化，如果KEY中也初始化了,主函数中就不要初始化KEY
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOE , &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);  
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

}



//void TIM6_DAC_IRQHandler(void)
//{
//	//LED1_ON();
//	if(TIM_GetITStatus(TIM6, TIM_IT_Update))
//	{
//		 TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//		
//			flag1++;
//		if(flag1>2)
//		{
//			flag1=0;
//		}
//			
//	}


//}
