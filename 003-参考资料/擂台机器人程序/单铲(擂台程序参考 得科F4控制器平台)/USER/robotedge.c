#include "robotedge.h"
#include "ysy.h"
void GoodMoto(int lspeed,int rspeed);
extern int Rs,Ls;

//光电返回0出台

# define F_G_E			DI(1)==0 || DI(2)==1			// 前铲出擂台
# define LF_G_E			DI(1)==0 && DI(2)==0			// 前铲左方出擂台
# define RF_G_E			DI(1)==1 && DI(2)==1			// 前铲右方出擂台
# define B_G_E			DI(3)==0 || DI(4)==1			// 后铲出擂台
# define RB_G_E			DI(3)==0 && DI(4)==0			// 后铲右方出擂台
# define LB_G_E			DI(3)==1 && DI(4)==1			// 后铲左方出擂台
# define KT					DI(1)==0&&DI(4)==1||DI(2)==1&&DI(3)==0				//卡台
# define L_G_E			DI(1)==0&&DI(4)==1				//左侧掉台
# define R_G_E			DI(2)==1&&DI(3)==0				//右侧掉台
# define A_S_C			analog_scan_close					//遇敌

void st_forward()
{
	reset_time();
	while(1)
	{
		GoodMoto(300,300);	
		if(mseconds()>350||F_G_E)	break;
	}	
}
void st_forward_stop()//前进时反向刹车
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
void st_forward_L45()//左前拐
{
	reset_time();
	while(1)
	{
		GoodMoto(100,500);
		if(mseconds()>500||F_G_E)	break;
	}	
}
void st_forward_R45()//右前拐
{
	reset_time();
	while(1)
	{
		GoodMoto(500,100);	
		if(mseconds()>500||F_G_E)	break;
	}	
}
void st_back_L45()//左后拐
{
	reset_time();
	while(1)
	{
		GoodMoto(-100,-500);
		if(mseconds()>500||B_G_E)	break;
	}	
}
void st_back_R45()//右后拐
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
	if(F_G_E)//前铲出台
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