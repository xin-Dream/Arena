#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "stm32f10x.h"
#include "lcd.h"
#include "mpu9250.h"
#include "steer.h"
#include "pid.h"
extern u8 jkjjk;
extern float angle[3];
extern u8 angle_data_recive[3][3];

#define PA12 PAout(12) // PA12

#define YUZHI 0.30
#define LIGHT GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define UNLIGHT GPIO_ResetBits(GPIOB,GPIO_Pin_9)


#endif

