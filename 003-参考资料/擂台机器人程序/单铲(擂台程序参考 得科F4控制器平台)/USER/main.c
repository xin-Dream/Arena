/********************************************
* 版本:	TheMonster_1.1_2017.08.09
*********************************************/
#include "init.h"
#include "function.h"		//所有业务详细子程序和详细模块程序都放在function.h头文件，main.c文件主要写跑的模块程序。
#include "ysy.h"				//2017.10
#include "edge.h"

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//字符串数显
#define ShowAI					display_GB2312_u16 //四位数显
#define ShowDI					display_GB2312_u1		//一位数显
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle	

void RobotInit(void);
void AD_Detection(void);
void GoodMoto(int lspeed,int rspeed);

u8 Key = 0;
u8 Key_Temp = 0;
extern int Rs,Ls;
int temp,t=0;

int main(void)
{
	int i,n=0;
	MarineRobot_init();
	start_feedback();//启动反馈
	
	
	while(1)
	{	
		allmotor(300, 300, 300, 300);
		delay_ms(1000);
		delay_ms(1000);
		allmotor(0, 0, 0, 0);
		delay_ms(1000);
		delay_ms(1000);
		allmotor(-800, -800, -800, -800);
		delay_ms(1000);
		delay_ms(1000);
		allmotor(0, 0, 0, 0);
		delay_ms(1000);
		delay_ms(1000);
	}
	
	while(1)
	{
		Key = KEY_Scan(0);
		Key_Temp = Key;
		ShowStr(0,1,"1、检测模式");
		ShowStr(2,1,"2、主程序");
		ShowStr(4,1,"3、测试程序");
		ShowStr(6,1,"4、返回");
		Key = KEY_Scan(0);
		if(Key != 0) Key_Temp = Key;
		if(Key_Temp==1)//按键1程序段
		{
			test();
		}
		else if(Key_Temp==2)//按键2程序段
		{
			ClearScreen();
	  	up_stage();
			while(1)
			{
				get_edge();
//				GoodMoto(-200,-200);	
				select_high();
				find_single();
			}
		}
		else if(Key_Temp==3)//按键3程序段
		{
			ClearScreen();
			while(1)
			{
				emagnet_off();
				delay_ms(1000);
				emagnet_on();
				delay_ms(1000);


//				ShowAI(0,1,n);
//				if(DI(1)==1)
//				{
//					while(1)
//					{
//						if(DI(1)==0)
//						{
//							n=n+1;
//							break;
//						}
//				}
//				}
		    }
//			up_stage();
//			GoodMoto(0,0);
		}
		else if(Key_Temp==4)//按键4程序段
		{
				
			ClearScreen();
			touch_sensor();
		}
	}
}