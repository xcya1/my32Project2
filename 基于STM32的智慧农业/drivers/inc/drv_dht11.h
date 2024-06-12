#ifndef _DRV_DHT11_H_
#define _DRV_DHT11_H_ 

#include "stm32f4XX.h"
#include "drv_systick.h"
#define u8 uint8_t
void DHT11_IO_OUT(void);
void DHT11_IO_IN(void);
void DHT11_Rst(void) ;
u8 DHT11_Check(void) ;
u8 DHT11_Read_Bit(void) ;
u8 DHT11_Read_Byte(void) ;
u8 DHT11_Read_Data(u8 *temp,u8 *humi) ;
u8 DHT11_Init(void);
  
#endif // _DRV_DHT11_H_
