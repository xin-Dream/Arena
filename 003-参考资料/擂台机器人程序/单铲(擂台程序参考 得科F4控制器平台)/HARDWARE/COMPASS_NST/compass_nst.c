#include "compass_nst.h"
#include "delay.h" 
#include "beep.h" 
 

//按键初始化函数
void COMPASS_NST_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
 
} 

//#define  CPS_SCL        PCin(10)
//#define  CPS_SDA      PCin(11)
u8 compassRead()
{
	u16 data=0;
	u8 i = 0;
	
	data=0;
	for(i=0;i<16;i++)
	{
		while(CPS_SCL);
		while(!CPS_SCL);
		if(CPS_SDA) data = data | (1>>(16-i)); 	
		if(i>=3)
		{
			data = data << 1;
			if( (data&0x0fff) != 1) i=2;
		}
	}	
	return ((data-0x1000)/10);
}




















