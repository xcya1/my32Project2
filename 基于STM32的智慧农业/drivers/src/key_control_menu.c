#include "key_control_menu.h"
#include "oled.h"
#include "drv_systick.h"
#include "LED.h"
#include "BEEP.h"

u8 key_control_menu(void)
{
		OLED_Clear();
	// OLED_ShowString(0,0,"111111",16,1);
		if( GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_8)==0)
		{
			OLED_ShowString(0,16,"LED1:open ",16,1);
		}
		else
		{
			OLED_ShowString(0,16,"LED1:close",16,1);
		}
		if( GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_10 )==1)
		{
			OLED_ShowString(0,16*2,"BEEP:open ",16,1);
		}
		else
		{
			OLED_ShowString(0,16*2,"BEEP:close",16,1);
		}
		OLED_Refresh();
	while(1)
	{
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
				{
					drv_systick_delayms(30); //按下按键时消抖
					if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)          //确认该按键按下
					{		
						while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0);    //按下低电平的时长，松手
					}
					static u8 num=0;
					num++;
					if(num==1)
					{
						LED1_ON();
						OLED_ShowString(0,16,"LED1:open ",16,1);
					}
					else
					{
						num=0;
						LED1_OFF();
						OLED_ShowString(0,16,"LED1:close",16,1);
					}
				}	
				if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)
				{
					drv_systick_delayms(30); //按下按键时消抖
					if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)          //确认该按键按下
					{	
						while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0);    //按下低电平的时长，松手
					}		
					static u8 num=0;
					num++;
					if(num==1)
					{
						BEEP_ON();
						OLED_ShowString(0,16*2,"BEEP:open ",16,1);
					}
					else
					{
						num=0;
						BEEP_OFF();
						OLED_ShowString(0,16*2,"BEEP:close",16,1);
					}
				}	
				
			OLED_Refresh();
				
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)      //key4 返回上一级
			{
				drv_systick_delayms(30); //按下按键时消抖
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)          //确认该按键按下
				{
					while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0);    //按下低电平的时长，松手
				}
				OLED_Clear();
				return 0;
			}
	}
	
	
	


}