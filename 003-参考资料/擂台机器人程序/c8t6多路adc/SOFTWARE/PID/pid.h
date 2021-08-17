#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include "interrupt.h"
float pid_calculate_1(float a,float b);
float pid_calculate_2(float a,float b);

extern float major_power,power_L,power_R,power_1,power_2,power_3,power_4;
void moto_calculate(void);
#endif
