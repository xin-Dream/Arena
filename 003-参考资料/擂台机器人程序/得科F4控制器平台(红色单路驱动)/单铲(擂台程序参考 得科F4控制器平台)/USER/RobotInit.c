#include "init.h"

void RobotInit(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIODʱ��
	
	delay_init(168);				//��ʱ��ʼ�� 
	uart_init(1,1000000);		//���ڳ�ʼ��������Ϊ115200  �������

	BEEP_Init();						//��������ʼ��
	KEY_Init();							//������ʼ��		
	InitLCD();              //Һ����ʼ��
	PWM_Init();             //pwm,����������ʼ��

	TIM2_Int_Init(1000-1,84-1);		//��ʱ��ʱ��84M����Ƶϵ��84000������84M/84=1M�ļ���Ƶ�ʣ�����1000��Ϊ1ms
	start_time();							 		//������ʱ��	
	LED_Init();		  							//LED��ʼ��	
	SENSOR_Init();								//ģ�⡢���ִ�������ʼ��	
}
