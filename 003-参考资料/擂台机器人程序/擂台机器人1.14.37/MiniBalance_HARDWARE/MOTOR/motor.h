#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define parap 0.005
#define parap1 0.004
#define parai 0.001
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void Set_Pwm(u8 channel,int num);
void Set_Speed(int left,int right);
void Set_Speed_Show(int left,int right);
void Set_Speed_Safe(int left,int right);
void Set_Speed_Safe_Show(int left,int right);
void Clockwise(u8 angle);	
void Counterlockwise(u8 angle);
void dengtai(void);
//void Clock_90();
//void Counter_90();
//void Clock_180();
void Turn_to(int pianzhuan);
void Turn_to_abs(int pianzhuan);
void baizheng(void);
#endif
