
#include "wifi_menu.h"
#include "oled.h"
#include "drv_systick.h"
#include "WIFI.h"
#include "string.h"
#include "LED.h"


char USART2_RxPacket[100]={0};   //接收数据数组,接收为文本（字符），用char，要求一次接收不超100
u8 USART2_RverFlag;
u8 USART2_RverData;

		

u8 wifi_menu(void)
{
		OLED_ShowChinese(0,0,21,16,0);
		OLED_ShowChinese(16,0,21,16,0);
		OLED_ShowChinese(16*1,0,21,16,0);
		OLED_ShowChinese(16*2,0,10,16,0);   //消
		OLED_ShowChinese(16*3,0,11,16,0);   //息
		OLED_ShowChinese(16*4,0,12,16,0);  //内
		OLED_ShowChinese(16*5,0,13,16,0);  //容 
		OLED_ShowChinese(16*6,0,21,16,0);
		OLED_ShowChinese(16*7,0,21,16,0);
		
		OLED_Refresh();	
	
	while(1)
	{
	
			if(USART2_RverFlag==1)
			{
				USART2_RverFlag=0;
				OLED_ShowString(0,16,"           ",16,1);

				OLED_ShowString(0,16,(u8 *)USART2_RxPacket,16,1);
		
				printf("%s",USART2_RxPacket);
				OLED_Refresh();	

					
					if(strcmp(USART2_RxPacket,"LED_ON")==0)
					{
						//printf("%s",USART2_RxPacket);
						LED1_ON();
						memset(USART2_RxPacket,0,sizeof(USART2_RxPacket));
					}
					if(strcmp(USART2_RxPacket,"LED_OFF")==0)
					{
					//	printf("%s",USART2_RxPacket);
						LED1_OFF();
						memset(USART2_RxPacket,0,sizeof(USART2_RxPacket));
					}	
								
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




				
	}

}



void  USART2_IRQHandler(void)
{
	static u8 RXState=0;     //定义个静态变量表状态，静态变量出了该函数的作用域值不会清0
	static u8 pRxPacket=0;  //用于看接收到第几个数据了
	
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	//	USART_SendData(USART1, USART_ReceiveData(USART2));  //WIFI模块收到数据时，MCU通过串口1把收到的数据打印到电脑上
	
	USART2_RverData=USART_ReceiveData(USART2);
		if(RXState==0)
		{
			if(USART2_RverData=='*')     //接收到自定义数据包头成立
			{
				RXState=1;
				pRxPacket=0;    //接收数据下标清0，从数组第一位开始接收数据
			}
			else
			{
				RXState=0;
			}
		}
		else if(RXState==1)  
		{
			if(USART2_RverData=='\r')   //有可能接收数据时接收到包尾
			{
				RXState=2;
			}
			else
			{
				USART2_RxPacket[pRxPacket]=USART2_RverData;
				pRxPacket++;
			}

		}
		
		else if(RXState==2)
		{
			if(USART2_RverData=='\n')   //接收第2个包尾
			{
				USART2_RverFlag=1;         //接收数据包完成标志位置1，表接收完成
				RXState=0;                //开始下一轮数据接收
			
			  USART2_RxPacket[pRxPacket]='\0';  //结束标志位
			}			
		}
	}
}









