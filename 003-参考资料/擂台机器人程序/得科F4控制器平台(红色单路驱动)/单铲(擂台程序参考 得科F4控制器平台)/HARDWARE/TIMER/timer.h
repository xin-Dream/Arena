#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM2_Int_Init(u16 arr,u16 psc);

//�����ʱ  
void start_time(void);
			
//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ����
u16 mseconds(void);

//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ��			
u16 seconds(void);
void stop_time(void);
void beep_time(void);
void beep_stop(void);
void reset_time(void);
			
void TIM5_Int_Init(u16 arr,u16 psc);
//�����ʱ  
void start_time_1(void);		
//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ����
u16 mseconds_1(void);
//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ��			
u16 seconds_1(void);
void stop_time_1(void);
void beep_time_1(void);
void reset_time_1(void);

#endif
