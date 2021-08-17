//
// Created by dream on 2021/6/11.
//

#ifndef INC_002_ARENA_MOTORCONTROL_H
#define INC_002_ARENA_MOTORCONTROL_H

#include "macro.h"


/*
 * --函数----------------------------------------------------------------------------------------
 */


void motor_control(int L_speed, int R_speed);

void remoteControl();

void encode_read(TIM_HandleTypeDef L_tim, TIM_HandleTypeDef R_tim);


#endif //INC_002_ARENA_MOTORCONTROL_H
