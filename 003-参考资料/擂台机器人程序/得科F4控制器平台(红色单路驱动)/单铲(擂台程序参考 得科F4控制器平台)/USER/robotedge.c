#include "robotedge.h"
#include "ysy.h"
void GoodMoto(int lspeed,int rspeed);
extern int Rs,Ls;

//��緵��0��̨

# define F_G_E			DI(1)==0 || DI(2)==1			// ǰ������̨
# define LF_G_E			DI(1)==0 && DI(2)==0			// ǰ���󷽳���̨
# define RF_G_E			DI(1)==1 && DI(2)==1			// ǰ���ҷ�����̨
# define B_G_E			DI(3)==0 || DI(4)==1			// �������̨
# define RB_G_E			DI(3)==0 && DI(4)==0			// ����ҷ�����̨
# define LB_G_E			DI(3)==1 && DI(4)==1			// ����󷽳���̨
# define KT					DI(1)==0&&DI(4)==1||DI(2)==1&&DI(3)==0				//��̨
# define L_G_E			DI(1)==0&&DI(4)==1				//����̨
# define R_G_E			DI(2)==1&&DI(3)==0				//�Ҳ��̨
# define A_S_C			analog_scan_close					//����

void st_forward()
{
	reset_time();
	while(1)
	{
		GoodMoto(300,300);	
		if(mseconds()>350||F_G_E)	break;
	}	
}
void st_forward_stop()//ǰ��ʱ����ɲ��
{
	reset_time();
	while(1)
	{
		GoodMoto(-600,-600);	
		if(mseconds()>50)	break;
	}	
}
void st_back()
{
	reset_time();
	while(1)
	{
		GoodMoto(-300,-300);	
		if(mseconds()>350||B_G_E)	break;
	}	
}
void st_back_stop()
{
	reset_time();
	while(1)
	{
		GoodMoto(600,600);	
		if(mseconds()>50)	break;
	}	
}
void st_forward_L45()//��ǰ��
{
	reset_time();
	while(1)
	{
		GoodMoto(100,500);
		if(mseconds()>500||F_G_E)	break;
	}	
}
void st_forward_R45()//��ǰ��
{
	reset_time();
	while(1)
	{
		GoodMoto(500,100);	
		if(mseconds()>500||F_G_E)	break;
	}	
}
void st_back_L45()//����
{
	reset_time();
	while(1)
	{
		GoodMoto(-100,-500);
		if(mseconds()>500||B_G_E)	break;
	}	
}
void st_back_R45()//�Һ��
{
	reset_time();
	while(1)
	{
		GoodMoto(-500,-100);
		if(mseconds()>500||B_G_E)	break;
	}	
}
void st_forward_90()
{
	reset_time();
	while(1)
	{
		GoodMoto(400,250);	
		if(mseconds()>500||F_G_E)	break;
	}	
}
void st_back_90()
{
	reset_time();
	while(1)
	{
		GoodMoto(-400,-250);	
		if(mseconds()>500||B_G_E)	break;
	}	
}
int st_get_edge()
{
	if(F_G_E)//ǰ����̨
	{
		if(LF_G_E)
		{
			forward_stop();
			back_R45();//
		}
		else if(RF_G_E)
		{
			forward_stop();
			back_L45();
		}
		else
		{
			forward_stop();
			back_90();
		}
		back();
		return 1;
	}
	else if(B_G_E)
	{
		if(LB_G_E)
		{
			back_stop();
			forward_R45();
		}
		else if(RB_G_E)
		{
			back_stop();
			forward_L45();
		}
		else
		{
			back_stop();
			forward_90();
		}
		forward();
		return 1;
	}
	else if(KT)
	{
		if(L_G_E)
		{
			reset_time();
			while(1)
			{
				GoodMoto(300,-300);	
				if(mseconds()>600||B_G_E&&~F_G_E)	break;
			}
			forward();
		}
		else if(R_G_E)
		{
			reset_time();
			while(1)
			{
				GoodMoto(-300,300);	
				if(mseconds()>600||B_G_E&&~F_G_E)	break;
			}
			forward();
		}
		return 1;
	}
	else return 0;
}