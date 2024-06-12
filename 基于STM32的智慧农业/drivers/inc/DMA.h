#ifndef __DMA_H
#define __DMA_H
#include "stm32f4xx.h"

void DMA2_Init(u32 size,u32*src,u32*drc);
void buf_cmp(void);
#endif
