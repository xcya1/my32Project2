//由于外部晶振是8MHZ，需要改USART_Init()中327行 332行的25改为8


#include "LED.h"
#include "USART1.h"


char c1;
char ret;

u8 flag='A';
void USART_1_Init(void)  //参数可以设为波特率
{
	  GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_AF;    //端口设为复用
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;   //推挽既能
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,& GPIO_InitStructure);
		
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10,GPIO_AF_USART1);
	
	USART_InitStructure.USART_BaudRate=115200;   //设置波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx |USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	
}

                            //printf函数的实现会调用fputc函数
int fputc(int ch,FILE *f)   //printf函数重定向，printf默认是打印到屏幕上，需要重定向到串口上 调用C库的函数，要包含stdio.h
{
	USART_SendData(USART1,ch);                                //等待数据发送完
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //USART发送数据完USART_FLAG_TC会置1，该标志位为0则表还在发送
	USART_ClearFlag(USART1,USART_FLAG_TC); //数据发送完，USART_FLAG_TC（数据传输完成标志）会由硬件置1，需要软件清0（参考手册）

	return ch;
	
}



void USART1_IRQHandler()
{
	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{
	
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	
	}


}
	




