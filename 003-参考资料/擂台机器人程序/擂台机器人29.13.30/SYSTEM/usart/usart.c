#include "sys.h"
#include "usart.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
_sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
//	USART_ClearFlag(USART3,USART_FLAG_TC);
    while((USART3->SR&0X40)==0);//Flag_Show=0  使用串口3
    USART3->DR = (u8) ch;
    return ch;
}
#endif
void uart1_init(u32 bound) {
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    //USART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10
    //USART 初始化设置

    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

    USART_InitStructure.USART_BaudRate = bound;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1

}



void uart2_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    //时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA,D时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟

    //GPIO端口设置
    //TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	           //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //复用推挽
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);      //复位串口2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);     //停止复位

    USART_InitStructure.USART_BaudRate = bound;                  //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8位数据长度
    USART_InitStructure.USART_StopBits = USART_StopBits_1;       //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;          ///奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式

    USART_Init(USART2, &USART_InitStructure);                //初始化串口
    USART_ClearFlag(USART2,USART_FLAG_TC);

    //中断
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级2级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断

    USART_Cmd(USART2, ENABLE);                    //使能串口
}


/**************************************************************************
函数功能：串口3初始化
入口参数： bound:波特率
返回  值：无
**************************************************************************/

void uart3_init(u32 bound)
{
	
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能UGPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
    //USART3_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART3_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART3, &USART_InitStructure);     //初始化串口3
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART3, ENABLE);                    //使能串口3
}

/**************************************************************************
函数功能：串口1接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART1_IRQHandler(void)
{
    u8 data;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收到数据
    {
        USART_ClearFlag(USART1,USART_IT_RXNE);
        data=USART_ReceiveData(USART1);
        USART_SendData(USART3,data);

    }
}

/**************************************************************************
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void)
{
    static u8 data[18];
    u8 i;
	    if(USART_GetITStatus(USART2, USART_FLAG_ORE) != RESET) //接收到数据
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);
	}
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收到数据
    {
        USART_ClearFlag(USART2,USART_IT_RXNE);
		
        data[17]=USART_ReceiveData(USART2);
        if (data[0]==0xaa&&data[17]==0x55)
        {
			len1=data[1]<<8|data[2];
			len2=data[3]<<8|data[4];
			len3=data[5]<<8|data[6];
			len4=data[7]<<8|data[8];
			len5=data[9]<<8|data[10];
			len6=data[11]<<8|data[12];
			len7=data[13]<<8|data[14];
			len8=data[15]<<8|data[16];
			
//		if(Len_Edge_Left<2700)
//		{
//			Set_Speed_Show(-BASIC,-BASIC);
//			delay_ms(200);
//			Set_Speed_Show(BASIC,-BASIC);
//			delay_ms(200);
//		}
//		if(Len_Edge_Right<2700)
//		{
//			Set_Speed_Show(-BASIC,-BASIC);
//			delay_ms(200);
//			Set_Speed_Show(-BASIC,BASIC);
//			delay_ms(200);

//		}		

        }

        for(i=0; i<17; i++)
        {
            data[i]=data[i+1];
        }

    }
}

/**************************************************************************
函数功能：串口3接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART3_IRQHandler(void)
{
	u8 k;
	static u8 rebuf[8];
//	if(USART_GetITStatus(USART2, USART_FLAG_ORE) != RESET) //接收到数据
//	{
//		USART_ClearFlag(USART2,USART_FLAG_ORE);
//	}
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		
		rebuf[0] =USART_ReceiveData(USART3);	//读取接收到的数据					
		if(rebuf[0]==0x55&&rebuf[7]==0xaa)
		{
			YAW=(rebuf[6]<<8|rebuf[5]);
			ROLL=(rebuf[4]<<8|rebuf[3]);
			PITCH=(rebuf[2]<<8|rebuf[1]);
			
			if(YAW>18000)
				YAW=36000-(65535-YAW);
			if(PITCH>18000)
				PITCH=36000-(65535-PITCH);
			if(ROLL>18000)
				ROLL=36000-(65535-ROLL);			

		}
		 
		for(k=7;k>0;k--)
			rebuf[k]=rebuf[k-1];		
		

	}
	USART_ClearFlag(USART3, USART_IT_RXNE);
}


void IMU_init(void)
{
	while((USART3->SR&0x40)==0){}
	USART_SendData(USART3,0xa5);while((USART3->SR&0x40)==0){}
	USART_SendData(USART3,0x52);while((USART3->SR&0x40)==0){}

	USART_SendData(USART3,0xa5);while((USART3->SR&0x40)==0){}
	USART_SendData(USART3,0x55);while((USART3->SR&0x40)==0){}

	USART_SendData(USART3,0xa5);while((USART3->SR&0x40)==0){}
	USART_SendData(USART3,0x54);while((USART3->SR&0x40)==0){}

	USART_SendData(USART3,0xa5);while((USART3->SR&0x40)==0){}
	USART_SendData(USART3,0x52);while((USART3->SR&0x40)==0){}

}
