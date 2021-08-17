#include "pwm.h"

#define         SERVO_CENTER    4016   /* Center value of Servo  500ms~2500ms  1000~5000     */
#define         HANDLE_STEP     19     /* 1 degree part value          */


 

//TIM4 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14ʱ��ʹ��    	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); //GPIOA8����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM1 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel3 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
 
    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM14
 
										  
} 

//TIM4 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14ʱ��ʹ��    	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //GPIOA8����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //GPIOA8����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM1 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel3 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	//��ʼ��TIM1 Channel4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
 
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM14
 
										  
} 

void PWM_Init()
{
	TIM3_PWM_Init(1000-1,3-1);		//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/250=4Khz. 
	TIM4_PWM_Init(1000-1,3-1);
	init_servos(1);  //˵�����ŷ�������أ� 0 Ϊ�أ� 1 Ϊ��
}

void motor(int motorID, int speed)
{
	if(speed>1000) speed=1000;
	if(speed<-1000) speed=-1000;
	
	if(motorID == 0) 
	{
		if(speed >= 0)
		{
			TIM_SetCompare1(TIM4,1000-speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare2(TIM4,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
		else
		{
			TIM_SetCompare2(TIM4,1000+speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare1(TIM4,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
	}
	else if(motorID == 1)
	{
		if(speed >= 0)
		{
			TIM_SetCompare3(TIM4,1000-speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare4(TIM4,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
		else
		{
			TIM_SetCompare4(TIM4,1000+speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare3(TIM4,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
	}
	else if(motorID == 2)
	{
		if(speed >= 0)
		{
			TIM_SetCompare1(TIM3,1000-speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare2(TIM3,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
		else
		{
			TIM_SetCompare2(TIM3,1000+speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare1(TIM3,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
	}
	else if(motorID == 3)
	{
		if(speed >= 0)
		{
			TIM_SetCompare3(TIM3,1000-speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare4(TIM3,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
		else
		{
			TIM_SetCompare4(TIM3,1000+speed);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			TIM_SetCompare3(TIM3,1000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		}
	}
}

void allmotor(int speed_0, int speed_1, int speed_2, int speed_3)
{
	motor(0, speed_0);
	motor(1, speed_1);
	motor(2, speed_2);
	motor(3, speed_3);
}

int Ls,Rs;
void GoodMoto(int lspeed,int rspeed)//��·���
{
	Ls=lspeed;
	Rs=rspeed;
	motor(2,lspeed);
	motor(3,rspeed);
}

void stop()
{
	allmotor(0, 0, 0, 0);
}

void off(int motorID)
{
	switch(motorID)
	{
		case 0:  motor(0, 0); break;	//�޸ıȽ�ֵ���޸�ռ�ձ�
		case 1:  motor(1, 0); break;
		case 2:  motor(2, 0); break;
		case 3:  motor(3, 0); break;
	} 
}
	

void init_servos(u8 cmd)  //˵�����ŷ�������أ� 0 Ϊ�أ� 1 Ϊ��
{
	if(cmd == 1)  TIM_Cmd(TIM4, ENABLE);  			//��TIM4	
	else if(cmd == 0) TIM_Cmd(TIM4, DISABLE);  //�ر�TIM4	
}

//˵�������ָ���ŷ������ֵ  ch Ϊ�ŷ�����ţ���ΧΪ 0��3�����壩�� 4��19����չ�壩 s Ϊ�ŷ������ֵ����ΧΪ -90~90
void servos(u8 ch,int s)
{
	switch(ch)
	{
		case 4:  TIM_SetCompare1(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;	//�޸ıȽ�ֵ���޸�ռ�ձ�
		case 3:  TIM_SetCompare2(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;
		case 2:  TIM_SetCompare3(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;//2��
		case 1:  TIM_SetCompare4(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;//���1��
	}  
}
