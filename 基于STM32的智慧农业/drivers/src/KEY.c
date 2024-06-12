#include "KEY.h"
#include "drv_systick.h"

void KEY_Init(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOC, ENABLE);    //外设的总线时钟在存储器和总线架构中找外设
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //只有在设置端口为GPIO_Mode_OUT时才用设置,可以看GPIO_Init
   // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOE , &GPIO_InitStructure);
	 GPIO_Init(GPIOC , &GPIO_InitStructure);

}

u8 key_scan(void)
{
	u8 ret=0;
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
	{
		drv_systick_delayms(30); //按下按键时消抖
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)          //确认该按键按下
		{
			ret=1;
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0);    //按下低电平的时长，松手
		}
	}
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)
	{
		drv_systick_delayms(30); //按下按键时消抖
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0)          //确认该按键按下
		{
			ret=2;
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)==0);    //按下低电平的时长，松手
		}
	}
	
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)==0)
	{
		drv_systick_delayms(30); //按下按键时消抖
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)==0)          //确认该按键按下
		{
			ret=3;
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)==0);    //按下低电平的时长，松手
		}
	}
	
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)
	{
	drv_systick_delayms(30); //按下按键时消抖
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)          //确认该按键按下
		{
			ret=4;
			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0);    //按下低电平的时长，松手
		}
	}

	return ret;

}