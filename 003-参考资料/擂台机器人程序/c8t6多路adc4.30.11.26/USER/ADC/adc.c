 #include "./adc/adc.h"
 #include "delay.h"			
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}	


void ADC_DMA_Multichannel_Init(u32 ADC_Buff) {
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
	
    //??DMA1??
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);      
  
		//???IO 
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_15;        
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;        
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
 
    //??DMA1 ??1 ADC
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//ADC?????
    DMA_InitStructure.DMA_MemoryBaseAddr  = ADC_Buff;//?????
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//?????
    DMA_InitStructure.DMA_BufferSize = 14;//????
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//????????
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//????????
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//16?? 12?ADC
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//16??
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//????
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;//????
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//?????????
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//???DMA1 ??1
    DMA_Cmd(DMA1_Channel1, ENABLE);//??DMA ??1
 
    ADC_DeInit(ADC1);//??ADC1
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//????
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; //???? ????? 
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //?????? ???? ????
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//??????
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//?????
    ADC_InitStructure.ADC_NbrOfChannel = 14;//??3???
    ADC_Init(ADC1, &ADC_InitStructure);//???ADC
		
		//ADC?? ????14MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72/6 = 12MHz 
		//????ADC????,??????
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 14, ADC_SampleTime_239Cycles5);
    //??ADC DMA
	ADC_DMACmd(ADC1, ENABLE);
		//??ADC
    ADC_Cmd(ADC1, ENABLE);
		
	ADC_ResetCalibration(ADC1);//???????  
    while(ADC_GetResetCalibrationStatus(ADC1));//???????????  
  
    ADC_StartCalibration(ADC1);//ADC??  
    while(ADC_GetCalibrationStatus(ADC1));//??????  
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//??????????,????????ADC?? 
		
}


//获得ADC值
//ch:通道值 0~3
u16 Get_Adc1(void)   
{
	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
//		adcx=ADC_GetConversionValue(ADC1);
//		temp=(float)adcx*(3.3/4096);

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
u16 Get_Adc2(void)   
{
	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
//		adcx=ADC_GetConversionValue(ADC1);
//		temp=(float)adcx*(3.3/4096);

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
u16 Get_Adc3(void)   
{
	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
//		adcx=ADC_GetConversionValue(ADC1);
//		temp=(float)adcx*(3.3/4096);

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
u16 Get_Adc4(void)   
{
	
		ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5 );
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
//		adcx=ADC_GetConversionValue(ADC1);
//		temp=(float)adcx*(3.3/4096);

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
//u16 Get_Adc_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc();
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 



























