#ifndef _SENSOR_H
#define _SENSOR_H
#include "sys.h"
#include "delay.h"

#define  N  50	     //每通道采10次
#define  M  16	     //为16个通道

void SENSOR_Init(void);
u16 analog(u8 port);
u8 digital(u8 port);
	
#endif
