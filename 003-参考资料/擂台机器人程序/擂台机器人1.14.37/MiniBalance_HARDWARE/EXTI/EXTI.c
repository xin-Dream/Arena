#include "EXTI.h"


void EXTI_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PA�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	            //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
	
}

void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	EXTI_GPIO_Init();


  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�0�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

}


void EXTI4_IRQHandler(void)
{
//	u8 xiaodou=0;
//	u8 i;
//	for (i=0;i<5;i++)
//	{
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12))
//		{
//			xiaodou++;
//			delay_us(500);
//		}
//	}
//	
//	if(xiaodou>3)
//	{
//		LED_On;
//		Avoid_Falling_180();
//		LED_Off;		
//	}
    LED_On;
	delay_ms(100);
	LED_Off;
	delay_ms(100);
	LED_On;
	
	
//	if((PITCH>2000&&PITCH<34000)|(ROLL>2000&&ROLL<34000))//����Ƿ�����б
//	{
//		Anti_Lean();
//	}	
//	else
//	{
//		LED_On;
//		Avoid_Falling_180();
//		LED_Off;
//	}

	
	
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ
}
