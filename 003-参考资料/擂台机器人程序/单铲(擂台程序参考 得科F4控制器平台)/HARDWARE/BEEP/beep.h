#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

//LED端口定义
#define BEEP PDout(11)	// 蜂鸣器控制IO 

void BEEP_Init(void);//初始化	

//函数： 说明：发出一个 500Hz， 0.3s 的声音
void beep(void);
void beepoff();
			
#endif

















