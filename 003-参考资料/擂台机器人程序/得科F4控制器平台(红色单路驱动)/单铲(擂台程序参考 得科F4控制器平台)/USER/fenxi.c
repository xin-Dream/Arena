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
#define FS	AI(3)>2400 && abs(AI(2)-AI(4))<100 && DI(4)==1 && (AI(0)<900 && AI(6)<900)		// ǰ������̨
#define BS	AI(3)>2400 && abs(AI(2)-AI(4))<100 && DI(4)==0 && (AI(0)<900 && AI(6)<900)		// ��������̨
#define LRS	(AI(0)>2400 && AI(6)>2400) && AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(5)==0	// ����������̨
// �ж������ټ�⡢�Ż�
// �����ϻҶȣ�

//F-fence	sum=2
#define FLF	AI(3)>2400 && abs(AI(2)-AI(4)<100) && DI(4)==0 && AI(0)>1800 && AI(6)<900		// ǰ������Χ��
#define FRF	AI(3)>2400 && abs(AI(2)-AI(4)<100) && DI(4)==0 && AI(0)<900 && AI(6)>1800		// ǰ������Χ��
#define BLF	AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(4)==1 && AI(0)>1800 && AI(6)<900	// ��������Χ��
#define BRF	AI(3)<900 && AI(2)<900 && AI(4)<900 && DI(4)==1 && AI(0)<900 && AI(6)>1800	// ��������Χ��

//ͬʱ��⵽���������ˡ�	sum=3	-��̨�¼�⵽���˺��� -���󡢳��ҵ���������⿪�أ� -���˴��ж��б�Ҫ������������⿪�أ�
#define FLR	AI(3)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==0 && AI(8)<900	//ǰ��Χ���ҵ��ˣ��������ޣ���ǰ��Χ������ˣ��������У���������̨ǰ���ˣ��������ޣ�
#define BLR	AI(8)>1800 && AI(0)>1800 && AI(6)>1800 && DI(4)==1 && AI(3)<900	//����Χ���ҵ��ˣ��������ޣ�������Χ������ˣ��������У���������̨����ˣ��������ޣ�
#define FBL	AI(3)>1800 && AI(8)>1800 && AI(0)>1800 && AI(6)<900 && DI(4)==1	//ǰ��Χ������ˣ��������ޣ�������Χ��ǰ���ˣ��������ޣ���ǰ����̨����ˣ��������ޣ�
#define FBR	AI(3)>1800 && AI(8)>1800 && AI(6)>1800 && AI(0)<900 && DI(4)==1	//ǰ��Χ������ˣ��������У�������Χ��ǰ���ˣ��������У���ǰ����̨�ҵ��ˣ��������ޣ�

// б�ڽ���		sum=4

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
	u8 EnemyNum	= 0;		// ��¼ͬʱ��⡰���ˡ���
	if(F||L45||R45)	EnemyNum++;
	if(L90)	EnemyNum+;
	if(R90)	EnemyNum++;
	if(B||BL||BR)	EnemyNum++;
	
	if(EnemyNum>2)	renturn 0;		// ��̨��
	else						renturn 1;		// ��̨��
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

extern void S_90(void){		//������ͷ������̨��ֱ �� �������Ӵ��������־������
	ResetTime();
	while(1){
		if((second()>1.8)||FS)	break;	//���ٵ���λ��
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
	/***��⵽��̨***/
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
	/***��⵽Χ��***/
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
		S_30();			//С�Ƕ�ת�Ǻ��˵���λ�ã��д��Ż�
	}
}
