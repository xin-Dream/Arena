#include "interrupt.h"
#include "usart.h"
#include "string.h"
#include ".\NRF24L01\24l01.h"
#include "./GPIO/GPIO.h"
#include "./adc/adc.h"
#include "delay.h"
extern u8 biaoji;
u8 rebuf[8]= {0,0,0,0,0,0,0,0};
u16 YAW=0,ROLL=0,PITCH=0;
//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == SET)
//	{
//		READ_MPU9250_origin();
//		Caculate_MPU9250();
//		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//	}
//}

void TIM3_IRQHandler(void)
{
	static u8 j=0;
    if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET)
    {
		extern u16 ADC_BUFF[14];
		static u16 ADC_Data[14];
        u8 data[30];
        u8 i;
		
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		if(j<10)
		{
			j++;
			for(i=0;i<14;i++)
			{
				ADC_Data[i]+=ADC_BUFF[i];
			}
		}
		else
		{
			j=0;
			for(i=0;i<14;i++)
			{
				ADC_Data[i]=ADC_Data[i]/10;
			}
			if(ADC_Data[6]<2700||ADC_Data[7]<2700)
			{
				GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			}
			else
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_12);
			}

			data[0]=0xaa;
			data[29]=0x55;
			
			for(i=0;i<14;i++)
			{
				data[2*i+1]=ADC_Data[i]>>8;
				data[2*i+2]=ADC_Data[i];
			}
			for(i=0; i<30; i++)
			{
				USART_SendData(USART3,data[i]);
				while((USART3->SR&0x40)==0)
				{
				}	
			}
		}

    }
}



float angle[3];
u8 angle_data_recive[3][3];
u8 angle_data_recive_count,angle_data_recive_flag;
void USART1_IRQHandler(void) //
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) //
    {
        USART_SendData(USART2,USART_ReceiveData(USART1));

    }
    USART_ClearFlag(USART1, USART_IT_RXNE); //
}
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {   USART_SendData(USART1,USART_ReceiveData(USART2));
        //USART_SendData(USART3,USART_ReceiveData(USART2));
    }
    USART_ClearFlag(USART2, USART_IT_RXNE);
}

void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
		USART_SendData(USART3,USART_ReceiveData(USART3));
    }
    USART_ClearFlag(USART3, USART_IT_RXNE);
}
