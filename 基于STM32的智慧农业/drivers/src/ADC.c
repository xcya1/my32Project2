#include "ADC.h"

uint16_t adc_data[100];

//电阻 PC10 可用ADC123 


void ADC1_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef  ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_DMA2|RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	ADC_CommonInitStruct.ADC_DMAAccessMode= ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4 ;
	ADC_CommonInitStruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	//ADC_InitStruct.ADC_ExternalTrigConv
	ADC_InitStruct.ADC_ExternalTrigConvEdge= ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_NbrOfConversion=1;
	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode=ENABLE;
	ADC_Init(ADC1, &ADC_InitStruct);

	DMA_InitStruct.DMA_BufferSize = 100;//需要搬运的数据的数量
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;//DMA的通道号       看手册得
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设到内存
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;//不适用fifo模式
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)adc_data; //目标地址
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;//单次触发
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//数据半字传输
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//目标地址自增
	DMA_InitStruct.DMA_Mode =DMA_Mode_Circular;//循环缓存模式

	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//数据来源地址
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;//优先级非常高
	DMA_Init(DMA2_Stream0, &DMA_InitStruct);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);//设置采样规则，采样时间
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 2, ADC_SampleTime_480Cycles);  //采样可变电阻
	
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);//设置DMA触发条件
	DMA_Cmd(DMA2_Stream0, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

	ADC_SoftwareStartConv(ADC1);//使能ADC1的软件触发
	
		
	
	
}



uint16_t drv_adc_res_value(void)
{
	uint32_t sum=0;                 //分辨率是12位 范围可为0~2^12-1
	uint8_t i =0;
	for(i=0;i<100;i++)
	{
		sum = sum + adc_data[i];
	}
	return (uint16_t)(sum/100);   //可以将数字转换为电压量
}


//-------------------------------------
//    OLED_ShowString(0,0,"Light:",16,1);
//		L_data=drv_adc_res_value();
//		
//		OLED_ShowNum(48,0,L_data,4,16,1);
//		OLED_Refresh();
//		printf("adc_value=%d\r\n",drv_adc_res_value());
//		drv_systick_delayms(500);
//----------------------------------------------------




//--------------------------------------------------
//		OLED_ShowNum(0,0,adc_data[0],4,16,1);
//		OLED_ShowNum(0,16,adc_data[1],4,16,1);
//		OLED_Refresh();
//		drv_systick_delayms(500);







