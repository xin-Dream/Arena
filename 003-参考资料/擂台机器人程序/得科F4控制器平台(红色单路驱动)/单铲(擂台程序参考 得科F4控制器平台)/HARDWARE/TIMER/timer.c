#include "timer.h"
#include "beep.h" 
#include "led.h" 

u16 count_ms_0=0;
u16 count_s_0=0;
u16 count_ms_1=0;
u16 count_s_1=0;
u8 beep_label=0;
u16 beep_ms=0;

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//�����ʱ  ˵������ʱ����Ϊ 0
void start_time()
{
	count_ms_0=0;
	count_s_0=0;
	TIM_Cmd(TIM2,ENABLE);	//ʹ�ܶ�ʱ��3
}

//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ����
u16 mseconds()
{
	return count_ms_0;
}

//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ��			
u16 seconds()
{
	return count_s_0;
}

u16 getseconds()
{
	return (1000*count_s_0+count_ms_0);
}

void stop_time()
{
	TIM_Cmd(TIM2,DISABLE); //ʹ�ܶ�ʱ��2
}

void reset_time()
{
	count_ms_0=0;
	count_s_0=0;
}

void beep_time()
{
	beep_label = 1;
	BEEP = 0;
}
void beep_stop()
{
		beep_label = 0;
	  BEEP = 1;
}
void start_time_1()
{
	count_ms_1=0;
	count_s_1=0;
	TIM_Cmd(TIM5,ENABLE);	//ʹ�ܶ�ʱ��3
}

//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ����
u16 mseconds_1()
{
	return count_ms_1;
}

//��ȡ��ʱ  ˵��������ϵͳ��ʱ����λ��			
u16 seconds_1()
{
	return count_s_1;
}

u16 getseconds_1(){
	return (1000*count_s_1+count_ms_1);
}

void stop_time_1()
{
	TIM_Cmd(TIM5,DISABLE); //ʹ�ܶ�ʱ��2
}

void reset_time_1()
{
	count_ms_1=0;
	count_s_1=0;
}
//��ʱ��3�жϷ�����  1ms�ж�һ��
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		if(beep_label == 1 )
		{
			beep_ms++;
			if(beep_ms >= 200)
			{
				BEEP = 1;
				beep_label = 0;
				beep_ms = 0;
			}
		}
		
		count_ms_0++;
		
		if(count_ms_0 == 1000)  count_s_0++;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		count_ms_1++;
		if(count_ms_1 == 1000)  count_s_1++;
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}
