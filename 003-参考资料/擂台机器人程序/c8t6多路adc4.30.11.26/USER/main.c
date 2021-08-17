#include "stm32f10x.h"
#include "delay.h"
#include "timer.h"
#include "lcd.h"
#include "window.h"
#include "mpu9250.h"
#include "timer.h"
#include "usart.h"
#include "steer.h"
#include "dac.h"
#include "interrupt.h"
#include "./GPIO/GPIO.h"
#include "./adc/adc.h"


u16 ADC_BUFF[14];

int main(void)
{

    delay_init();
	  uart1_init(115200);
	  uart3_init(115200);
//    GPIO_IN_Init();
    ADC_DMA_Multichannel_Init((u32)ADC_BUFF);

    TIM3_Config();
    TIM_Cmd(TIM3,ENABLE);
	
    while(1)
    {
//        for(u8 i=0; i<4; i++)
//        {
//            USART_SendData(USART3,ADC_BUFF[i]);
//            while((USART3->SR&0x40)==0)
//            {
//            }
//			
//        }

	}
}


