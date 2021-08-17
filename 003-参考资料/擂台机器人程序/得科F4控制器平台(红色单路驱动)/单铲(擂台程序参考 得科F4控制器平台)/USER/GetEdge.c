#include "lcd.h"
#include "pwm.h"
#include "sensor.h"
#include <stdarg.h>
#include <stdio.h>
#include "codelib.h"

# define AI analog
# define DI digital
# define TimeGo start_time
# define TimeStop stop_time
# define ResetTime reset_time

/*	数字量红外开关-红外开关前后左右0~3-正常1100-0011
		模拟量红外测距-从右开始逆时针0~11
		灰度传感器-12*/

/**********************宏定义********************/
# define F_G_R			AI(4)>1150				//作为长距离检测?
# define FF_G_R			AI(3)>1300 || AI(4)>1300 || AI(5)>1300
# define AF_G_R			AI(3)>1300 && AI(4)>1300 && AI(5)>1300
# define FL_G_R			AI(4)>1600 && AI(5)>1600 && AI(3)<1000  		// 2/3! 左前检测到敌人
# define FR_G_R			AI(4)>1600 && AI(3)>1600 && AI(5)<1000			// 2/3! 右前检测到敌人
# define NF_G_R			AI(3)<1100 && AI(4)<1100 && AI(5)<1100			//all not! 前检测到nothing

# define L_G_R			AI(6)>1100		// 左前45°检测到敌人
# define R_G_R			AI(2)>1100		// 右前45°检测到敌人

# define L90_G_R		AI(7)>1100		// 左前90°检测到敌人
# define R90_G_R		AI(1)>1100		// 右前90°检测到敌人
# define BLX_G_R		AI(8)>1100
# define BRX_G_R		AI(0)>1100
# define BL_G_R			AI(9)>1000
# define BR_G_R			AI(11)>1000
# define B_G_R			AI(10)>1100	// 后检测到敌人

/*** PriorityLevel - '3' ***/
# define F_G_E			DI(1)==1 || DI(2)==1			// 前铲出擂台
# define LF_G_E			DI(1)==1 && DI(2)==0			// 前铲左方出擂台
# define RF_G_E			DI(1)==0 && DI(2)==1			// 前铲右方出擂台
# define F1_G_E    (DI(1)==1 && DI(2)==0) || (DI(0)==0 && DI(1)==1	// 
/******/

/*** PriorityLevel - '2' ***/
# define B_G_E			DI(3)==1 || DI(4)==1			// random one behind side
# define BL_G_E			(DI(3)==1 && DI(4)==0) && (DI(0)==1&& DI(1)==1)	// left behind side get edge
# define BR_G_E			(DI(3)==0 && DI(4)==1) && (DI(0)==1&& DI(1)==1)		// right behind side get edge
# define B1_G_E    (DI(3)==0 && DI(4)==1) || (DI(2)==1 && DI(3)==0)	// only one behind side get edge
/******/

/*** PriorityLevel - '1' -TheSupremeLevel***/
# define FBL_G_E   DI(1)==0 && DI(3)==1 		// left whole side get edge
# define FBR_G_E   DI(2)==0 && DI(4)==1 		// right whole side get edge
/******/

# define BY        AI(12)>

/***# define WX_F      DI(0)<300||DI(1)<300***/

# define kaishi    AI(1)<1500

/***铲被侧向抬起***/
/*9-500-46cm*/
# define CAUTION_L			(DI(1)==0 && DI(2)==0) && (AI(6)>2600 || AI(5)>2600 || AI(4)>2600) /*&& AI(9)<500		/*&&(AI(16)<600&&AI(18)<600)*/
# define CAUTION_R			(DI(1)==0 && DI(2)==0) && (AI(2)>2600 || AI(3)>2600 || AI(4)>2600) /*&& AI(9)<500	/*铲被抬起&&右侧检测到敌人&&灰度500区域*/	/*&&(AI(16)<600&&AI(18)<600)*/
# define DANGEROUS			(DI(1)==0 && DI(2)==0) && (DI(3)==1 && DI(4)==1)								/*未用*//*铲被抬起&&后检测到边缘*/


u16 mseconds(void);
/***************************************边沿行为函数**********************************/

extern void E_Back(){
	reset_time();
	while(1){
		GoodMoto(-400,-400);
		if((mseconds()>750)||BLX_G_R||BRX_G_R||BL_G_R||BR_G_R||B_G_R||B_G_E)	break;
	}	
}

extern void E_Foward(){
	ResetTime();
	while(1){
		GoodMoto(400,400);	
		if((mseconds()>750)||FF_G_R||L_G_R||R_G_R||F_G_E)	break;		//L90_G_R||R90_G_R
	}	
}

extern void E_135(){
	ResetTime();
	while(1){	
		if((mseconds()>650)||FF_G_R||BR_G_E||F_G_E)	break;
		GoodMoto(300,-300);
	}
}

extern void E_Stop(void){
    ResetTime();
	while(1){	
		if(mseconds()>100)	break;
		GoodMoto(0,0);
		}
}

extern void URGENT_L(void){ 
	ResetTime();
	while(1){
		if((mseconds()>440)||B_G_E)	break;
		GoodMoto(350,600);
	}
	/*ResetTime();
	while(1){
		if((seconds()>0.24)||B_G_E)		break;
		GoodMoto(-60,-60);
	}*/
}

extern void URGENT_R(void){ 
	ResetTime();
	while(1){
		if((mseconds()>440)||B_G_E)	break;
		GoodMoto(60,35);
	}
	/*ResetTime();
	while(1){
		if((seconds()>0.24)||B_G_E)		break;
		GoodMoto(-60,-60);
	}*/
}

/**未用到边沿行为函数
extern void E_Left(){ 
	ResetTime();
	while(1)
	{	if((seconds()>0.15)||F_G_E)break;
		GoodMoto(-10,25); 	
	}
}
extern void E_Right()                                      
{ 
	ResetTime();
	while(1)
	{	if((seconds()>0.15)||F_G_E)break;                 
		GoodMoto(25,-10);
	}
}


extern void E_45(){
	ResetTime();
	while(1){
		if((seconds()>0.24)||F_G_R)	break;
		GoodMoto(-30,30);
	}
}

extern void EL_45(){
	ResetTime();
	while(1){	
		if((mseconds()>300)||B_G_E||F_G_E)	break;
		GoodMoto(-45,45);
	}
}

extern void ER_45(){
	ResetTime();
	while(1){	
		if((mseconds()>300)||B_G_E||F_G_E)	break;
		GoodMoto(45,-45);
	}
}

extern void E_LFoward(){
	ResetTime();
	while(1){
		GoodMoto(40,50);
		if((mseconds()>450)||FF_G_R||L_G_R||R_G_R||L90_G_R||R90_G_R||BLX_G_R||BRX_G_R||F_G_E)	break;
	}	
}

extern void E_RFoward(){
	ResetTime();
	while(1){
		GoodMoto(50,40);
		if((mseconds()>450)||FF_G_R||L_G_R||R_G_R||L90_G_R||R90_G_R||BLX_G_R||BRX_G_R||F_G_E)	break;
	}	
}
**/

/****		GetEdge()!!!!		****/
extern void GetEdge(){

/***陷入角落-紧急处理***/
	/*if(FBL_G_E){
	     ER_45();
	     E_Foward(); 
	     }
 	else if(FBR_G_E){
	     EL_45(); 
	     E_Foward();
	     }
	*/
	     
/***铲被侧向抬起-紧急处理***/
	/*if(CAUTION_L){
		URGENT_L();
	}
	else if(CAUTION_R){
		URGENT_R();
	}
	*/
	
/*****正常巡台*****/
	if(F_G_E){
		//E_Stop();
		E_Back();
		E_135();
	}								

	/***多余处理
	else if(F1_G_E){
		E_Back();
		E_135();
	}
	
	else if(LB_G_E){

		E_LFoward();
		E_135();
	}
	
	else if(RB_G_E){

		E_RFoward();
		E_135();
	}
	***/
	
	else if(B_G_E){
		E_Foward();
		E_135();
	}	
	/*else if(BY){
		GoodMoto(35,35);
		}*/
	else{                                                         //以上情况均没发生--直走
		GoodMoto(300,300);
	}
}