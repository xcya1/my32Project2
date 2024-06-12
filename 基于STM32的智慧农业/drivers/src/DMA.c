#include "DMA.h"
#include "USART1.h"

extern u32  buf1[10];
extern u32  buf2[10];

//设置存储器到存储器，只能采用DMA2 
void DMA2_Init(u32 size,u32*src,u32*drc)
{
	
		DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	 DMA_InitStruct.DMA_BufferSize=size;           //传输数据的个数
	 DMA_InitStruct.DMA_Channel=DMA_Channel_0 ;    //存储器到存储器只能用DMA2,数据流通道只有用到外设是才要注意设置,现在任意设
	 DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToMemory ;
	 DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable ;
	 DMA_InitStruct.DMA_Memory0BaseAddr=(u32)drc;     //目标地址，地址32位
	 DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single ;
	 DMA_InitStruct.DMA_MemoryDataSize=DMA_PeripheralDataSize_Byte ;  //单个传输数据的字节大小
	 DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;    //地址是否自增，只有外设时才不用自增
	 DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;    //只有是传输的数据一直变的时候才用循环，比如采样的数据
	
		DMA_InitStruct.DMA_PeripheralBaseAddr=(u32)src;  //源地址
	 DMA_InitStruct.DMA_PeripheralBurst=DMA_MemoryBurst_Single;
	 DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	 DMA_InitStruct.DMA_PeripheralInc=DMA_MemoryInc_Enable;
	 DMA_InitStruct.DMA_Priority=DMA_Priority_High;
                   
	DMA_Init( DMA2_Stream0,&DMA_InitStruct);  //存储器到存储器只能用DMA2，数据流通道只有用到外设是才要注意设置，现在可任意设置 参考手册204页  
	DMA_Cmd(DMA2_Stream0,ENABLE);
}



void buf_cmp(void)
{
	if(buf1[0]==buf2[0])
	{
		printf("buf1[0]=0x%x,buf1[0]=0x%x",buf1[0],buf2[0]);
	}
	else
	{
	
		printf("不同");
	}

}


	//while(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==0);
	//buf_cmp();