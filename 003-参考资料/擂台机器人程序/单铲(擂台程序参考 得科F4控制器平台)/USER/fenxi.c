//F-Foward B-Behind L-Left	R-Right		sum=1
#define F		A2>1100 || A3>1100 || A4>1100
#define FL	A2>1100 || A3>1100 || A4<900
#define FR	A2<900  || A3>1100 || A4>1100
#define L		A2>1100 || A3<900  || A4<900
#define R		A2<900  || A3<900  || A4>1100
#define L45	AI(1)>1100
#define R45	AI(5)>1100
#define L90	AI(0)>1100
#define R90	AI(6)>1100
#define B		AI(8)>1100
#define BL	AI(9)>1100
#define BR	AI(7)>1100

//E-Edge	sum=0
#define FE	DI(0)==0 || DI(1)==0
#define BE	DI(2)==1 || DI(3)==1

//S-stage	sum=2
#define FS	AI(3)>2400 && abs(AI(2)-AI(4))<100 && DI(4)==1 && (AI(0)<900 && AI(6)<900)		// 前正对擂台
#define BS	AI(3)>2400 && abs(AI(2)-AI(4))<100 && DI(4)==0 && (AI(0)<900 && AI(6)<900)		// 后正对擂台
#define LRS	(AI(0)>2400 && AI(6)>2400) && AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(5)==0	// 左右正对擂台
// 判断条件再检测、优化
// 利用上灰度？

//F-fence	sum=2
#define FLF	AI(3)>2400 && abs(AI(2)-AI(4)<100) && DI(4)==0 && AI(0)>1800 && AI(6)<900		// 前左正对围栏
#define FRF	AI(3)>2400 && abs(AI(2)-AI(4)<100) && DI(4)==0 && AI(0)<900 && AI(6)>1800		// 前右正对围栏
#define BLF	AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(4)==1 && AI(0)>1800 && AI(6)<900	// 后左正对围栏
#define BRF	AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(4)==1 && AI(0)<900 && AI(6)>1800	// 后右正对围栏

//同时检测到三个“敌人”	sum=3	-在台下检测到敌人后退 -朝后、朝右的漫反射红外开关？ -？此处判断有必要加上漫反射红外开关？
#define FLR	AI(3)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==0 && AI(8)<900	//前左围栏右敌人（后无右无）、前右围栏左敌人（后无右有）、左右擂台前敌人（后无右无）
#define BLR	AI(8)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==1 && AI(3)<900	//后左围栏右敌人（后有右无）、后右围栏左敌人（后有友有）、左右擂台后敌人（后无右无）
#define FBL	AI(3)>1800 && AI(8)>1800 && AI(0)>1800 && AI(6)<900 && DI(4)==1	//前左围栏后敌人（后有右无）、后左围栏前敌人（后有右无）、前后擂台左敌人（后有右无）
#define FBR	AI(3)>1800 && AI(8)>1800 && AI(6)>1800 && AI(0)<900 && DI(4)==1	//前右围栏后敌人（后无右有）、后右围栏前敌人（后无右有）、前后擂台右敌人（后有右无）

// 斜在角落		sum=4

u16 A[14]={0};
u8 D[6]={0};

u16 ADReturnOnStage(void){
	A2 = AI(2);
	A3 = AI(3);
	A4 = AI(4);
}

u16 ADReturnUnderStage(void){
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

u16 ADReturn(u8 *temp,u8 num){
	u8 i;
	for(i=0;i<num;i++){
		A[temp[i]] = AI(i);
	}
}

u8 stage(void){
	u8 EnemyNum	= 0;		// 记录同时检测“敌人“数
	if(F||L45||R45)	EnemyNum++;
	if(L90)	EnemyNum+;
	if(R90)	EnemyNum++;
	if(B||BL||BR)	EnemyNum++;
	
	if(EnemyNum>2)	renturn 0;		// 在台上
	else						renturn 1;		// 在台下
}

extern void S_Foward(void){
	ResetTime();
	while(1){
		if((second()>1.3||LRS||FLF||FRF))	break;
		GoodMoto(50,50);
	}
}

extern void S_Back(void){
	ResetTime();
	while(1){
		if((second()>0.9)||LRS||FLF||FRF)	break;
		GoodMoto(-50,-50);
	}
}

extern void S_back(void){
	
}

extern void S_30(void){
	ResetTime();
	while(1){
		if((second()>))	break;
		GoodMoto(-50,50);
	
	}
}

extern void S_180(void){
	ResetTime();
	while(1){
		if((second()>0.9||FS))	break;
		GoodMoto(60,-60);
	}
}

extern void S_90(void){		//调整车头朝向擂台垂直 或 合理增加传感器区分具体情况
	ResetTime();
	while(1){
		if((second()>1.8)||FS)	break;	//慢速调整位置
		GoodMoto(45,-45);
	}
}

extern void S_L90(void){
	ResetTime();
	while(1){
		if((second()>0.33||FS))	break;
		GoodMoto(-50,50);
	}
}

extern void S_R90(void){
	ResetTime();
	while(1){
		if((second()>))	break;
		GoodMoto(50,-50);
	}
}

extern void Up2Stage(void){
	ResetTime();
	while(1){
		if((second()>))	break;
	
	}
}

extern void GetStage(void){
	/***检测到擂台***/
	if(FS){
		for(i=0;i<3;i++){
			if(FS)	;
			else return;
		}
		Up2Stage();
	}
	else if(BS){
		for(i=0;i<3;i++){
			if(BS)	;
			else return;
		}
		S_180();
		Up2Stage();
	}
	else if(LRS){
		for(i=0;i<3;i++){
			if(LRS)	;
			else return;
		}
		S_90();
		Up2Stage();
	}
	/***检测到围栏***/
	if(FLF){
		for(i=0;i<3;i++){
			if(FLF)	;
			else return;
		}
		S_Back();
		S_R90();
		Up2Stage();
	}
	else if(FRF){
		for(i=0;i<3;i++){
			if(FRF)	;
			else return;
		}
		S_Back();
		S_L90();
		Up2Stage();
	}
	else if(BLF){
		for(i=0;i<3;i++){
			if(BLF)	;
			else return;
		}
		S_Foward();
		S_R90();
		Up2Stage();
	}
	else if(BRF){
		for(i=0;i<3;i++){
			if(BRF)	;
			else return;
		}
		S_Foward();
		S_L90();
		Up2Stage();
	}
	else{
		S_back();
		S_30();			//小角度转角后退调整位置，有待优化
	}
}
