#include "stm32f4XX.h"
#include "LED.h"
#include "systick_Delay.h"
#include "KEY.h"
#include "USART1.h"
#include "string.h"
#include "EXTI.h"


u8 key_ret;
u8 key_flag;
char str[20];
char c;
u8 e=0;



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	LED_Init();
	systick_Init(168);
	KEY_Init();
	USART_1_Init();
	
	
	while(1)
	{
		

//		if(i==1)
//		{
//								
//				LED_flow();
//			
//			
//		}
//		
//		key_ret=key_scan();

//		
//		if(key_ret==1)
//		{
//			key_flag++;
//			if(key_flag==1)
//				LED1_ON();
//			if(key_flag==2)
//			{
//				LED1_OFF();
//				key_flag=0;
//			}
//		}

//		if(key_ret==2)
//		{
//			key_flag++;
//			if(key_flag==1)
//				LED2_ON();
//			if(key_flag==2)
//			{
//				LED2_OFF();
//				key_flag=0;
//			}		
//		}
//		
//		if(key_ret==3)
//		{
//			printf("123\r\n");
//		
//		}
//		
//		
//		
//		if(key_ret==4)
//		{
//			key_flag++;
//			if(key_flag==1)
//				i=1;
//			if(key_flag==2)
//			{
//				i=0;
//				key_flag=0;
//			}
//		}




				if(strcmp(str,"LED1_ON")==0)
				{
					e=0;
					printf("%s",str);
					LED1_ON();
				//	 memset(str, 0,20);
						
					
				}
				if(strcmp(str,"LED1_OFF")==0)
				{
					e=0;
					printf("%s",str);
						LED1_OFF();
					//memset(str, 0,20);
				}
		}
}


	
	

	
	
void USART1_IRQHandler()
{
	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{
	
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		c=USART_ReceiveData(USART1);
		if(c!='\r')
		{
		
			str[e]=c;
			
		}
		else
		{
				str[e]='\0';
		}
	
		e++;
	
	
		
//		if(e==1)
//		{
//		USART_SendData(USART1,'A');
//			
//		}
//		if(e==2)
//		{
//		USART_SendData(USART1,'B');
//		
//		}
//		if(e==3)
//		{
//		USART_SendData(USART1,'C');
//			
//		}
//		if(e==4)
//		{
//		USART_SendData(USART1,'D');
//			
//		}
//		if(e==5)
//		{
//		USART_SendData(USART1,'E');
//		
//		}
//		if(e==6)
//		{
//		USART_SendData(USART1,'F');
//			
//		}
//		if(e==7)
//		{
//		USART_SendData(USART1,'E');
//			
//		}
//		if(e==8)
//		{
//		USART_SendData(USART1,'T');
//			
//		}
		
		
		
		
		
		
//		if(e==4)
//		{
//		LED3_OFF();
//			
//		}
//						if(e==5)
//		{
//		LED2_OFF();
//			
//		}
//							if(e==6)
//		{
//		LED1_OFF();
//			
//		}
			
			
			//str[e]=c;
			
		//USART_SendData(USART1,str[e]);
		
	//e++;

	}


}
		



