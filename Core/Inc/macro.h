/*
 * macro.h
 *
 *  Created on: 2021年5月23日
 *      Author: dream
 */

#ifndef INC_MACRO_H_

#define INC_MACRO_H_

/*
 * --头文件-----------------------------------------------------------------------------------------
 */

#include "main.h"
#include "oled.h"
#include "string.h"
#include "stdio.h"
#include "communication.h"

/*
 * --定义结构体-----------------------------------------------------------------------------------------
 */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim1;;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/*
 * --函数-----------------------------------------------------------------------------------------
 */

void hardware_Init();

void ParamInit(void);

/*
 * --变量-----------------------------------------------------------------------------------------
 */

//串口


#define MAX_RECV_LEN 1024
#define BUFFER_SIZE 255

struct UART_Parameter {
    //串口中断用参数
    uint8_t msg_buff[1024];
    uint8_t *msg;

    //DMA+空闲中断用参数
    uint8_t receive_buff[255];

};

//extern UART_Parameter uart1;
//extern UART_Parameter uart2;

struct UART_Parameter uart1;
struct UART_Parameter uart2;

/*
 * -------------------------------------------------------------------------------------------
 */

//JY60

struct SAngle {
    short Angle[3];
    short T;
};

struct Angle {
    uint16_t PITCH;
    uint16_t ROLL;
    uint16_t YAW;
};


struct Angle Angle_int;
struct SAngle sAngle;



//extern SAngle sAngle;
//extern Angle Angle_int;

/*
 * -------------------------------------------------------------------------------------------
 ADC数据读取
 包括灰度传感器与红外测距传感器
 */


uint32_t ADC_Buff[3];

/*
 * -------------------------------------------------------------------------------------------
 PID控制器参数设置
 */

struct PID_TypeDef {
    __IO int32_t
            SetPoint;        //设定目标 Desired Value
    __IO float SumError;        //误差累计
    __IO float Proportion;    //比例常数 Proportional Const
    __IO float Integral;        //积分常数 Integral Const
    __IO float Derivative;    //微分常数 Derivative Const
    __IO int LastError;        //Error[-1]
    __IO int PrevError;        //Error[-2]

};

struct PID_TypeDef sPID;



//PID_TypeDef *ptr = &sPID;

/*
 * -------------------------------------------------------------------------------------------
 Encode数据
 */

struct motor {
    //编码器
    int encode_Dir;
    uint32_t encode_captureNum32;
    uint16_t encode_captureNum16;
    uint32_t lastCap;
    uint32_t simSpeed;        //电机模拟速度，无单位，60/1000对应100

    int setSpeed;
};


struct motor L_motor;
struct motor R_motor;


//extern motor L_motor;
//extern motor R_motor;


struct variable {
    int motion_flag;
    int speed;
};

struct variable globalVariable;


//extern variable globalVariable;

#define MAXSPEED    300
#define forward        1
#define backward    2
#define left        3
#define right        4
#define stop        5

/* 四舍五入 */
//将浮点数x四舍五入为int32_t
#define ROUND_TO_INT32(x)   ((int32_t)(x)+0.5f)>=(x)? ((int32_t)(x)):((uint32_t)(x)+1)

/*
 * -------------------------------------------------------------------------------------------
 */
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

#endif /* INC_MACRO_H_ */
