#include "EXTI.h"


void EXTI_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;	            //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
	
}

void EXTI4_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	            //端口配置
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
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

}

void EXTI4_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	EXTI_GPIO_Init();

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级0， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

}

void EXTI15_10_IRQHandler(void)
{
	LED_On;
	delay_ms(300);
	printf("A12:%d,A15:%d\r\n",GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15));
//		Attack_Defend();
//		Avoid_Falling_180();
	LED_Off;
//	u8 xiaodou=0;
//	u8 i;

//	if(EXTI_GetITStatus(EXTI_Line15)|EXTI_GetITStatus(EXTI_Line12))
//	{
//		for (i=0;i<10;i++)
//		{
//			if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==1)|(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==1))
//			{
//				xiaodou++;
//				delay_us(100);
//			}
//		}
//		
//		if(xiaodou>6)
//		{
//			if((PITCH>2000&&PITCH<34000)|(ROLL>2000&&ROLL<34000))//检查是否有倾斜
//			{
//				Attack_Defend();
//		//		Anti_Lean();
//			}	
//			else
//			{

//				LED_On;
//				delay_ms(300);
//				printf("A12:%d,A15:%d\r\n",GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15));
//		//		Attack_Defend();
//		//		Avoid_Falling_180();
//				LED_Off;


//			}		
//		}
//	}

	EXTI_ClearITPendingBit(EXTI_Line12);  //清除LINE4上的中断标志位
	EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE4上的中断标志位
}
