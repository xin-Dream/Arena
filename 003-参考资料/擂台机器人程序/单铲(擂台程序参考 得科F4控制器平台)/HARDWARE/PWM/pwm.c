#include "pwm.h"

#define         SERVO_CENTER    4016   /* Center value of Servo  500ms~2500ms  1000~5000     */
#define         HANDLE_STEP     19     /* 1 degree part value          */


 

//TIM4 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14时钟使能    	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); //GPIOA8复用为定时器3
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器14
	
	//初始化TIM1 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 
    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM14
 
										  
} 

//TIM4 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14时钟使能    	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //GPIOA8复用为定时器3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //GPIOA8复用为定时器3
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器14
	
	//初始化TIM1 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel3 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	
	//初始化TIM1 Channel4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM14
 
										  
} 

void PWM_Init()
{
	TIM3_PWM_Init(1000-1,3-1);		//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/250=4Khz. 
	TIM4_PWM_Init(1000-1,3-1);
	init_servos(1);  //说明：伺服电机开关， 0 为关， 1 为开
}

void motor(int motorID, int speed)
{
	if(speed>1000) speed=1000;
	if(speed<-1000) speed=-1000;
	
	if(motorID == 0) 
	{
		if(speed >= 0)
		{
			TIM_SetCompare1(TIM4,1000-speed);	//修改比较值，修改占空比
			TIM_SetCompare2(TIM4,1000);	//修改比较值，修改占空比
		}
		else
		{
			TIM_SetCompare2(TIM4,1000+speed);	//修改比较值，修改占空比
			TIM_SetCompare1(TIM4,1000);	//修改比较值，修改占空比
		}
	}
	else if(motorID == 1)
	{
		if(speed >= 0)
		{
			TIM_SetCompare3(TIM4,1000-speed);	//修改比较值，修改占空比
			TIM_SetCompare4(TIM4,1000);	//修改比较值，修改占空比
		}
		else
		{
			TIM_SetCompare4(TIM4,1000+speed);	//修改比较值，修改占空比
			TIM_SetCompare3(TIM4,1000);	//修改比较值，修改占空比
		}
	}
	else if(motorID == 2)
	{
		if(speed >= 0)
		{
			TIM_SetCompare1(TIM3,1000-speed);	//修改比较值，修改占空比
			TIM_SetCompare2(TIM3,1000);	//修改比较值，修改占空比
		}
		else
		{
			TIM_SetCompare2(TIM3,1000+speed);	//修改比较值，修改占空比
			TIM_SetCompare1(TIM3,1000);	//修改比较值，修改占空比
		}
	}
	else if(motorID == 3)
	{
		if(speed >= 0)
		{
			TIM_SetCompare3(TIM3,1000-speed);	//修改比较值，修改占空比
			TIM_SetCompare4(TIM3,1000);	//修改比较值，修改占空比
		}
		else
		{
			TIM_SetCompare4(TIM3,1000+speed);	//修改比较值，修改占空比
			TIM_SetCompare3(TIM3,1000);	//修改比较值，修改占空比
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
void GoodMoto(int lspeed,int rspeed)//两路电机
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
		case 0:  motor(0, 0); break;	//修改比较值，修改占空比
		case 1:  motor(1, 0); break;
		case 2:  motor(2, 0); break;
		case 3:  motor(3, 0); break;
	} 
}
	

void init_servos(u8 cmd)  //说明：伺服电机开关， 0 为关， 1 为开
{
	if(cmd == 1)  TIM_Cmd(TIM4, ENABLE);  			//打开TIM4	
	else if(cmd == 0) TIM_Cmd(TIM4, DISABLE);  //关闭TIM4	
}

//说明：设的指定伺服电机数值  ch 为伺服电机号，范围为 0～3（主板）， 4～19（扩展板） s 为伺服电机数值，范围为 -90~90
void servos(u8 ch,int s)
{
	switch(ch)
	{
		case 4:  TIM_SetCompare1(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;	//修改比较值，修改占空比
		case 3:  TIM_SetCompare2(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;
		case 2:  TIM_SetCompare3(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;//2口
		case 1:  TIM_SetCompare4(TIM4,SERVO_CENTER - s  * HANDLE_STEP); break;//舵机1口
	}  
}
