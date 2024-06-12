#include "WIFI.h"
#include "drv_systick.h"
#include "string.h"
//开发板的WIFI模块与MCU通过串口2通信

//char USART2_RxPacket[100];   //接收数据数组,接收为文本（字符），用char，要求一次接收不超100

//u8 USART1_RverFlag;
//u8 USART1_RverData;



void WIFI_USART_2_Init(void)  //参数可以设为波特率
{
	  GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF;    //端口设为复用
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;   //推挽既能
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOD,& GPIO_InitStructure);
		
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6,GPIO_AF_USART2);
	
	USART_InitStructure.USART_BaudRate=115200;   //设置波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx |USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2,ENABLE);
	
}

void usart_sendstr(USART_TypeDef*USARTx,char *str,int size)  //自定义发送字符串函数
{
	u8 i=0;
	USART_ClearFlag(USARTx,USART_FLAG_TC);
	for(i=0;i<size;i++)
	{
		USART_SendData(USARTx,*str);
		while(USART_GetFlagStatus( USARTx,USART_FLAG_TC)==0);
		USART_ClearFlag(USARTx, USART_FLAG_TC);
		str++;
	}
}




//设WIFI模块为客户端，在主函数中调用
//	usart_sendstr(USART2,"AT+RESTORE\r\n",strlen("AT+RESTORE\r\n"));
//	drv_systick_delayms(2000);
//	usart_sendstr(USART2,"AT\r\n",strlen("AT\r\n"));
//	drv_systick_delayms(500);
//	usart_sendstr(USART2,"AT+CWMODE_CUR=1\r\n",strlen("AT+CWMODE_CUR=1\r\n"));   //设为服务器
//	drv_systick_delayms(500);
//	usart_sendstr(USART2,"AT+CIPMUX=0\r\n",strlen("AT+CIPMUX=0\r\n"));           //单连接模式
//	drv_systick_delayms(1000);
//	usart_sendstr(USART2,"AT+CWJAP_CUR=\"xc\",\"123456xc\"\r\n",strlen("AT+CWJAP_CUR=\"xc\",\"123456xc\"\r\n"));
//	drv_systick_delayms(7000);
//	usart_sendstr(USART2,"AT+CIPSTART=\"TCP\",\"192.168.43.178\",9003\r\n",strlen("AT+CIPSTART=\"TCP\",\"192.168.43.178\",9003\"\r\n"));
//	drv_systick_delayms(2000);
//	usart_sendstr(USART2,"AT+CIPSEND=2\r\n",strlen("AT+CIPSEND=2\r\n"));
//	drv_systick_delayms(500);
//	usart_sendstr(USART2,"OK\r\n",strlen("0K\r\n"));
//	drv_systick_delayms(500);
//-------------------------------------------------------------------------------------------





//------------------------------------------------------
//				if(USART1_RverFlag==1)
//				{
//					OLED_Clear();		
//					OLED_ShowChar(0,0,USART2_RxPacket[0],16,1);
//					OLED_ShowChar(8,0,USART2_RxPacket[1],16,1);
//					OLED_ShowChar(8*2,0,USART2_RxPacket[2],16,1);
//					OLED_ShowChar(8*3,0,USART2_RxPacket[3],16,1);
//					OLED_ShowChar(8*4,0,USART2_RxPacket[4],16,1);
//					OLED_ShowChar(8*5,0,USART2_RxPacket[5],16,1);
//					OLED_ShowChar(8*7,0,USART2_RxPacket[6],16,1);
//					if(sizeof(USART2_RxPacket)-1==7)
//					{
//						OLED_ShowChar(8*8,0,USART2_RxPacket[7],16,1);
//					}
//					OLED_Refresh();
//					USART1_RverFlag=0;
//					if(strcmp(USART2_RxPacket,"LED_ON")==0)
//					{
//						printf("%s",USART2_RxPacket);
//						LED1_ON();
//						memset(USART2_RxPacket,0,sizeof(USART2_RxPacket));
//					}
//					if(strcmp(USART2_RxPacket,"LED_OFF")==0)
//					{
//						printf("%s",USART2_RxPacket);
//						LED1_OFF();
//						memset(USART2_RxPacket,0,sizeof(USART2_RxPacket));
//					}	
//				}	




//void  USART2_IRQHandler(void)
//{
//	static u8 RXState=0;     //定义个静态变量表状态，静态变量出了该函数的作用域值不会清0
//	static u8 pRxPacket=0;  //用于看接收到第几个数据了
//	
//	if(USART_GetFlagStatus(USART2,USART_IT_RXNE))
//	{
//		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	//	USART_SendData(USART1, USART_ReceiveData(USART2));  //WIFI模块收到数据时，MCU通过串口1把收到的数据打印到电脑上
	
//	USART1_RverData=USART_ReceiveData(USART2);
//		if(RXState==0)
//		{
//			if(USART1_RverData=='@')     //接收到自定义数据包头成立
//			{
//				RXState=1;
//				pRxPacket=0;    //接收数据下标清0，从数组第一位开始接收数据
//			}
//			else
//			{
//				RXState=0;
//			}
//		}
//		else if(RXState==1)  
//		{
//			if(USART1_RverData=='\r')   //有可能接收数据时接收到包尾
//			{
//				RXState=2;
//			}
//			else
//			{
//				USART2_RxPacket[pRxPacket]=USART1_RverData;
//				pRxPacket++;
//			}

//		}
//		
//		else if(RXState==2)
//		{
//			if(USART1_RverData=='\n')   //接收第2个包尾
//			{
//				USART1_RverFlag=1;         //接收数据包完成标志位置1，表接收完成
//				RXState=0;                //开始下一轮数据接收
//			
//			  USART2_RxPacket[pRxPacket]='\0';  //结束标志位
//			}			
//		}
//	}
//}




