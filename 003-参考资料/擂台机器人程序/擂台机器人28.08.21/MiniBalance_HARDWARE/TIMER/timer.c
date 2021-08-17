#include "timer.h"
/**************************************************************************
�������ܣ���ʱ��3ͨ��3���벶���ʼ��
��ڲ�������ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ��
����  ֵ����
**************************************************************************/
void TIM3_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef        NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Prescaler = 72-1; 			  //ʱ��Ԥ��Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    TIM_TimeBaseStructure.TIM_Period = 50000-1;			        //�Զ���װֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //ʱ�ӷ�Ƶ1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3,TIM_FLAG_Update);
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  	    //��Ӧ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_Cmd(TIM3,DISABLE);
}


void TIM3_IRQHandler(void)
{
	static u8 time=0;//������б�������Ĵ���
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    { 
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		if((PITCH>2000&&PITCH<34000)|(ROLL>2000&&ROLL<34000))
		{
			time++;
			if(time>20)//�����б�������һ�뼰����
			{
				Anti_Lean();
			}
			
		}
		else
		{
			time=0;//���ʱ�����
			if(NumGrayLess(1000)>1&&NumLenMore(CM40)>0)//���������ײ��Ҷȴ�������⵽�ҶȽϴ�ʱ
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

