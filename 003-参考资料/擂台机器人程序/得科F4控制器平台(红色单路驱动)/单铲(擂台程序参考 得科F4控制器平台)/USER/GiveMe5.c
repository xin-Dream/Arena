#include <stdarg.h>
#include <stdio.h>
#include "codelib.h"
#include "beep.h" 
#include "key.h"
#include "delay.h" 
#include "lcd.h"
#include "led.h" 
#include "timer.h"
#include "sensor.h"
#include "pwm.h"
#include "servor_bc.h"
#include "usart.h"

//F-Foward B-Behind L-Left	R-Right		sum=1	-*4号传感器比其他大50*- -1550-40cm-1050-70cm-
#define F		A2>1050 || A3>1050 || A4>1100		
#define sF	A2>1550 || A3>1550 || A4>1600		//前方任意一个检测到
#define FL	A2>1050 && A3>1050 && A4<900
#define sFL	A2>1550 && A3>1550 && A4<900		//左前方检测到
#define FR	A2<900  && A3>1050 && A4>1050
#define sFR	A2<900  && A3>1550 && A4>1550		//右前方检测到
#define L		A2>1050 && A3<900  && A4<900
#define sL	A2>1550 && A3<900  && A4<900		//偏左方检测到
#define R		A2<900  && A3<900  && A4>1050
#define sR	A2<900  && A3<900  && A4>15500	//偏右方检测到
#define L45		AI(1)>1050
#define sL45	AI(1)>1550		//左45度检测到
#define R45		AI(5)>1050
#define sR45	AI(5)>1550		//右45度检测到
#define L90		AI(0)>1050
#define sL90	AI(0)>1550		//左90度检测到
#define R90		AI(6)>1050
#define sR90	AI(6)>1550		//右90度检测到
#define B			AI(12)>1050
#define sB		AI(12)>1550		//正后方检测到
#define BL	AI(9)>1050
#define sBL	AI(9)>1550			//左后方检测到
#define BR	AI(7)>1050
#define sBR	AI(7)>1550			//右后方检测到

//E-Edge	sum=0
#define FE	DI(0)==0 || DI(1)==0	//前方出擂台
#define BE	DI(2)==1 || DI(3)==1	//后方出擂台

#define BY	AI(10)>2500
#define sBY	AI(10)>2400
#define Centre	AI(10)<2000				//小车在中央
#define	Around	AI(10)>2200				//小车在距台边20+cm的地方和红色区域

//S-stage	sum=2
#define FS	(AI(3)>2000 && AI(12)>2000 && abs(AI(2)-AI(4))<250 && DI(0)==1 && (AI(0)<1300 && AI(6)<1300))		// 前正对擂台
#define BS	(AI(3)>2000 && AI(12)>2000 && abs(AI(2)-AI(4))<250&& DI(0)==0 && (AI(0)<1300 && AI(6)<1300))		// 后正对擂台
#define LRS	(AI(0)>2000 && AI(6)>2000 && AI(12)<1300 && AI(3)<1300 && AI(2)<11100 && AI(4)<1100 && DI(0)==1)// 左右正对擂台
// 判断条件再检测、优化
// 利用上灰度？

//F-fence	sum=2
#define FLF	(AI(3)>2200 && abs(AI(2)-AI(4))<250 && DI(0)==0 && AI(0)>2300 && AI(6)<900 && AI(12)<900)		// 前左正对围栏
#define FRF	(AI(3)>2200 && abs(AI(2)-AI(4))<250 && DI(0)==0 && AI(0)<900 && AI(6)>2300 && AI(12)<900)		// 前右正对围栏
#define BLF	(AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(0)==1 && AI(0)>2300 && AI(6)<900 && AI(12)>2000)	// 后左正对围栏
#define BRF	(AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(0)==1 && AI(0)<900 && AI(6)>2300 && AI(12)>2000)	// 后右正对围栏

#define FLLF	(AI(3)>2000 /*&& AI(12)>2000*/ && AI(0)>2000 && AI(6)<900 && (AI(7)>2000 && AI(9)<1100) && DI(0)==0)		//前左对围栏，但比较远
#define FRRF	(AI(3)>2000 /*&& AI(12)>2000*/ && AI(0)<900 && AI(6)>2000 && (AI(7)<1100 && AI(9)>2000) && DI(0)==0)		//前右对围栏，但比较远
#define	BLLF	(AI(3)>2000 /*&& AI(12)>2000*/ && AI(0)>2000 && AI(6)<1100 && (AI(1)<1100 && AI(5)>2000) && DI(1)==0)		//后左对围栏，但比较远
#define BRRF	(AI(3)>2000 /*&& AI(12)>2000*/ && AI(0)<1100 && AI(6)>2000 && (AI(1)>2000 && AI(5)<1100) && DI(1)==0)		//后右对围栏，但比较远

#define FLXF	AI(7)>2000 && AI(9)<1100 && AI(6)<1000
#define FRXF	AI(7)<1100 && AI(9)>2000 && AI(0)<1000

//同时检测到三个“敌人”	sum=3	-在台下检测到敌人后退 -朝后、朝右的漫反射红外开关？ -？此处判断有必要加上漫反射红外开关？
#define FLR	AI(3)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==0 && AI(8)<900	//前左围栏右敌人（后无右无）、前右围栏左敌人（后无右有）、左右擂台前敌人（后无右无）
#define BLR	AI(8)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==1 && AI(3)<900	//后左围栏右敌人（后有右无）、后右围栏左敌人（后有友有）、左右擂台后敌人（后无右无）
#define FBL	AI(3)>1800 && AI(8)>1800 && AI(0)>1800 && AI(6)<900 && DI(4)==1	//前左围栏后敌人（后有右无）、后左围栏前敌人（后有右无）、前后擂台左敌人（后有右无）
#define FBR	AI(3)>1800 && AI(8)>1800 && AI(6)>1800 && AI(0)<900 && DI(4)==1	//前右围栏后敌人（后无右有）、后右围栏前敌人（后无右有）、前后擂台右敌人（后有右无）

// 斜在角落		sum=4


#define AI analog
#define DI digital
#define ResetTime	reset_time
#define ServoSetMode	UP_CDS_SetMode	//设置舵机工作方式				
#define ServoSetAngle	UP_CDS_SetAngle	//舵机调速
#define CDS_SEVMODE			0			
#define CDS_MOTOMODE		1			
#define GrayNum					3


void GetEdge(void);
void GetRobot(void);
void Up2Stage(void);
u16 getseconds(void);
void GoodMoto(int lspeed,int rspeed);
void ADReturnOnStage(void);

u16 A[14]={0};
u8 D[6]={0};
u16 A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13;
u8 D0,D1,D2,D3,D4;
u8 nstage = 0;
u32 nBY = 0;
u8 j = 0;

u8 Stage(void){
	u8 EnemyNum	= 0;		//	记录“敌人”的数量
	ADReturnOnStage();
	if(F||L45||R45)	EnemyNum++;	
	if(L90)	EnemyNum++;
	if(R90)	EnemyNum++;
	if(B||BL||BR)	EnemyNum++;
	
	if(EnemyNum>2)	return 1;			// 在台上
	else						return 0;			// 在台下
}

void GiveMe5(void){
	for(j=0;j<GrayNum;j++)	nBY+=AI(10);
	nBY /= GrayNum;				//记录灰度值
	if(nBY<2000){
		GetRobot();
	}
	else {
		nstage = Stage();
		switch(nstage){
			case 0:	
				GetEdge();
				GetRobot();
				break;
			case 1: 
				//GetStage();
				break;
		}
	}
}

void ADReturnOnStage(void){
	A2 = AI(2);
	A3 = AI(3);
	A4 = AI(4);
}

void ADReturnUnderStage(void){
	A0 = AI(0);
	//A1 = AI(1);
	A2 = AI(2);
	A3 = AI(3);
	A4 = AI(4);
	A6 = AI(6);
	//A7 = AI(7);
	A8 = AI(8);
	//A9 = AI(9);
}

void ADReturn(u8 *temp,u8 num){
	u8 i;
	for(j=0;j<num;j++){
		A[temp[i]] = AI(i);
	}
}

void Up2Stage(void){
	ServoSetMode(1,CDS_SEVMODE);
	ServoSetAngle(1,1000,800);
	display_GB2312_string(0,1,"3");
	delay_ms(1000);
	display_GB2312_string(0,1,"2");
	delay_ms(1000);
	display_GB2312_string(0,1,"1");
	delay_ms(1000);
	GoodMoto(300,300);
	ServoSetAngle(1,680,1023);
	delay_ms(500);
	ServoSetAngle(1,600,1023);
	delay_ms(700);
	ServoSetAngle(1,1000,800);
	delay_ms(500);
	
	GoodMoto(0,0);
	display_GB2312_string(0,1,"Done!");
	while(1);
}
