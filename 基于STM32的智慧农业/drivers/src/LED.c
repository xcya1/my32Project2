#include "LED.h"
#include "drv_systick.h"



void LED_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;    //配置端口的模式可为输出\输入\复用\模拟
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   //推挽输出，既能输出高低电平   //开漏默认输出低低电平，除非加上拉电阻
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;     //设置上不上拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10 );

	
//寄存器操作，控制GPIOE的8引脚输出低电平（对寄存器操作要看中文参考手册）
//	RCC->AHB1ENR |=(0x01<<4);  //开启GPIOE外设的时钟  ，如果是开BEEP的是GPIOB的外设，移动的位数要看手册
//	
//有些寄存器复位为0，若本来就要设为0，可以不用配置，看手册
//	GPIOE->MODER &=~(0x03E<<16);           //端口模式设置如果是两位控制一个引脚一般要先清0，0x03E就为第几个引脚口对应的位数，16转2进制
//	GPIOE->MODER |=(0x035<<16);
//	
//	GPIOE->ODR &=~(0x07<<8);           //ODR数据输出寄存器，设置0x07引脚产生低电平

}


void LED1_ON(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_8);
}


void LED1_OFF(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_9);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
}

void LED3_ON(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

void LED3_OFF(void)
{
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}



void LED_flow(void)
{

		LED1_ON();
	drv_systick_delayms(500);
		LED1_OFF();

		LED2_ON();
	drv_systick_delayms(500);;
		LED2_OFF();

		LED3_ON();
		drv_systick_delayms(500);
		LED3_OFF();
		
}