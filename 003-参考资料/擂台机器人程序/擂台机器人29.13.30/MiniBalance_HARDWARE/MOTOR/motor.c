#include "motor.h"
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

void MiniBalance_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //ʹ��GPIO����ʱ��ʹ��
    //���ø�����Ϊ�����������,���TIM1 CH1 CH4��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //TIM_CH1 -4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��
	  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��
	  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��

    TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1

}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{
    int temp;
    if(a<0)  temp=-a;
    else temp=a;
    return temp;
}


/**************************************************************************
�������ܣ��޷�
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
int xianfu(int num)
{
	if(num<-100) return -100;
	if(num>100)  return  100;
	else return num;

}

/**************************************************************************
�������ܣ����Ƶ��ת�ٺͷ���
��ڲ���������PWM������PWM
����  ֵ����
**************************************************************************/
void Set_Speed(int left,int right)
{
	left=xianfu(left);
	right=xianfu(right);
	PWML=left;
	PWMR=right;
	if(left>=0)  {TIM1->CCR1=left;TIM1->CCR2=0;}
	else  {TIM1->CCR1=0;TIM1->CCR2=(-1)*left;}
	if(right>=0)  {TIM1->CCR3=right;TIM1->CCR4=0;}
	else  {TIM1->CCR3=0;TIM1->CCR4=(-1)*right;}

}

void Set_Speed_Safe(int left,int right)
{
	if((left>0&&PWML<0)|(left<0&&PWML>0)|(right>0&&PWMR<0)|(right<0&&PWMR>0))
	{
		Set_Speed(0,0);
		delay_ms(100);
	}
	Set_Speed(left,right);
}

void Set_Speed_Show(int left,int right)
{
	Set_Speed(left,right);
	OLED_Show();

}

void Set_Speed_Safe_Show(int left,int right)
{
	Set_Speed_Safe(left,right);
	OLED_Show();
}

void Stop_Forever()
{
	Set_Speed_Safe(0,0);
	while(1)
	{
	}
}
void dengtai(void)
{
	Set_Speed_Safe_Show(0,0);
	LED_On;
	delay_ms(100);
	LED_Off;
	delay_ms(100);
	LED_On;
//	delay_ms(100);
//	LED_Off;
	
//	Set_Speed_Show(-80,-80);
//	delay_ms(1200);

//	Set_Speed_Show(0,0);
//	delay_ms(100);

//	Set_Speed_Show(30,30);
//	OLED_Show();
	while(1);

}

//���Ƕ�����ϵ ��ʱ��Ϊ������ һȦϸ��Ϊ36000������
int Get_Target(int start,int bias)
{
	start=start+bias;
	if(start<0)
	{
		start+=36000;
	}
	else if(start>36000)
	{
		start-=36000;
	}
	return start;

}

int Get_Bias(int start,int target)//�����Ŀ��Ƕȵ�ƫ��ֵ
{
	int bias;
	bias=target-start;
	if(bias<-18000)
	{
		bias=bias+36000;
	}
	else if(bias>18000)
	{
		bias=bias-36000;
	}
	return bias;

}

//void Clock_90()
//{
//	int target;
//	int bias;
//	target=Get_Target(YAW,-9000);
//	while(1)
//	{
//		bias=Get_Bias(YAW,target);
//		if(myabs(bias)<2000)
//		{
//			if(bias<0)
//				Set_Speed(10,-10);
//			else
//				Set_Speed(-10,10);
//		}
//		else
//			Set_Speed(-bias/200,bias/200);
//		if(myabs(bias)<250)
//		{
//			break;
//		}
//	}
//	Set_Speed(BASIC,BASIC);
//}

//void Counter_90()
//{
//	int target;
//	int bias;
//	target=Get_Target(YAW,9000);
//	while(1)
//	{
//		bias=Get_Bias(YAW,target);
//		if(myabs(bias)<2000)
//		{
//			if(bias<0)
//				Set_Speed(10,-10);
//			else
//				Set_Speed(-10,10);
//		}
//		else
//			Set_Speed(-bias/200,bias/200);
//		if(myabs(bias)<250)
//		{
//			break;
//		}
//	}
//	Set_Speed(BASIC,BASIC);
//}

//void Clock_180()
//{
//	int target;
//	int bias;
//	target=Get_Target(YAW,-18000);
//	while(1)
//	{
//		bias=Get_Bias(YAW,target);
//		if(myabs(bias)<2000)
//		{
//			if(bias<0)
//				Set_Speed(10,-10);
//			else
//				Set_Speed(-10,10);
//		}
//		else
//			Set_Speed(-bias/200,bias/200);
//		if(myabs(bias)<250)
//		{
//			break;
//		}
//	}
//	Set_Speed(BASIC,BASIC);
//}

void Turn_to(int pianzhuan)
{
	int target;
	int bias;
	int sum=0;
	pianzhuan=pianzhuan*100;
	target=Get_Target(YAW,pianzhuan);
	while(1)
	{
		bias=Get_Bias(YAW,target);
		sum+=bias;
		Set_Speed_Show(-bias*parap,bias*parap);
		delay_ms_for(2);
		if(myabs(bias)<600)
		{
			break;
		}
	}
	Set_Speed_Show(0,0);
}
//-bias*parap-sum*parai,bias*parap+sum*parai
void Turn_to_abs(int target)
{
//	int target;
	int bias;
	int sum=0;
	target=target*100;
//	target=Get_Target(YAW,pianzhuan);
	while(1)
	{
		bias=Get_Bias(YAW,target);
		sum+=bias;
		Set_Speed_Show(-bias*parap,bias*parap);
		delay_ms_for(2);
		if(myabs(bias)<600)
		{
			break;
		}
	}
	Set_Speed_Show(0,0);
}

void baizheng(void)//���������˵ĳ���ʹ���ܹ��������ʼ�����90�ȵı����ĽǶ�
{
	if(YAW<4500|YAW>31500)
	{
		Turn_to_abs(0);
	}
	else if(YAW<13500|YAW>4500)
	{
		Turn_to_abs(90);
	}
	else if(YAW<22500|YAW>13500)
	{
		Turn_to_abs(180);
	}
	else if(YAW<31500|YAW>22500)
	{
		Turn_to_abs(270);
	}	
}

