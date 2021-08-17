#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

void MiniBalance_PWM_Init(u16 arr,u16 psc);
void Set_Pwm(u8 channel,int num);
void Set_Speed(int left,int right);
void Set_Speed_Show(int left,int right);
void Set_Speed_Safe(int left,int right);
void Set_Speed_Safe_Show(int left,int right);
void dengtai();
//void Clock_90();
//void Counter_90();
//void Clock_180();
void Turn_to(int pianzhuan);
void Turn_to_abs(int pianzhuan);
void baizheng(void);
#endif
