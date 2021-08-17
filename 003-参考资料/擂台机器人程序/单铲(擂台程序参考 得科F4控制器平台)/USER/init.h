/***************************************
* MarineRobot Ver1.0	 
* 机器人功能函数


***************************************/

#include "stm32f4xx.h" 

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "lcd.h"
#include "usart.h"
#include "pwm.h"
#include "sensor.h"
#include "timer.h" 
//#include "myiic.h"
//#include "24cxx.h"
//#include "compass_nst.h"
#include "servor_bc.h"

#define KEY_BEEP 1     //1为按键有声音 0为关闭
#define JIGUANG 1     //1为串口1为激光并开启，0为关闭
 
void MarineRobot_init(void); //系统硬件总初始化


