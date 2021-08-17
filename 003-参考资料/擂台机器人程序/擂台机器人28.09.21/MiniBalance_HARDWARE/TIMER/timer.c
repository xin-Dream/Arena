#include "timer.h"
/**************************************************************************
函数功能：定时器3通道3输入捕获初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数
返回  值：无
**************************************************************************/
void TIM3_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 			  //时钟预分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
    TIM_TimeBaseStructure.TIM_Period = 50000-1;			        //自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //时钟分频1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	    //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM3,DISABLE);
}


void TIM3_IRQHandler(void)
{
	static u8 time=0;//进入倾斜检测情况的次数
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    { 
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		if((PITCH>2000&&PITCH<34000)|(ROLL>2000&&ROLL<34000))
		{
			time++;
			if(time>20)//如果倾斜情况保持一秒及以上
			{
				Anti_Lean();
			}
			
		}
		else
		{
			time=0;//清除时间计数
			if(NumGrayLess(1000)>1&&NumLenMore(CM40)>0)//当有两个底部灰度传感器检测到灰度较大时
			{
				baizheng();
				if(NumLenMore(CM40)>1)
				{
					dengtai_auto();
				}
				else
				{
					Attack_Defend();
				}
				
			}
			else 
			{
				Attack_Defend();
			}
		}

		
    }
}

