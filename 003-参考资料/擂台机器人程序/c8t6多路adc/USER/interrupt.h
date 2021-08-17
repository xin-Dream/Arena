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

#define SHZ_OPEN 'a'
#define SHZ_CLOSE 'b'
#define GZ_OPEN 'c'
#define GZ_CLOSE 'd'

#define SHZ_LIGHT   GPIO_SetBits(GPIOC,GPIO_Pin_15)
#define SHZ_UNLIGHT GPIO_ResetBits(GPIOC,GPIO_Pin_15)
#define GZ_LIGHT    GPIO_SetBits(GPIOC,GPIO_Pin_14)
#define GZ_UNLIGHT  GPIO_ResetBits(GPIOC,GPIO_Pin_14 )

#define MHQ	1
#define MHT 2
#define GG 3

#define GG_OPEN 'e'
#define GG_CLOSE 'f'

#define YUZHI 0.30
#define LIGHT GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define UNLIGHT GPIO_ResetBits(GPIOB,GPIO_Pin_9)


#endif

