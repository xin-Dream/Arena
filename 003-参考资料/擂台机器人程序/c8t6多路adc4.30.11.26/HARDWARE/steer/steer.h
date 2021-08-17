#ifndef __STEER_H
#define __STEER_H	
#include "stm32f10x.h"	 

void PWMInit(void);
void ScanInit(void);

extern u16 scan_output[50];
extern u16 steer_current_position;
void SteerScan(void);


#endif

















