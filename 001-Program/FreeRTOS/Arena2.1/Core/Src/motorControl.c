//
// Created by dream on 2021/6/11.
//

#include "motorControl.h"


/*
 * --引用的官方类型-----------------------------------------------------------------------------------------
 */

extern TIM_HandleTypeDef htim3;

extern Motor_TypeDef motor;

/*
 * --函数-----------------------------------------------------------------------------------------
 */


/**
 * @brief encode read motor Function
 * @param motorSide:left/right speed:0-1000
 * @retval None
 */

void encode_read(TIM_HandleTypeDef L_tim, TIM_HandleTypeDef R_tim) {

    motor.L_encode = __HAL_TIM_GET_COUNTER(&L_tim);
    motor.R_encode = __HAL_TIM_GET_COUNTER(&R_tim);

    motor.L_encode_Dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&L_tim);
    motor.R_encode_Dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&R_tim);

    if (motor.L_encode_Dir && motor.L_encode != 0) {
        motor.L_encode = limit_range((60000 - motor.L_encode), (MAXSPEED * 0.7));
    }

    if (motor.R_encode_Dir && motor.R_encode != 0) {
        motor.R_encode = limit_range((60000 - motor.R_encode), (MAXSPEED * 0.7));
    }

    __HAL_TIM_SET_COUNTER(&L_tim, 0);
    __HAL_TIM_SET_COUNTER(&R_tim, 0);
}


/**
 * @brief Bluetooth controlled motor Function
 * @param motorSide:left/right speed:0-1000
 * @retval None
 */
void remoteControl() {
    switch (motor.motion_flag) {
        case forward:
            motor_control((motor.speed), (motor.speed));
            break;
        case backward:
            motor_control((-motor.speed), (-motor.speed));
            break;
        case left:
            motor_control((motor.speed), (-motor.speed));
            break;
        case right:
            motor_control((-motor.speed), (motor.speed));
            break;
        case stop:
            motor_control(0, 0);
            break;
        case roll:
            angle_incremental(180);
//            angle_position(90);
            motor.motion_flag = stop;
            break;
        default:
            motor_control(0, 0);
    }
}


/**
 * @brief Motor Control Function
 * @param motorSide:left/right speed:0-1000
 * @retval None
 */
void motor_control(int L_speed, int R_speed) {
    L_speed = limit_range(L_speed, MAXSPEED);
    R_speed = limit_range(R_speed, MAXSPEED);

    if (L_speed < 0) {
        L_speed = -L_speed;
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, L_speed);
    } else if (L_speed >= 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, L_speed);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
    }

    if (R_speed < 0) {
        R_speed = -R_speed;
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, R_speed);
    } else if (L_speed >= 0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, R_speed);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
    }
}

