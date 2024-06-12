
#include "pwm_control_menu.h"
#include "oled.h"
#include "drv_systick.h"
#include "ADC.h"
#include "TIM.h"
#include "drv_dht11.h"
#include "LED.h"


u8 temp,humi;
u16 Light_Val;


u8 pwm_control_menu(void)
{

	
	
	 //关照值越亮越小，越暗值越大
		OLED_ShowChinese(0,0,2,16,1);    //光
		OLED_ShowChinese(16,0,3,16,1);   //照
		OLED_ShowChinese(16*2,0,4,16,1);  //强
		OLED_ShowChinese(16*3,0,7,16,1);  //度 
		OLED_ShowChar(16*4,0,':',16,1);
		
	  OLED_ShowChinese(0,16,0,16,1);    //当
	  OLED_ShowChinese(16,16,1,16,1);  //前
		OLED_ShowChinese(16*2,16,2,16,1); //光 
		OLED_ShowChinese(16*3,16,3,16,1); //照
		OLED_ShowChar(16*4,16,':',16,1); 
	   
	

		OLED_ShowChinese(0,16*2,0,16,1);  //当
	  OLED_ShowChinese(16,16*2,1,16,1);  //前
		OLED_ShowChinese(16*2,16*2,8,16,1);  //温
	  OLED_ShowChinese(16*3,16*2,7,16,1);  //度
		OLED_ShowChar(16*4,16*2,':',16,1);
		OLED_ShowChar(16*6,16*2,'C',16,1); 

			OLED_ShowChinese(0,16*3,0,16,1);  //当
			OLED_ShowChinese(16,16*3,1,16,1);  //前
			OLED_ShowChinese(16*2,16*3,9,16,1);  //湿
			OLED_ShowChinese(16*3,16*3,7,16,1);  //度  
			OLED_ShowChar(16*4,16*3,':',16,1);
	
			OLED_ShowChar(16*6,16*3,'%',16,1); 
	
	while(1)
	{
		Light_Val=drv_adc_res_value();
		drv_systick_delayms(100);
		DHT11_Read_Data(&temp,&humi);
		
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)      //key4 返回上一级
			{
				drv_systick_delayms(30); //按下按键时消抖
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)          //确认该按键按下
				{
					while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0);    //按下低电平的时长，松手
				}
				OLED_Clear();
				TIM_SetCompare1(TIM1,0);
				return 0;
			}
				
		
		if(Light_Val<2000 && Light_Val>1000)
		{
			TIM_SetCompare1(TIM1,210);
			OLED_ShowChinese(16*5,0,5,16,1);  //光亮度为中，LED中等
		}
		if(Light_Val>2800 )
		{
			TIM_SetCompare1(TIM1,450);
			OLED_ShowChinese(16*5,0,6,16,1);  // 光亮度为低 LED高
		}
		if(Light_Val<1000)
		{
			TIM_SetCompare1(TIM1,100);
			OLED_ShowChinese(16*5,0,4,16,1);  // 光亮度为高 LED弱
		}
		
	 OLED_ShowNum(16*5,16,Light_Val,4,16,1);
	 OLED_ShowNum(16*5,16*2,temp,2,16,1);
	 OLED_ShowNum(16*5,16*3,humi,2,16,1);

		
		drv_systick_delayms(200);
		OLED_Refresh();
		
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)      //key4 返回上一级
			{
				drv_systick_delayms(30); //按下按键时消抖
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)          //确认该按键按下
				{
					while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0);    //按下低电平的时长，松手
				}
				OLED_Clear();
				TIM_SetCompare1(TIM1,0);
				return 0;
			}
				
		
		
		
	}
	

}