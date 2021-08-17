#include "show.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

unsigned char Send_Count; //串口需要发送的数据个数

/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void OLED_Show(void)
{
	
	
//	len1=1000;len2=2000;len3=3000;len4=4000;
//	len5=5000;len6=6000;len7=7000;len8=8000;
	//=============第一行显示len1—len4=======================//
	OLED_ShowNumber(00,0,len1,4,12);
	OLED_ShowNumber(32,0,len2,4,12);
	OLED_ShowNumber(64,0,len3,4,12);
	OLED_ShowNumber(96,0,len4,4,12);
	//=============第二行显示len5—len8=======================//
	OLED_ShowNumber(00,10,len5,4,12);
	OLED_ShowNumber(32,10,len6,4,12);
	OLED_ShowNumber(64,10,len7,4,12);
	OLED_ShowNumber(96,10,len8,4,12);
    //=============第三行显示编码器1=======================//
    OLED_ShowString(00,20,"ENL");
    if( Encoder_Left<0)		OLED_ShowString(25,20,"-"),
							OLED_ShowNumber(37,20,-Encoder_Left,3,12);
    else                 	OLED_ShowString(25,20,"+"),
                            OLED_ShowNumber(37,20, Encoder_Left,3,12);
    //=============第三行显示编码器2=======================//
    OLED_ShowString(64+00,20,"ENR");
    if(Encoder_Right<0)		OLED_ShowString(64+25,20,"-"),
							OLED_ShowNumber(64+37,20,-Encoder_Right,3,12);
    else               		OLED_ShowString(64+25,20,"+"),
                            OLED_ShowNumber(64+37,20,Encoder_Right,3,12);
	
    //=============第四行显示PWM左=======================//
    OLED_ShowString(00,30,"L");
    if(PWML<0)		OLED_ShowString(13,30,"-"),
					OLED_ShowNumber(31,30,-PWML,4,12);
    else            OLED_ShowString(13,30,"+"),
                    OLED_ShowNumber(31,30,PWML,4,12);
    //=============第四行显示PWM右=======================//
    OLED_ShowString(64+00,30,"R");
    if(PWMR<0)		OLED_ShowString(64+13,30,"-"),
					OLED_ShowNumber(64+31,30,-PWMR,4,12);
    else            OLED_ShowString(64+13,30,"+"),
                    OLED_ShowNumber(64+31,30,PWMR,4,12);
    //=============第五行显示角度=======================//
    OLED_ShowString(0,40,"P");
	OLED_ShowNumber(0+16,40,PITCH/100,3,12);
    OLED_ShowString(42,40,"R");
	OLED_ShowNumber(42+16,40,ROLL/100,3,12);
    OLED_ShowString(85,40,"Y");
	OLED_ShowNumber(85+16,40,YAW/100,3,12);
	//=============第六行显示灰度=======================//
	OLED_ShowNumber(00,50,Gray_Left,4,12);
	OLED_ShowNumber(40,50,Gray_Mid,4,12);
	OLED_ShowNumber(80,50,Gray_Right,4,12);

    //=============刷新=======================//
    OLED_Refresh_Gram();
}

