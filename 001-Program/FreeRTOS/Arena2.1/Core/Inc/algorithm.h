//
// Created by dream on 2021/6/12.
//

#ifndef INC_002_ARENA_ALGORITHM_H
#define INC_002_ARENA_ALGORITHM_H


#include "macro.h"

/*
 * 小函数-------------------------------------------------------------------------------------
 */
int my_abs(int number);

uint32_t my_32abs(uint32_t number);

/*
 * 一阶低通滤波函数-------------------------------------------------------------------------------------
 */
float filter(float alpha, float adc_now, float adc_pre);

/*
 * 快速排序算法-------------------------------------------------------------------------------------
 */
void my_qsort(int a[], int low, int high);

void quick_sort(int a[], int length);

int partition(int a[], int low, int high);


/*
 * 变权重均值计算-------------------------------------------------------------------------------------
 */
int varweight_mean(int a[]);

/*
 * 方向判断函数-------------------------------------------------------------------------------------
 */
int direction_judge(int a[]);

/*
 * 角度控制算法-------------------------------------------------------------------------------------
 */
int angle_position(int TargetAngle);

int angle_incremental(int deviation);

int Get_Target(int start, int bias);

int Get_Bias(int start, int target);

#endif //INC_002_ARENA_ALGORITHM_H
