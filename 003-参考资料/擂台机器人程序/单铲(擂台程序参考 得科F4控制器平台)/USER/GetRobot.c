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
# define JS	LittleCute

unsigned char i =0;


/******���������⿪��-���⿪��ǰ������0~3-����1100-0011
		ģ����������-���ҿ�ʼ��ʱ��0~11
		�Ҷȴ�����-12
******/
		
/**********************************���������*************************************
//��ֵ��ʾ��ͷ����,�� 350+ -> 300+	400+

�����̨��Ե
	#ǰ��-��翪��	7.8
	��̨	1800+ 1600+
	����	75+
	
	#��-������	17.18
	��̨	35+
	����	1450+

�����˾���
	#����-������	0.6
	ADֵ	����0	����6	��ע
	1000+	200		180
 	800+	290		280
 	500+	480		450
 	400+	630		570
 	300+	840		770
 	<100					��ⲻ������
 	
 	#45��-������	1.5
 	ADֵ	����1	����5	��ע
 	1000+	180		170
 	600+	390		380
 	300+	690		670
 	<100					��ⲻ������
 	
 	#ǰ-������	2.3.4
 	ADֵ	����2	����3	����4	��ע
 	*1100							���ӽӴ���Ӧ������ս �� ����һ����������
 	1000+	210		200		150
 	800+	-		-		200
 	600+	400		390		390
 	*350+	610		600		600		�ʺϷ�������ľ���
	
	#��-������	12.13.14
	ADֵ	����12	����13	����14	��ע
	1000+	190		190		170
	800+	270		260		240
	250+	-		-		-		�ɻ�ͷ�������
	
���Ҷȿ���С���ٶ�
	#����-�Ҷ�	9.10
	ADֵ9	ADֵ10	��ע
	800+	400+	����������
	700+	350+	Σ��
	500+	300+	���밲ȫ����
	500+	250+	������������

*********************************************************************************/

/**********************�궨��********************/
# define F_G_E			DI(0)==0 || DI(1)==0			// a forward side or two get edge
# define LF_G_E    DI(0)==0 && DI(1)==1			// left forward side get edge
# define RF_G_E    DI(0)==1 && DI(1)==0			// right forward side get edge
# define F1_G_E    (DI(0)==1 && DI(1)==0) || (DI(0)==0 && DI(1)==1)		// only one forward side get edge

# define B_G_E			DI(2)==1 || DI(3)==1			// random one behind side
# define BL_G_E    (DI(2)==1 && DI(3)==0) && (DI(0)==1&& DI(1)==1)	// left behind side get edge
# define BR_G_E	  (DI(2)==0 && DI(3)==1) && (DI(0)==1&& DI(1)==1)		// right behind side get edge
# define B1_G_E    (DI(2)==0 && DI(3)==1) || (DI(2)==1 && DI(3)==0)	// only one behind side get edge

# define FBL_G_E   DI(0)==0 && DI(2)==1 		// left whole side get edge
# define FBR_G_E   DI(1)==0 && DI(3)==1 		// right whole side get edge

/*** PriorityLevel - '3' ***/
# define F_G_R			AI(4)>1100				//��Ϊ��������? 1050-70cm
# define FF_G_R			AI(3)>1200 || AI(4)>1200 || AI(5)>1200
# define AF_G_R			AI(3)>1300 && AI(4)>1300 && AI(5)>1300
# define AAF_G_R		AI(3)>2400 && AI(4)>2400 && AI(5)>2400
# define FL_G_R			AI(4)>1600 && AI(5)>1600 && AI(3)<1000  		// 2/3! ��ǰ��⵽����
# define FR_G_R			AI(4)>1600 && AI(3)>1600 && AI(5)<1000			// 2/3! ��ǰ��⵽����
# define NF_G_R			AI(3)<1100 && AI(4)<1100 && AI(5)<1100			//all not! ǰ��⵽nothing
# define FLL_G_R		AI(4)<1100 && AI(5)>1700
# define FRR_G_R		AI(4)<1100 && AI(3)>1700
/******/

/*** PriorityLevel - '2' ***/
# define L_G_R			AI(6)>1100		// ��ǰ45���⵽����
# define L90_G_R		AI(7)>1100		// ��ǰ90���⵽����
# define R_G_R			AI(2)>1100		// ��ǰ45���⵽����
# define R90_G_R		AI(1)>1100		// ��ǰ90���⵽����
/******/

/*** PriorityLevel - '1' -TheSupremeLevel***/
# define BL_G_R			AI(9)>1000
# define BR_G_R			AI(11)>1000
# define B_G_R			AI(10)>1100	// ���⵽����
# define BLX_G_R		AI(8)>1100
# define BRX_G_R		AI(0)>1100
# define B45_G_R		AI(9)>1000 || AI(11)>1000
/******/

# define BY
# define kaishi    AI(6)>1300	/*Velocity=70-50*/
# define begin     AI(0)>1300	/*Velocity=80-60*/

/****��ɫ�����ǿ���****/	
# define sBY       	 AI(9)>540   						/*��̨�߾���25cm*/
# define F60_G_R     AI(3)>345||AI(4)>345||AI(2)>345			/*60cm*/
# define L60_G_R     AI(1)>330
# define R60_G_R     AI(10)>310
# define L90_60_G_R  AI(0)>305
# define R90_60_G_R  AI(6)>355
# define LB60_G_R    AI(12)>335
# define RB60_G_R    AI(14)>380
# define B60_G_R     AI(13)>340

/***��������̧��***/
/*9-500-46cm*/
# define CAUTION_L			(DI(0)==0 && DI(1)==0) && (AI(6)>2100 || AI(5)>2100 || AI(4)>2100) /*&& AI(9)<500		/*&&(AI(16)<600&&AI(18)<600)*/
# define CAUTION_R			(DI(0)==0 && DI(1)==0) && (AI(2)>2100 || AI(3)>2100 || AI(4)>2100) /*&& AI(9)<500	/*����̧��&&�Ҳ��⵽����&&�Ҷ�500����*/	/*&&(AI(16)<600&&AI(18)<600)*/
# define DANGEROUS			(DI(0)==0 && DI(1)==0) && (DI(2)==0 && DI(3)==0)								/*δ��*//*����̧��&&���⵽��Ե*/

/***************************************??????************************************/
extern void Afoward(void){
	ResetTime();
	while(1){
		GoodMoto(45,45);
		if(NF_G_R||FLL_G_R||FRR_G_R||F_G_E||B_G_E)	break;
		//GoodMoto(50,50);
	}	
}

extern void LittleCute(void){	//JS
	ResetTime();
	while(1){
		if((mseconds()>600)||NF_G_R||FLL_G_R||FRR_G_R||L_G_R||R_G_R||F_G_E||B_G_E||CAUTION_L||CAUTION_R)		break;
		GoodMoto(80,80);
	}	
}

extern void Foward(void){
	ResetTime();
	while(1){
		if(NF_G_R||FLL_G_R||FRR_G_R||L_G_R||R_G_R||CAUTION_L||CAUTION_R||F_G_E||B_G_E)	break;
		GoodMoto(25,25);
	}	
}

extern void L(void){ 
  ResetTime();
	while(1){
		if((mseconds()>250)||FF_G_R||F_G_R||B_G_E||F_G_E)		break;
	    GoodMoto(-60,60);
	}
}

extern void R(void){
    ResetTime();
	while(1){
		if((mseconds()>250)||F_G_R||AF_G_R||F_G_E||B_G_E)		break;
		GoodMoto(60,-60); 
	}
}
extern void L90(void){ 
    ResetTime();
	while(1){
		if((mseconds()>350)||FF_G_R||F_G_R||B_G_E||F_G_E)		break;			
	  GoodMoto(-60,60);
	}
}

extern void R90(void){
    ResetTime();
	while(1){
		if((mseconds()>350)||F_G_R||AF_G_R||F_G_E||B_G_E)		break;		
		GoodMoto(60,-60); 
	}
}

extern void L_135(void){
	ResetTime();
	while(1){	
		if((mseconds()>650)||FF_G_R||F_G_R||B_G_E||F_G_E)		break;
		GoodMoto(-60,60);
	}
}
extern void R_135(void){ 
	ResetTime();
	while(1){
		if((mseconds()>650)||F_G_R||AF_G_R||F_G_E||B_G_E)		break;		 
		GoodMoto(60,-60);
	}
}
extern void L_180(void){
	ResetTime();
	while(1){
		if((mseconds()>700)||FF_G_R||F_G_R||B_G_E||F_G_E)		break;
		GoodMoto(-60,60);
	}
}

extern void GetRobot(void)
{
	if(F_G_E)
	{
		E_Stop();
		E_Back();
		E_135();
	}
  
	if(F_G_R||FF_G_R){
		for(i=0;i<1;i++){		//3
			if(F_G_R||FF_G_R)	;
			else break;
			if(F_G_R||FF_G_R)	;
			else break;
			beep();
			Afoward();
			}

		//JS();
		//Foward();
	}
	else if(L_G_R||FLL_G_R){
			for(i=0;i<1;i++){		//2
				if(L_G_R||FLL_G_R)	;
				else return;
		}
		L();
	}
	
	else if(R_G_R||FRR_G_R/*||FR_G_R*/){
		for(i=0;i<1;i++){		//2
		   if(R_G_R||FRR_G_R/*||FR_G_R*/)		;
		   else return;
		}
		R();
	}
	else if(L90_G_R){
		for(i=0;i<1;i++){	//3
		   if(L90_G_R)		;
		   else return;
		}
		L90();
	}
	else if(R90_G_R){
		for(i=0;i<1;i++){
		   if(R90_G_R)		;
		   else return;
		}
		R90();
	}
	
	else if(BL_G_R||BLX_G_R){
		for(i=0;i<1;i++){	//3
		   if(BL_G_R||BLX_G_R)		;
		   else return;
		}
		L_135();
	}
	else if(BR_G_R||BRX_G_R){
		for(i=0;i<1;i++){	//3
		   if(BR_G_R||BRX_G_R)		;
		   else return;
		}
		R_135();
	}

	else if(B_G_R){
		for(i=0;i<1;i++){	//3
		   if(B_G_R)		;
		   else return;
		}
		L_180();
	}
	
	if(F_G_R||FF_G_R){
		for(i=0;i<1;i++){		//3
		   if(F_G_R||FF_G_R)	;
		   else return;
		}
		beep();
		Afoward();
		//JS();
		//Foward();
	}
	/*else if(BY){
		GoodMoto(35,35);
		}*/
	else{                                                      
	  GoodMoto(45,45);
		}
 }
