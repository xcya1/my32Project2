#include "stm32f4XX.h"
#include "LED.h"
#include "BEEP.h"
#include "drv_systick.h"
#include "KEY.h"
#include "USART1.h"
#include "string.h"
#include "EXTI.h"
#include "TIM.h"
#include "oled.h"
#include "bmp.h"
#include "DMA.h"
#include "ADC.h"
#include "WIFI.h"

#include "menu1.h"
#include "key_control_menu.h"
#include "pwm_control_menu.h"
#include "wifi_menu.h"



u32 buf1[10]={0x11,0x12,0x13};
u32 buf2[10]={0};

u8 key_ret;
u8 menu;


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	drv_systick_init(168);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	USART_1_Init();
//	DMA2_Init(1,buf1,buf2);
//	TIM6_Init();  
	
	OLED_Init();
	ADC1_Init();
	WIFI_USART_2_Init();
	
	DHT11_Init();
	PWM_TIM1_Init();
	
	
	usart_sendstr(USART2,"AT+RESTORE\r\n",strlen("AT+RESTORE\r\n"));
	drv_systick_delayms(2000);
	usart_sendstr(USART2,"AT\r\n",strlen("AT\r\n"));
	drv_systick_delayms(500);
	usart_sendstr(USART2,"AT+CWMODE_CUR=1\r\n",strlen("AT+CWMODE_CUR=1\r\n"));   //设为服务器
	drv_systick_delayms(500);
	usart_sendstr(USART2,"AT+CIPMUX=0\r\n",strlen("AT+CIPMUX=0\r\n"));           //单连接模式
	drv_systick_delayms(1000);
	usart_sendstr(USART2,"AT+CWJAP_CUR=\"xc\",\"123456xc\"\r\n",strlen("AT+CWJAP_CUR=\"xc\",\"123456xc\"\r\n"));
	drv_systick_delayms(7000);
	usart_sendstr(USART2,"AT+CIPSTART=\"TCP\",\"192.168.43.178\",9003\r\n",strlen("AT+CIPSTART=\"TCP\",\"192.168.43.178\",9003\"\r\n"));
	drv_systick_delayms(2000);
	usart_sendstr(USART2,"AT+CIPSEND=2\r\n",strlen("AT+CIPSEND=2\r\n"));
	drv_systick_delayms(500);
	usart_sendstr(USART2,"OK\r\n",strlen("0K\r\n"));
	drv_systick_delayms(500);


	
	while(1)
	{
		
		menu=menu1();
		if(menu==1) key_control_menu();
		if(menu==2) pwm_control_menu(); 
		if(menu==3) wifi_menu();
		
	}
}





	
	
	



