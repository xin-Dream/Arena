#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"


void PWM_Init(void);
void motor(int motorID, int speed);
void allmotor(int speed_0, int speed_1, int speed_2, int speed_3);
void stop(void);
void off(int motorID);
void init_servos(u8 cmd);  //˵�����ŷ�������أ� 0 Ϊ�أ� 1 Ϊ��
void servos(u8 ch,int s);
	
#endif
