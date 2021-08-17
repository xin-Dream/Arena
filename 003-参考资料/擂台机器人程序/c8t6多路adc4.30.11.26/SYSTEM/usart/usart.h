#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
void uart2_init(u32 bound);
void uart1_init(u32 bound);
void uart5_init(u32 bound);
void uart3_init(u32 bound);
void USART_SendData32(u32 data);
void floattoascsend(float data);
void GY25_init(void);
void getangle(void);
void uart_delay(void);
#endif


