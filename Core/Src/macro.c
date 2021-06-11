//
// Created by dream on 2021/6/11.
//
#include "macro.h"

/**
 * @brief ALL HardWare params init Function
 * @param None
 * @retval None
 */
void hardware_Init(){

    OLED_Init();
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, (uint8_t *) uart1.receive_buff, BUFFER_SIZE);

    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *) uart2.receive_buff, BUFFER_SIZE);

    HAL_ADC_Start_DMA(&hadc1, ADC_Buff, 10);

    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}


/**
 * @brief PID params init Function
 * @param None
 * @retval None
 */
void ParamInit(void) {
    sPID.LastError = 0;               // Error[-1]
    sPID.PrevError = 0;               // Error[-2]
    sPID.Proportion = 0.2; // 比例常数 Proportional Const
    sPID.Integral = 0;   // 积分常数  Integral Const
    sPID.Derivative = 0; // 微分常数 Derivative Const
    sPID.SetPoint = 0;     // 设定目标Desired Value

    L_motor.lastCap = 0;
    R_motor.lastCap = 0;

    globalVariable.speed = 30;

}