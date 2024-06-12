#ifndef __DRV_SYSTICK_H__
#define __DRV_SYSTICK_H__
#include "stm32f4xx.h"
void drv_systick_init(uint8_t systick);
void drv_systick_delayms(uint16_t ms);
void drv_systick_delayus(uint16_t us);

#endif  // __DRV_SYSTICK_H__


