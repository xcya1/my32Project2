#include "stm32f4XX.h"
#include "LED.h"
#include "BEEP.h"
#include "drv_systick.h"
#include "KEY.h"
#include "USART1.h"
#include "string.h"
#include "EXTI.h"
#include "TIM.h"
#include "oled.h"
#include "bmp.h"
#include "DMA.h"

u32 buf1[10]={0x11,0x12,0x13};
u32 buf2[10]={0};

u8 key_ret;

u8 j=0;


int main(void)
{
	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	drv_systick_init(168);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	USART_1_Init();
	DMA2_Init(1,buf1,buf2);
//	TIM6_Init();  
	
	OLED_Init();
	
	
	while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==0);
	buf_cmp();
	
	while(1)
	{
				

	}
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

	
	
	



