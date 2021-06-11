//
// Created by dream on 2021/6/11.
//

#ifndef INC_002_ARENA_MOTORCONTROL_H
#define INC_002_ARENA_MOTORCONTROL_H

#include "macro.h"


void motor_control(int L_speed, int R_speed);

int Limit_range(int speed);

int32_t SpdPIDCalc(int32_t SetPoint, float CurrentPoint);


#endif //INC_002_ARENA_MOTORCONTROL_H
