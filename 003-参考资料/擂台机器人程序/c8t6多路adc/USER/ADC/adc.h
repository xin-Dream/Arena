#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
void ADC_DMA_Multichannel_Init(u32 ADC_Buff);
void Adc_Init(void);
u16  Get_Adc1(void); 
u16  Get_Adc2(void); 
u16  Get_Adc3(void); 
u16  Get_Adc4(void); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
#endif 
