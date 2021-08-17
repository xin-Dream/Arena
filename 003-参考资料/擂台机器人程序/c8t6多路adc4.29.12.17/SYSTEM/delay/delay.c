#include "delay.h"

__IO uint32_t TIMinDelay=0;

void SysTick_Handler(void)
{
	if(TIMinDelay!=0)
		TIMinDelay--;
}

void delay_init(void)
{
	if(SysTick_Config(72)==1)
	{
		while(1);
	}
}

void delay_us(uint32_t nTime)
{
	TIMinDelay=nTime;
	while(TIMinDelay!=0);
}

void delay_ms(uint32_t nTime)
{
	TIMinDelay=nTime*1000;
	while(TIMinDelay!=0);
}

void delay_ms_for(uint32_t mTime)
{
	u16 i,j,k;
	for(i=72;i>0;i--)
		for(j=1000;j>0;j--)
			for(k=mTime;k>0;k--);
}

void delay_us_for(uint32_t mTime)
{
	u16 i,j,k;
	for(i=72;i>0;i--)
			for(k=mTime;k>0;k--);
}
