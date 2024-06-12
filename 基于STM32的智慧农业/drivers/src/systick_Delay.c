//开发板上的晶振使用的是8MHZ的，STM32F4默认是25MHZ的，为了匹配达到系统的最高128MHZ，可以把system_stm32f4xx.c的
//136行的25改为8
//利用内核中的systick定时器，自定义精确的延时函数，要板子上的晶振
//定时器本质就是计数器

#include "systick_Delay.h"
                           //static限制变量只能在改文件中使用
static uint8_t fs_us=0;   //us需要记脉冲的次数
static uint16_t fs_ms=0;  //ms需要记脉冲的次数



void systick_Init(uint8_t systick) //参数为频率，是最大频率要提供给外设的   
{                           //SysTick是内核的要查内核手册，不是片上外设的参考手册
		SysTick->CTRL &=~0x05;   //SysTick定时器的控制寄存器CTRL ，&=~0x05 设置为8分频 关闭定时器 没开中断
		fs_us=systick/8;          //若systick为128，计1us需要计21次
		fs_ms=fs_us*1000;         //若systick为128，计1ms需要计的次
}


//void systick_delay_ms(uint16_t ms)   //定时器是24位的 fs_ms*ms;可能会越界  
//{
//	u32 temp=0;               //1次ms的次数乘以1000次就是1s的时间，类似于总价格=1个商品的价格*买了几个该商品
//	SysTick->LOAD=fs_ms*ms;  //LOAD为SysTick的重载寄存器，24位，自减，设置的重载值就是定时的时间，减到0会自动重载
//	SysTick->VAL=0;            //当前值清0  VAL为SysTick的当前值寄存器，用于查看重载值减到了多少
//	SysTick->CTRL |= 0x01;    //开启定时器，CTRL寄存器的第一位置1
//	do
//	{
//	
//		temp=SysTick->CTRL;  //CTRL寄存器的16位为定时器时间到的标志位，该位为1表定时时间到，为0表定时未到
//	
//	}while(!(temp&(0x01<<16)));  //定时时间到为1，在非为0，退出循环
//	SysTick->CTRL &=~0x01;    //关闭定时器，CTRL寄存器的第一位置0
//	
//	
//}


void systick_delayms(uint16_t ms)
{
	uint32_t temp=0;
	uint8_t  systick_flg=0;
	while(systick_flg == 0)
	{
		if(ms > 798)
		{
			SysTick->LOAD = fs_ms*798;//装载值
			ms = ms - 798;
		}
		else
		{

			SysTick->LOAD = fs_ms*ms;//装载值
			systick_flg =1;

		}
		SysTick->VAL = 0;//当前值
		SysTick->CTRL |= 0x01;//开启定时功能
		do
		{
			temp = SysTick->CTRL;//获取计数标志
		}
		while (!(temp&(0x01<<16)));//等待定时时间到
		SysTick->CTRL &= ~0x01;//关闭定时器
	}
	
}
/**********************************************************
函数名：drv_systick_delayus

函数功能：us定时功能

输入参数：systick 系统时钟

输出参数：无

其它说明：	

**********************************************************/
void systick_delayus(uint16_t us)
{
	uint32_t temp=0;
	SysTick->LOAD = fs_us*us;//装载值
	SysTick->VAL = 0;//当前值
	SysTick->CTRL |= 0x01;//开启定时功能
	do
	{
		temp = SysTick->CTRL;//获取计数标志
	}
	while (!(temp&(0x01<<16)));//等待定时时间到
	SysTick->CTRL &= ~0x01;//关闭定时器
}
