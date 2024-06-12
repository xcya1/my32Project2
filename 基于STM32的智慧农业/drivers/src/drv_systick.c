#include "drv_systick.h"
static uint8_t fs_us=0; // US需要记的次数
static uint16_t fs_ms=0;//ms需要计的次数
/**********************************************************
函数名：drv_systick_init

函数功能：滴答定时器的初始化

输入参数：systick 系统时钟

输出参数：无

其它说明：	时钟源使能8分屏

**********************************************************/
void drv_systick_init(uint8_t systick)
{
	SysTick->CTRL &= ~0x05; //8分频，关闭定时器
	fs_us = systick/8;  //计1US需要计21次
	fs_ms = fs_us*1000;
}

/**********************************************************
函数名：drv_systick_delayms

函数功能：MS定时功能

输入参数：systick 系统时钟

输出参数：无

其它说明：	

**********************************************************/
void drv_systick_delayms(uint16_t ms)
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
void drv_systick_delayus(uint16_t us)
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

