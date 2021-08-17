#include "init.h"

#define nst_analog_8_white 1500
#define nst_analog_8_black 500
#define nst_analog_8_threshold (nst_analog_8_white+nst_analog_8_black)/2    //8路巡线灰度传感器白绿阈值，一般取（白色值+深色值）/2

u16 Ain[8]={0};


u8  nst_analog_8(u8 channel) //8路灰度传感器获取函数
{

	u8 i=0;
	u16 value=0;
	for(i=0;i<8;i++)
	{
		Ain[i]= 0;
	}
	
	if(channel == 1)
	{
		PDout(8) = 0;
		PBout(15) = 0;
		PBout(14) = 0;	
		delay_ms(4);
		Ain[0]= analog(15);	
		PDout(8) = 1;
		PBout(15) = 0;
		PBout(14) = 0;	
		delay_ms(4);
		Ain[1]= analog(15);
		PDout(8) = 0;
		PBout(15) = 1;
		PBout(14) = 0;	
		delay_ms(4);
		Ain[2]= analog(15);
		PDout(8) = 1;
		PBout(15) = 1;
		PBout(14) = 0;	
		delay_ms(4);
		Ain[3]= analog(15);
		delay_ms(4);
		PDout(8) = 0;
		PBout(15) = 0;
		PBout(14) = 1;	
		delay_ms(4);
		Ain[4]= analog(15);
		PDout(8) = 1;
		PBout(15) = 0;
		PBout(14) = 1;	
		delay_ms(4);
		Ain[5]= analog(15);
		PDout(8) = 0;
		PBout(15) = 1;
		PBout(14) = 1;	
		Ain[6]= analog(15);
		PDout(8) = 1;
		PBout(15) = 1;
		PBout(14) = 1;	
		delay_ms(4);
		Ain[7]= analog(15);
	}
	else if(channel == 2)
	{
		PEout(4) = 0;
		PEout(3) = 0;
		PEout(2) = 0;
		delay_ms(4);
		Ain[0]= analog(14);
		PEout(4) = 1;
		PEout(3) = 0;
		PEout(2) = 0;
		delay_ms(4);
		Ain[1]= analog(14);
		PEout(4) = 0;
		PEout(3) = 1;
		PEout(2) = 0;
		delay_ms(4);
		Ain[2]= analog(14);
		PEout(4) = 1;
		PEout(3) = 1;
		PEout(2) = 0;
		delay_ms(4);
		Ain[3]= analog(14);
		PEout(4) = 0;
		PEout(3) = 0;
		PEout(2) = 1;
		delay_ms(4);
		Ain[4]= analog(14);
		PEout(4) = 1;
		PEout(3) = 0;
		PEout(2) = 1;
		delay_ms(4);
		Ain[5]= analog(14);
		PEout(4) = 0;
		PEout(3) = 1;
		PEout(2) = 1;
		delay_ms(4);
		Ain[6]= analog(14);
		PEout(4) = 1;
		PEout(3) = 1;
		PEout(2) = 1;
		delay_ms(4);
		Ain[7]= analog(14);
	}
	
	for(i=0;i<8;i++)
	{
		if(Ain[i] >= nst_analog_8_threshold) value=(value|(1<<i));
		else value=(value&(~(1<<i)));
	}
	
	return value;
	
}

void Robot_Ready(void)		//机器人出发准备
{
	

}






