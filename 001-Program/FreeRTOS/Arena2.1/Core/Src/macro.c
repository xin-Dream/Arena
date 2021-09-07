//
// Created by dream on 2021/6/11.
//

#include "macro.h"

/*
 * --引用的官方类型-----------------------------------------------------------------------------------------
 */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/*
 * --自定义的内部全局类型-----------------------------------------------------------------------------------------
 */

Motor_TypeDef motor;
Sensor_TypeDef sensors;

extern UARTParams_TypeDef uart1_params;
extern UARTParams_TypeDef uart2_params;


void ParamsInit() {
    OLED_Init();

    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, (uint8_t *) uart1_params.receive_buff, BUFFER_SIZE);

    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *) uart2_params.receive_buff, BUFFER_SIZE);

    HAL_ADC_Start_DMA(&hadc1, sensors.ADC_Buff, ADC_CHANNEL_NUMBER);

    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);

    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    structParams();
}

void structParams() {
    motor.speed = 30;
    motor.turn_coff = 0.023;
}


void OLED_Show(void) {
    //	len1=1000;len2=2000;len3=3000;len4=4000;
    //	len5=5000;len6=6000;len7=7000;len8=8000;
    //=============第一行显示len1—len4=======================//
    // 第一行数据显示前面四个传感器
    // 依次为：前左，下左，下右，前右
//    OLED_ShowNum(00, 0, sensors.ADC_Buff[3], 4, 12);
//    OLED_ShowNum(32, 0, sensors.ADC_Buff[4], 4, 12);
//    OLED_ShowNum(64, 0, sensors.ADC_Buff[5], 4, 12);
//    OLED_ShowNum(96, 0, sensors.ADC_Buff[6], 4, 12);
    OLED_ShowNum(00, 0, sensors.ADC_Buff[5], 4, 12);
    OLED_ShowNum(32, 0, sensors.ADC_Buff[7], 4, 12);
    OLED_ShowNum(64, 0, sensors.ADC_Buff[4], 4, 12);
    OLED_ShowNum(96, 0, sensors.ADC_Buff[9], 4, 12);
    //=============第二行显示len5—len7=======================//
    // 第二行数据显示另外三个测距传感器
    // 依次为：左，后，右
//    OLED_ShowNum(00, 10, sensors.ADC_Buff[7], 4, 12);
//    OLED_ShowNum(32, 10, sensors.ADC_Buff[8], 4, 12);
//    OLED_ShowNum(64, 10, sensors.ADC_Buff[9], 4, 12);
    OLED_ShowNum(00, 10, sensors.ADC_Buff[6], 4, 12);
    OLED_ShowNum(32, 10, sensors.ADC_Buff[8], 4, 12);
    OLED_ShowNum(64, 10, sensors.ADC_Buff[3], 4, 12);
    OLED_ShowNum(96, 10, sensors.motion_flag, 4, 12);
//	OLED_ShowNum(96, 10, motion_flag, 4, 12);
    //=============第三行显示编码器1=======================//
    OLED_ShowString(00, 20, "L", 12);
    if (motor.L_encode_Dir)
        OLED_ShowString(12, 20, "+", 12), OLED_ShowNum(24, 20,
                                                       motor.L_encode, 5, 12);
    else
        OLED_ShowString(12, 20, "-", 12), OLED_ShowNum(24, 20, motor.L_encode,
                                                       5, 12);
    //=============第三行显示编码器2=======================//
    OLED_ShowString(62 + 00, 20, "R", 12);
    if (motor.R_encode_Dir)
        OLED_ShowString(62 + 12, 20, "+", 12), OLED_ShowNum(62 + 24, 20,
                                                            motor.R_encode, 5, 12);
    else
        OLED_ShowString(62 + 12, 20, "-", 12), OLED_ShowNum(62 + 24, 20,
                                                            motor.R_encode, 5, 12);

    //=============第四行显示PWM左=======================//
    OLED_ShowString(00, 30, "L", 12);
    if (motor.speed < 0)
        OLED_ShowString(13, 30, "-", 12), OLED_ShowNum(31, 30,
                                                       -motor.speed, 4, 12);
    else
        OLED_ShowString(13, 30, "+", 12), OLED_ShowNum(31, 30, motor.speed,
                                                       4, 12);
    //=============第四行显示PWM右=======================//
//	OLED_ShowString(64 + 00, 30, "R",12);
//	if (L_motor.speed < 0)
//		OLED_ShowString(64 + 13, 30, "-",12), OLED_ShowNum(64 + 31, 30, -L_motor.speed,
//				4, 12);
//	else
//		OLED_ShowString(64 + 13, 30, "+",12), OLED_ShowNum(64 + 31, 30, L_motor.speed, 4,
//				12);
    //=============第五行显示角度=======================//
    OLED_ShowString(0, 40, "P", 12);
    OLED_ShowNum(0 + 14, 40, sensors.PITCH, 5, 12);
    OLED_ShowString(42, 40, "R", 4);
    OLED_ShowNum(42 + 14, 40, sensors.ROLL, 5, 12);
    OLED_ShowString(85, 40, "Y", 4);
    OLED_ShowNum(85 + 14, 40, sensors.YAW, 5, 12);
    //=============第六行显示灰度=======================//
    //  第六行数据显示三个灰度传感器
    // 依次为：前左，后中，前右
    OLED_ShowNum(00, 50, sensors.ADC_Buff[0], 4, 12);
    OLED_ShowNum(40, 50, sensors.ADC_Buff[1], 4, 12);
    OLED_ShowNum(80, 50, sensors.ADC_Buff[2], 4, 12);

    //=============刷新=======================//
    OLED_Refresh_Gram();
}

/*
 * --各算法函数-----------------------------------------------------------------------------------------
 */


/**
 * @brief limit max speed Function
 * @param set speed
 * @return speed in limit range
 * @retval None
 */
int limit_range(int speed, int limit_num) {
    if (speed > limit_num) {
        speed = limit_num;
    }
    if (speed < -limit_num) {
        speed = -limit_num;
    }
    return speed;
}

/**
 * @简 介： ADC数据分类
 * @参 数：  无
 * @返回值：  无
 * @备 注：  无
 */
void ADCpartition() {
    uint32_t range_forward;

    //将前两测距传感器数据存入Range_forward并处理，将处理后的数据用做前侧数据
    sensors.Range_forward[0] = sensors.ADC_Buff[5];
    sensors.Range_forward[1] = sensors.ADC_Buff[9];
    //数据进行变权重处理
    range_forward = varweight_mean(sensors.Range_forward);

    //将周围测距传感器按，前后左右顺序分别存入Range_around
    sensors.Range_around[0] = range_forward;
    sensors.Range_around[1] = sensors.ADC_Buff[8];
    sensors.Range_around[2] = sensors.ADC_Buff[6];
    sensors.Range_around[3] = sensors.ADC_Buff[3];

    //按先左后右的顺序将传感器数据存入，以待后续处理
    sensors.Range_below[0] = sensors.ADC_Buff[7];
    sensors.Range_below[1] = sensors.ADC_Buff[4];

    //由于灰度传感器按三角放置，故按前左，前右，后中的顺序存入Gray
    sensors.Gray[0] = sensors.ADC_Buff[0];
    sensors.Gray[1] = sensors.ADC_Buff[1];
    sensors.Gray[2] = sensors.ADC_Buff[2];
}


void judge(void) {

    if (sensors.motion_flag == left) {
        angle_incremental(90);
    } else if (sensors.motion_flag == right) {
        angle_incremental(-90);
    } else if (sensors.motion_flag == backward) {
//        angle_incremental(180);
        return;
    } else {
        return;
    }
}