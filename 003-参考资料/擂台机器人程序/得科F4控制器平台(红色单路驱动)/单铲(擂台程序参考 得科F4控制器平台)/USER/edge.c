#include "edge.h"
#include "ysy.h"

//光电返回1出台  st188返回0出台     

# define AI 				analog
# define DI					digital

# define F_G_E			DI(1)==1 || DI(2)==1			// 前铲出擂台
# define LF_G_E			DI(1)==1 && DI(2)==0			// 前铲左方出擂台
# define RF_G_E			DI(1)==0 && DI(2)==1			// 前铲右方出擂台

# define A_S_C			0//analog_scan_close()					//遇敌

void back()
{
	reset_time();
	while(1)
	{
		GoodMoto(-400,-400);
		if(mseconds()>200||A_S_C)	break;
	}	
}

void forward_stop()//前进时反向刹车
{
	reset_time();
	while(1)
	{
		GoodMoto(-1000,-1000);	
		if(mseconds()>200)	break;
	}
	back();
}

void back_S90()//逆时针90
{
	reset_time();
	while(1)
	{
		GoodMoto(-1000,1000);
		if(mseconds()>200||A_S_C)	break;
	}	
}

void back_N90()//顺时针90
{
	reset_time();
	while(1)
	{
		GoodMoto(1000,-1000);
		if(mseconds()>200||A_S_C)	break;
	}
}

void edge_spin()
{
	reset_time();
	while(1)
	{
		GoodMoto(-700,700);	
		if(mseconds()>400||A_S_C)	break;
	}
}
int get_edge()
{
	if(F_G_E)//前铲出台
	{
		if(LF_G_E)
		{
			ShowStr(2,1,"---左侧");
			forward_stop();
			back_N90();
		}
		else if(RF_G_E)
		{
			ShowStr(2,1,"右侧---");
			forward_stop();
			back_S90();
		}
		else
		{
			forward_stop();
			edge_spin();
//			GoodMoto(0,0);
//			delay_ms(1000);
		}
		GoodMoto(400,400);//前进
		delay_ms(100);
		return 1;
	}
	else
	{
		GoodMoto(400,400);
		return 0;
	}
}