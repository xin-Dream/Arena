#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h" 

//LED�˿ڶ���
#define BEEP PDout(11)	// ����������IO 

void BEEP_Init(void);//��ʼ��	

//������ ˵��������һ�� 500Hz�� 0.3s ������
void beep(void);
void beepoff();
			
#endif

















