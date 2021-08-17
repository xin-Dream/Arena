#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h" 

extern __IO uint32_t TIMinDelay;
	 
void delay_init(void);
void delay_us(uint32_t nTime);
void delay_ms(uint32_t nTime);

void delay_ms_for(uint32_t mTime);
void delay_us_for(uint32_t mTime);
#endif





























