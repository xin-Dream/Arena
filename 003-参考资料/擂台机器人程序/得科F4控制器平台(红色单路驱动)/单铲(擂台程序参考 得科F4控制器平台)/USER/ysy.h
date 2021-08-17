#include "init.h"

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//字符串数显
#define ShowAI					display_GB2312_u16 //四位数显
#define ShowDI					display_GB2312_u1		//一位数显
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle

void speed_dispaly(void);//速度数显
int abs(int a,int b);
int Touch(void);//触摸AD转换
void up_stage(void);//单次登台
void start_feedback(void);//启动反馈
int analog_scan_close(void);//测距记录 最近传感器
int analog_scan_far(void);//测距记录 最远传感器
void touch_sensor(void);//触摸开关
void test(void);//测试模式总函数
int select_high(void);//掉台检测
void find_single();
int Find_Taizi();