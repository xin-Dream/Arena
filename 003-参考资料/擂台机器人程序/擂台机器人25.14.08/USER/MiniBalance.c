#include "stm32f10x.h"
#include "sys.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int PWML=0,PWMR=0;                              //电机PWM变量
int Voltage;                                //电池电压采样相关的变量
u16 YAW,PITCH,ROLL;							//航向，俯仰，横滚
u32 len1,len2,len3,len4,len5,len6,len7,len8;//八个长度
u16 ADC_BUFF[4];
extern u8 qidong;
int main(void)
{

    delay_init();	    	        //=====延时函数初始化
    uart2_init(115200);				//=====串口2初始化
    uart3_init(115200);             //=====串口3初始化
    JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
    JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
    LED_Init();                     //=====初始化与 LED 连接的硬件接口
    MY_NVIC_PriorityGroupConfig(2);	//=====中断优先级分组
    MiniBalance_PWM_Init(104,71);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口
    Encoder_Init_TIM2();            //=====编码器接口
    Encoder_Init_TIM4();            //=====初始化编码器2
    TIM3_Config();
	ADC_DMA_Multichannel_Init((u32)ADC_BUFF);
    OLED_Init();                    //=====OLED初始化
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

