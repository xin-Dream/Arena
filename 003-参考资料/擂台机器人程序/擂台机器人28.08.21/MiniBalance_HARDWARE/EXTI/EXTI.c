#include "EXTI.h"


void EXTI_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
	
}

void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	EXTI_GPIO_Init();


  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;	//KEY2
	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

}


void EXTI15_10_IRQHandler(void)
{
	u8 xiaodou=0;
	u8 i;
	for (i=0;i<5;i++)
	{
		if(Edge_Left|Edge_Right)
		{
			xiaodou++;
//			delay_ms(1);
		}
	}
	
	if(xiaodou>3)
	{
		LED_On;
		Avoid_Falling_180();
		LED_Off;		
	}
	
	
	EXTI_ClearITPendingBit(EXTI_Line15|EXTI_Line12);  //清除LINE4上的中断标志位
}
