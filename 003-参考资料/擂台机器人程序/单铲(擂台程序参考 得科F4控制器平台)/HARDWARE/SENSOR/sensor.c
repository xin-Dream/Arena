#include "sensor.h"
#define a 0.8 //滤波参数 0-1 

volatile vu16  AD_Value[M];   //用来存放ADC转换结果，也是DMA的目标地址
//volatile vu16  After_filter[M];    //用来存放求平均值之后的结果
u16  After_filter[16]={0},last_filter[16]={0};
void SENSOR_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA1时钟使能

	//模拟口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;//PA5 通道5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//PA5 通道5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//PA5 通道5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 


	//数字口配置
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15 ; //8路灰度传感器
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOE2,3,4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //8路灰度传感器
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;//8路灰度传感器
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
	

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	
	
	//DMA设置  
    //DMA通道配置  
    DMA_DeInit(DMA2_Stream0);  
    DMA_InitStructure.DMA_Channel = DMA_Channel_0;   
    //外设地址  
    DMA_InitStructure.DMA_PeripheralBaseAddr = ((u32)ADC1+0x4c);  //(uint32_t)(&ADC1->DR)
    //内存地址  
    DMA_InitStructure.DMA_Memory0BaseAddr =(u32)&AD_Value;  //DMA内存基地址  
    //dma传输方向  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  
    //设置DMA在传输时缓冲区的长度  
    DMA_InitStructure.DMA_BufferSize = M;  //DMA通道的DMA缓存的大小	M*N
    //设置DMA的外设递增模式，一个外设  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //设置DMA的内存递增模式  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //外设数据字长  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  
    //内存数据字长  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  
    //设置DMA的传输模式  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
    //设置DMA的优先级别  
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;  
      
    //指定如果FIFO模式或直接模式将用于指定的流:不使能FIFO模式    
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;      
    //指定了FIFO阈值水平  
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;          
    //指定的Burst转移配置内存传输   
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;         
    //指定的Burst转移配置外围转移  
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   
      
    //配置DMA的通道           
    DMA_Init(DMA2_Stream0, &DMA_InitStructure); 
    //使能通道  
    DMA_Cmd(DMA2_Stream0, ENABLE);  	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);    
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE); 
	//初始化ADC  
    ADC_DeInit();  

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_DMAAccessMode =  ADC_DMAAccessMode_Disabled; //DMA失能，//关闭DMA存取  
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 	
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;  //两次采样间隔  
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = M;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	
	  
     
	
	//规则模式通道配置 
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,7, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,8, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,9, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,10, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,11, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,12, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,13, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,14, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,15, ADC_SampleTime_56Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,16, ADC_SampleTime_56Cycles);
	
	//使能ADC的DMA 
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE); //源数据变化时开启DMA传输
	ADC_DMACmd(ADC1,ENABLE);//使能ADC的DMA传输
	 
	//使能ADC1 
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
	
	//开启ADC1的软件转换
	ADC_SoftwareStartConv(ADC1);
	
}

/*求平均值函数*/
//void filter(u8 num)
//{
//	u32  sum = 0;
//	u8  count;    

//	for(count=0;count<N;count++)
//	{
//		sum += AD_Value[num];
//	}
//	After_filter[num]=sum/N;
//	sum=0;
//}

void filter(u8 Channel)   
{  
	u16 new_value,value;	
	last_filter[Channel]=After_filter[Channel];
	value=last_filter[Channel];	
	new_value = AD_Value[Channel];   
	After_filter[Channel]= a*new_value+(1-a)*value; 
 }

u16 analog(u8 port)
{
	u8 num = 0;
	switch(port)
	{
	 	case 0:	  num = 10; break;
		case 1:	  num = 11; break;
	 	case 2:	  num = 12; break;
		case 3:	  num = 13; break;
	 	case 4:	  num = 0; break;
		case 5:	  num = 1; break;
	 	case 6:	  num = 2; break;
		case 7:	  num = 3; break;
	 	case 8:	  num = 4; break;
		case 9:	num = 5; break;
	 	case 10:	num = 6; break;
		case 11:	num = 7; break;
	 	case 12:	num = 14; break;
		case 13:	num = 15; break; 
		case 14:  num = 8; break;
	 	case 15:	num = 9;  break;
	}
	
	filter(num);
	return 	After_filter[num];	 
}

u8 digital(u8 port)
{
	u8 value = 0;
	switch(port) 
	{
		case 0:
			if(PBin(2) == 1) value = 1;
			else value = 0;
			break;
		case 1:
			if(PEin(7) == 1) value = 1;
			else value = 0;
			break;
		case 2:
			if(PEin(8) == 1) value = 1;
			else value = 0;
			break;
		case 3: 
			if(PEin(9) == 1) value = 1;
			else value = 0;
			break;
		case 4: 
			if(PEin(10) == 1) value = 1;
			else value = 0;
			break;
//		case 5:
//			if(PEin(11) == 1) value = 1;
//			else value = 0;
//			break;
		case 6:
			if(PEin(12) == 1) value = 1;
			else value = 0;
			break;
		case 7:
			if(PEin(13) == 1) value = 1;
			else value = 0;
			break;
		case 8:
			if(PEin(14) == 1) value = 1;
			else value = 0;
			break;
		case 9:
			if(PEin(15) == 1) value = 1;
			else value = 0;
			break;
		case 10:
			if(PBin(10) == 1) value = 1;
			else value = 0;
			break;
		case 11:
			if(PBin(11) == 1) value = 1;
			else value = 0;
			break;
		case 12:
			if(PBin(12) == 1) value = 1;
			else value = 0;
			break;
		case 13:
			if(PBin(13) == 1) value = 1;
			else value = 0;
			break;
		case 14:
			if(PBin(14) == 1) value = 1;
			else value = 0;
			break;		
		case 15:
			if(PBin(15) == 1) value = 1;
			else value = 0;
			break;
		case 16:
			if(PDin(8) == 1) value = 1;
			else value = 0;
			break;
		case 17:
			if(PDin(9) == 1) value = 1;
			else value = 0;
			break;
		case 18:
			if(PDin(10) == 1) value = 1;
			else value = 0;
			break;
		case 19:
			if(PAin(15) == 1) value = 1;
			else value = 0;
			break;
		case 20:
			if(PCin(12) == 1) value = 1;
			else value = 0;
			break;
		case 21:
			if(PDin(0) == 1) value = 1;
			else value = 0;
			break;
		case 22:
			if(PDin(1) == 1) value = 1;
			else value = 0;
			break;
		case 23:
			if(PDin(2) == 1) value = 1;
			else value = 0;
			break;
		case 24:
			if(PDin(3) == 1) value = 1;
			else value = 0;
			break;
		case 25:
			if(PDin(4) == 1) value = 1;
			else value = 0;
			break;
	}
	return value;
}



