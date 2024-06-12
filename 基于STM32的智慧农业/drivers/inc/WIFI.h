#ifndef __WIFI_H
#define __WIFI_H

#include "stm32f4xx.h"
#include "USART1.h"

//extern u8 str[20];
void WIFI_USART_2_Init(void);

void usart_sendstr(USART_TypeDef*USARTx,char *str,int size);


#endif