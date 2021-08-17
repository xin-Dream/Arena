#include "stm32f10x.h"
#include "sys.h"
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int PWML=0,PWMR=0;                              //���PWM����
int Voltage;                                //��ص�ѹ������صı���
u16 YAW,PITCH,ROLL;							//���򣬸��������
u32 len1,len2,len3,len4,len5,len6,len7,len8;//�˸�����
u16 ADC_BUFF[4];
extern u8 qidong;
int main(void)
{

    delay_init();	    	        //=====��ʱ������ʼ��
    uart2_init(115200);				//=====����2��ʼ��
    uart3_init(115200);             //=====����3��ʼ��
    JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
    JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
    LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
    MY_NVIC_PriorityGroupConfig(2);	//=====�ж����ȼ�����
    MiniBalance_PWM_Init(104,71);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ�
    Encoder_Init_TIM2();            //=====�������ӿ�
    Encoder_Init_TIM4();            //=====��ʼ��������2
    TIM3_Config();
	ADC_DMA_Multichannel_Init((u32)ADC_BUFF);
    OLED_Init();                    //=====OLED��ʼ��
    OLED_Clear();
    OLED_Show();

	IMU_init();
	dengtai();

//	EXTIX_Init();
//	SWI_Init();
	
	TIM_Cmd(TIM3,ENABLE);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	delay_ms(500);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	
//    Start_untouch();
    while(1)
    {


		OLED_Show();
		

	}
}

