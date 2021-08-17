#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM2_Int_Init(u16 arr,u16 psc);

//重设计时  
void start_time(void);
			
//获取计时  说明：返回系统计时，单位毫秒
u16 mseconds(void);

//获取计时  说明：返回系统计时，单位秒			
u16 seconds(void);
void stop_time(void);
void beep_time(void);
void beep_stop(void);
void reset_time(void);
			
void TIM5_Int_Init(u16 arr,u16 psc);
//重设计时  
void start_time_1(void);		
//获取计时  说明：返回系统计时，单位毫秒
u16 mseconds_1(void);
//获取计时  说明：返回系统计时，单位秒			
u16 seconds_1(void);
void stop_time_1(void);
void beep_time_1(void);
void reset_time_1(void);

#endif
