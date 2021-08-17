#include "show.h"
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

unsigned char Send_Count; //������Ҫ���͵����ݸ���

/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void OLED_Show(void)
{
	
	
//	len1=1000;len2=2000;len3=3000;len4=4000;
//	len5=5000;len6=6000;len7=7000;len8=8000;
	//=============��һ����ʾlen1��len4=======================//
	OLED_ShowNumber(00,0,len1,4,12);
	OLED_ShowNumber(32,0,len2,4,12);
	OLED_ShowNumber(64,0,len3,4,12);
	OLED_ShowNumber(96,0,len4,4,12);
	//=============�ڶ�����ʾlen5��len8=======================//
	OLED_ShowNumber(00,10,len5,4,12);
	OLED_ShowNumber(32,10,len6,4,12);
	OLED_ShowNumber(64,10,len7,4,12);
	OLED_ShowNumber(96,10,len8,4,12);
    //=============��������ʾ������1=======================//
    OLED_ShowString(00,20,"ENL");
    if( Encoder_Left<0)		OLED_ShowString(25,20,"-"),
							OLED_ShowNumber(37,20,-Encoder_Left,3,12);
    else                 	OLED_ShowString(25,20,"+"),
                            OLED_ShowNumber(37,20, Encoder_Left,3,12);
    //=============��������ʾ������2=======================//
    OLED_ShowString(64+00,20,"ENR");
    if(Encoder_Right<0)		OLED_ShowString(64+25,20,"-"),
							OLED_ShowNumber(64+37,20,-Encoder_Right,3,12);
    else               		OLED_ShowString(64+25,20,"+"),
                            OLED_ShowNumber(64+37,20,Encoder_Right,3,12);
	
    //=============��������ʾPWM��=======================//
    OLED_ShowString(00,30,"L");
    if(PWML<0)		OLED_ShowString(13,30,"-"),
					OLED_ShowNumber(31,30,-PWML,4,12);
    else            OLED_ShowString(13,30,"+"),
                    OLED_ShowNumber(31,30,PWML,4,12);
    //=============��������ʾPWM��=======================//
    OLED_ShowString(64+00,30,"R");
    if(PWMR<0)		OLED_ShowString(64+13,30,"-"),
					OLED_ShowNumber(64+31,30,-PWMR,4,12);
    else            OLED_ShowString(64+13,30,"+"),
                    OLED_ShowNumber(64+31,30,PWMR,4,12);
    //=============��������ʾ�Ƕ�=======================//
    OLED_ShowString(0,40,"P");
	OLED_ShowNumber(0+16,40,PITCH/100,3,12);
    OLED_ShowString(42,40,"R");
	OLED_ShowNumber(42+16,40,ROLL/100,3,12);
    OLED_ShowString(85,40,"Y");
	OLED_ShowNumber(85+16,40,YAW/100,3,12);
	//=============��������ʾ�Ҷ�=======================//
	OLED_ShowNumber(00,50,Gray_Left,4,12);
	OLED_ShowNumber(40,50,Gray_Mid,4,12);
	OLED_ShowNumber(80,50,Gray_Right,4,12);

    //=============ˢ��=======================//
    OLED_Refresh_Gram();
}

