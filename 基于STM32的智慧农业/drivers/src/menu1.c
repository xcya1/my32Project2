//menu1为选择界面


#include "menu1.h"
#include "oled.h"
#include "drv_systick.h"



u8 menu1_flag=1;

u8 menu1(void)
{
		OLED_ShowChinese(16*2,0,22,16,1);   //消
		OLED_ShowChinese(16*3,0,23,16,1);   //息
		OLED_ShowChinese(16*4,0,24,16,1);  //内
		OLED_ShowChinese(16*5,0,25,16,1);  //容 
  	OLED_Refresh();

//	OLED_Clear();
	while(1)
	{
	
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)   //选择某一项
		{
			drv_systick_delayms(30); 
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)          
			{
				menu1_flag++;
				if(menu1_flag==4)
				{
					menu1_flag=1;
				}
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0); 
			}
		}
		
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)      //确认该按键按下
		{
			drv_systick_delayms(30); //按下按键时消抖
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)        
			{
				while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0);    
			}		
			OLED_Clear();
			return menu1_flag;	
		}
		
		
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

		
		switch(menu1_flag)
		{
		case 1 : 
		OLED_ShowChar(0,16,'*',16,1);
	  OLED_ShowChinese(16,16,16,16,1);    //按
	  OLED_ShowChinese(16*2,16,17,16,1);  //键
		OLED_ShowChinese(16*3,16,14,16,1); //控 
		OLED_ShowChinese(16*4,16,15,16,1); //制
		
		OLED_ShowChar(0,16*2,' ',16,1);
		OLED_ShowChinese(16,16*2,18,16,1);  //传
	  OLED_ShowChinese(16*2,16*2,19,16,1);  //感
		OLED_ShowChinese(16*3,16*2,20,16,1);  //器
	  OLED_ShowChinese(16*4,16*2,14,16,1);  //控
		OLED_ShowChinese(16*5,16*2,15,16,1);  //制
		
		OLED_ShowChar(0,16*3,' ',16,1);
		OLED_ShowString(16,16*3,"WIFI",16,1);
		OLED_ShowChinese(16*3,16*3,14,16,1);  //控
		OLED_ShowChinese(16*4,16*3,15,16,1);  //制
	
		OLED_Refresh();
		break;
			
		case 2: 
		OLED_ShowChar(0,16,' ',16,1);
	  OLED_ShowChinese(16,16,16,16,1);    //按
	  OLED_ShowChinese(16*2,16,17,16,1);  //键
		OLED_ShowChinese(16*3,16,14,16,1); //控 
		OLED_ShowChinese(16*4,16,15,16,1); //制
		
		OLED_ShowChar(0,16*2,'*',16,1);
		OLED_ShowChinese(16,16*2,18,16,1);  //传
	  OLED_ShowChinese(16*2,16*2,19,16,1);  //感
		OLED_ShowChinese(16*3,16*2,20,16,1);  //器
	  OLED_ShowChinese(16*4,16*2,14,16,1);  //控
		OLED_ShowChinese(16*5,16*2,15,16,1);  //制
		
		OLED_ShowChar(0,16*3,' ',16,1);
		OLED_ShowString(16,16*3,"WIFI",16,1);
		OLED_ShowChinese(16*3,16*3,14,16,1);  //控
		OLED_ShowChinese(16*4,16*3,15,16,1);  //制
		OLED_Refresh();
		break;
			
		case 3 : 
		OLED_ShowChar(0,16,' ',16,1);
	  OLED_ShowChinese(16,16,16,16,1);    //按
	  OLED_ShowChinese(16*2,16,17,16,1);  //键
		OLED_ShowChinese(16*3,16,14,16,1); //控 
		OLED_ShowChinese(16*4,16,15,16,1); //制
		
		OLED_ShowChar(0,16*2,' ',16,1);
		OLED_ShowChinese(16,16*2,18,16,1);  //传
	  OLED_ShowChinese(16*2,16*2,19,16,1);  //感
		OLED_ShowChinese(16*3,16*2,20,16,1);  //器
	  OLED_ShowChinese(16*4,16*2,14,16,1);  //控
		OLED_ShowChinese(16*5,16*2,15,16,1);  //制
		
		OLED_ShowChar(0,16*3,'*',16,1);
		OLED_ShowString(16,16*3,"WIFI",16,1);
		OLED_ShowChinese(16*3,16*3,14,16,1);  //控
		OLED_ShowChinese(16*4,16*3,15,16,1);  //制
		OLED_Refresh();
		OLED_Refresh();
		break;
		}
	
	
	
	
	
	
	}
	




}
