#inculude "ADC.h"

void ADC_Init()
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AN;
	
	
}


