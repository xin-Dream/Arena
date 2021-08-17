#include "init.h"

void RobotInit(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOD时钟
	
	delay_init(168);				//延时初始化 
	uart_init(1,1000000);		//串口初始化波特率为115200  博创舵机

	BEEP_Init();						//蜂鸣器初始化
	KEY_Init();							//按键初始化		
	InitLCD();              //液晶初始化
	PWM_Init();             //pwm,电机、舵机初始化

	TIM2_Int_Init(1000-1,84-1);		//定时器时钟84M，分频系数84000，所以84M/84=1M的计数频率，计数1000次为1ms
	start_time();							 		//开启定时器	
	LED_Init();		  							//LED初始化	
	SENSOR_Init();								//模拟、数字传感器初始化	
}
