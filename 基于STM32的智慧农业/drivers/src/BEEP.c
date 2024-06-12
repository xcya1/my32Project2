#include "BEEP.h"

void BEEP_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOE,GPIO_Pin_8 |GPIO_Pin_9|GPIO_Pin_10 );
	
}
void BEEP_ON()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_10 );
}

void BEEP_OFF()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_10 );
}