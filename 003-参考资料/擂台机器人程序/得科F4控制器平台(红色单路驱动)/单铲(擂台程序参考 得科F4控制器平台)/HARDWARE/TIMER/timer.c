#include "timer.h"
#include "beep.h" 
#include "led.h" 

u16 count_ms_0=0;
u16 count_s_0=0;
u16 count_ms_1=0;
u16 count_s_1=0;
u8 beep_label=0;
u16 beep_ms=0;

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
    TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
//重设计时  说明：计时重设为 0
void start_time()
{
	count_ms_0=0;
	count_s_0=0;
	TIM_Cmd(TIM2,ENABLE);	//使能定时器3
}

//获取计时  说明：返回系统计时，单位毫秒
u16 mseconds()
{
	return count_ms_0;
}

//获取计时  说明：返回系统计时，单位秒			
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
	TIM_Cmd(TIM2,DISABLE); //使能定时器2
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
	TIM_Cmd(TIM5,ENABLE);	//使能定时器3
}

//获取计时  说明：返回系统计时，单位毫秒
u16 mseconds_1()
{
	return count_ms_1;
}

//获取计时  说明：返回系统计时，单位秒			
u16 seconds_1()
{
	return count_s_1;
}

u16 getseconds_1(){
	return (1000*count_s_1+count_ms_1);
}

void stop_time_1()
{
	TIM_Cmd(TIM5,DISABLE); //使能定时器2
}

void reset_time_1()
{
	count_ms_1=0;
	count_s_1=0;
}
//定时器3中断服务函数  1ms中断一次
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
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
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		count_ms_1++;
		if(count_ms_1 == 1000)  count_s_1++;
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}
