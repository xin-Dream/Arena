#ifndef _SENSOR_H
#define _SENSOR_H
#include "sys.h"
#include "delay.h"

#define  N  50	     //ÿͨ����10��
#define  M  16	     //Ϊ16��ͨ��

void SENSOR_Init(void);
u16 analog(u8 port);
u8 digital(u8 port);
	
#endif
