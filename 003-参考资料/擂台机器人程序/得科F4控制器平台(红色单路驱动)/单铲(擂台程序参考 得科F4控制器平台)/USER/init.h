/***************************************
* MarineRobot Ver1.0	 
* �����˹��ܺ���


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

#define KEY_BEEP 1     //1Ϊ���������� 0Ϊ�ر�
#define JIGUANG 1     //1Ϊ����1Ϊ���Ⲣ������0Ϊ�ر�
 
void MarineRobot_init(void); //ϵͳӲ���ܳ�ʼ��


