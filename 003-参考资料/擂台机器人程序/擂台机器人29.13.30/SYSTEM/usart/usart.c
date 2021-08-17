#include "sys.h"
#include "usart.h"
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;

};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
_sys_exit(int x)
{
    x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
//	USART_ClearFlag(USART3,USART_FLAG_TC);
    while((USART3->SR&0X40)==0);//Flag_Show=0  ʹ�ô���3
    USART3->DR = (u8) ch;
    return ch;
}
#endif
void uart1_init(u32 bound) {
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10
    //USART ��ʼ������

    //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1

}



void uart2_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    //ʱ��ʹ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOA,Dʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

    //GPIO�˿�����
    //TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	           //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             //PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);      //��λ����2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);     //ֹͣ��λ

    USART_InitStructure.USART_BaudRate = bound;                  //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ���ݳ���
    USART_InitStructure.USART_StopBits = USART_StopBits_1;       //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;          ///��żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure);                //��ʼ������
    USART_ClearFlag(USART2,USART_FLAG_TC);

    //�ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�

    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
}


/**************************************************************************
�������ܣ�����3��ʼ��
��ڲ����� bound:������
����  ֵ����
**************************************************************************/

void uart3_init(u32 bound)
{
	
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��UGPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
    //USART3_TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART3_RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure);     //��ʼ������3
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3
}

/**************************************************************************
�������ܣ�����1�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART1_IRQHandler(void)
{
    u8 data;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //���յ�����
    {
        USART_ClearFlag(USART1,USART_IT_RXNE);
        data=USART_ReceiveData(USART1);
        USART_SendData(USART3,data);

    }
}

/**************************************************************************
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void)
{
    static u8 data[18];
    u8 i;
	    if(USART_GetITStatus(USART2, USART_FLAG_ORE) != RESET) //���յ�����
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);
	}
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
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
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART3_IRQHandler(void)
{
	u8 k;
	static u8 rebuf[8];
//	if(USART_GetITStatus(USART2, USART_FLAG_ORE) != RESET) //���յ�����
//	{
//		USART_ClearFlag(USART2,USART_FLAG_ORE);
//	}
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		
		rebuf[0] =USART_ReceiveData(USART3);	//��ȡ���յ�������					
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
