//
// Created by dream on 2021/6/11.
//

#include "motorControl.h"

/**
 * @brief Motor Control Function
 * @param motorSide:left/right speed:0-1000
 * @retval None
 */
void motor_control(int L_speed, int R_speed) {
    L_speed = Limit_range(L_speed);
    R_speed = Limit_range(R_speed);

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

/**
 * @brief limit max speed Function
 * @param set speed
 * @return speed in limit range
 * @retval None
 */
int Limit_range(int speed) {
    if (speed > MAXSPEED) {
        speed = MAXSPEED;
    }
    if (speed < -MAXSPEED) {
        speed = -MAXSPEED;
    }
    return speed;
}


/**
 * @brief 	Speed closed loop controller
 * @param 	Input:Current control quantity;
 * 			Output:Target control quantity
 * @retval 	None
 */
int32_t SpdPIDCalc(int32_t SetPoint, float CurrentPoint) {
    SetPoint = SetPoint * 0.6;
    float iError, dError;
    iError = SetPoint - CurrentPoint; //偏差

    /* 小的误差是正常的*/
    if ((iError < 10) && (iError > -10))
        iError = 0.0;

    sPID.SumError += iError;                        //积分
    dError = iError - sPID.LastError;                //微分

    sPID.LastError = iError;
    return (ROUND_TO_INT32(sPID.Proportion * iError //比例
                           + sPID.Integral * (float) sPID.SumError //积分
                           + sPID.Derivative * dError)); //微分
}