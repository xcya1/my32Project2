#ifndef __SYSTICK_DELAY_
#define __SYSTICK_DELAY_

#include "stm32f4xx.h"

void systick_Init(uint8_t systick);
//void systick_delay_ms(uint16_t ms);

void systick_delayms(uint16_t ms);
void systick_delayus(uint16_t us);

#endif