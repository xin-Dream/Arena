#include "motor.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

void MiniBalance_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIO外设时钟使能
    //设置该引脚为复用输出功能,输出TIM1 CH1 CH4的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //TIM_CH1 -4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能
	  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH2预装载使能
	  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH3预装载使能
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能

    TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

    TIM_Cmd(TIM1, ENABLE);  //使能TIM1

}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{
    int temp;
    if(a<0)  temp=-a;
    else temp=a;
    return temp;
}


/**************************************************************************
函数功能：限幅
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
int xianfu(int num)
{
	if(num<-100) return -100;
	if(num>100)  return  100;
	else return num;

}

/**************************************************************************
函数功能：控制电机转速和方向
入口参数：左轮PWM、右轮PWM
返回  值：无
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

//本角度坐标系 逆时针为正方向 一圈细分为36000个部分
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

int Get_Bias(int start,int target)//获得与目标角度的偏移值
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

void baizheng(void)//调整机器人的朝向，使其能够朝向与初始方向成90度的倍数的角度
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

