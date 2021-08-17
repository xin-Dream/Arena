#include "strategy.h"

/******************策略*****************/

/**************************************************************************
函数功能：非接触式启动
入口参数：无
返回  值：unsigned int
**************************************************************************/

u8 qidong=0;
u8 Start_untouch(void)
{
	uint8_t i=0;
	while(i<20)
	{
		if(Len_Left>2000&&Len_Right>2000)
		{
			i++;
			delay_ms(50);
		}
	}
	dengtai();
	return qidong;
}

void Avoid_Falling(void)
{
	Set_Speed_Safe(-BASIC,-BASIC);
	delay_ms(300);
	if(Edge_Left)
	{
		Turn_to(10);
	}
	else if(Edge_Right)
	{
		Turn_to(-10);
	}
		
	Set_Speed_Safe(BASIC,BASIC);
}

void Avoid_Falling_180(void)
{
	Set_Speed_Safe_Show(-BASIC,BASIC);
	delay_ms(9000/BASIC);
	Set_Speed_Safe_Show(BASIC,BASIC);
	delay_ms(9000/BASIC);
}
//	左侧传感器测得数值比其他的大一些 大约大100左右
u8 NumLenMore(int len)
{
	u8 i=0;
	if(Len_Back>len)
		i++;
	if(Len_Front>len)
		i++;
	if(Len_Left>len)
		i++;
	if(Len_Right>len)
		i++;
	
	return i;
}

u8 NumLenLess(int len)
{
	u8 i=0;
	if(Len_Back<len)
		i++;
	if(Len_Front<len)
		i++;
	if(Len_Left-100<len)
		i++;
	if(Len_Right<len)
		i++;
	
	return i;
}

u8 NumGrayMore(int gray)
{
	u8 i=0;
	if(Gray_Left>gray)
		i++;
	if(Gray_Mid>gray)
		i++;
	if(Gray_Right>gray)
		i++;
	
	return i;
}

u8 NumGrayLess(int gray)
{
	u8 i=0;
	if(Gray_Left<gray)
		i++;
	if(Gray_Mid<gray)
		i++;
	if(Gray_Right<gray)
		i++;
	
	return i;
}

void Front_Back(void)
{
	if(Len_Upback>1200)//如果尾部向上的传感器检测到边缘的木板，头部朝向台子
	{
		while(Len_Front>1500)//缓速向前移动直到距离围栏较远,留出转向空间
		{
		Set_Speed_Safe_Show(15,15);
		}
		Turn_to(180);
		while(Len_Front<2200)//缓速向前移动直到距离台子或围栏较近，留出冲刺距离
		{
		Set_Speed_Safe_Show(15,15);
		}
		baizheng();//上台冲刺之前，保证车身正对台子
		dengtai();
	}
	else//尾部向上的传感器未检测到边缘的木板，可能是机器人尾部朝向台子，也可能是头部朝向台子但是车身过于靠近台子
	{
		while(Len_Back<2200)//缓速向后移动直到距离台子或围栏较近
		{
		Set_Speed_Safe_Show(-15,-15);
		}
		
		if(Len_Upback>1200)//如果尾部向上的传感器检测到围栏的木板，头部朝向台子
		{
			while(Len_Front>1500)//缓速向前移动直到距离围栏较远,留出转向空间
			{
			Set_Speed_Safe_Show(15,15);
			}
			Turn_to(180);
			while(Len_Front<2200)//缓速向前移动直到距离围栏较近，留出冲刺距离
			{
			Set_Speed_Safe_Show(15,15);
			}
			baizheng();//上台冲刺之前，保证车身正对台子
			dengtai();
		}
		else
		{
			while(Len_Front<2500)//如果尾部向上的传感器未能够检测到围栏的木板，尾部朝向台子
			{
				Set_Speed_Safe_Show(15,15);//缓速向前移动直到距离围栏较近，留出冲刺距离
			}
			baizheng();//上台冲刺之前，保证车身正对台子
			dengtai();
		}
	}
}

void Front_Left(void)
{
	while(Len_Front<1500)//缓速向前移动直到距离围栏较近，又能够保证有转向空间
	{
	Set_Speed_Safe_Show(15,15);
	}
	Turn_to(-90);//顺时针转向
	while(Len_Back>700)//缓速向前移动直到保证能够车身位于正方形的“边”上
	{
	Set_Speed_Safe_Show(15,15);
	}
	delay_ms(1000);//继续缓速向前移动直到保证能够车身位于正方形的“边”上
	Turn_to(90);//逆时针转向
	while(Len_Front<2200)//缓速向前移动直到距离围栏较近，留出冲刺距离
	{
	Set_Speed_Safe_Show(15,15);
	}		
	baizheng();//上台冲刺之前，保证车身正对台子
	dengtai();
}

void Run_Free(void)
{
	if(Len_Front>CM40|Len_Back>CM40)
	{
		if(Len_Left>Len_Right)//如果左边更靠近某个边缘，则左转并向前走一会
		{
			Turn_to(90);
			Set_Speed(15,15);
			delay_ms(100);
		}
		else//如果右边更靠近某个边缘，则右转并向前走一会
		{
			Turn_to(-90);
			Set_Speed(15,15);
			delay_ms(100);			
		}
	}
	else if(Len_Left>CM40|Len_Right>CM40)
	{
		if(Len_Front>Len_Back)//如果前方更靠近某个边缘，则向前走一会
		{
			Set_Speed(15,15);
			delay_ms(100);			
		}
		else//如果后方更靠近某个边缘，则向后走一会
		{
			Set_Speed(-15,-15);
			delay_ms(100);			
		}
	}
}

void dengtai_auto(void)
{
	if(Len_Front>CM40&&Len_Back>CM40)
	{
		Front_Back();
	}
	
	else if(Len_Left>CM40&&Len_Right>CM40)
	{
		Turn_to(90);
		Front_Back();
	}
	else if(Len_Front>CM40&&Len_Left>CM40)
	{
		Front_Left();
	}
	else if(Len_Back>CM40&&Len_Left>CM40)
	{
		Turn_to(90);
		Front_Left();
	}
	else if(Len_Back>CM40&&Len_Right>CM40)
	{
		Turn_to(180);
		Front_Left();
	}
	else if(Len_Front>CM40&&Len_Right>CM40)
	{
		Turn_to(-90);
		Front_Left();
	}
	else//并不排除未能够有两个传感器获取的距离数据满足检查到边缘这一情况，假设此时有一个检测到边缘
	{
		Run_Free();
	}
}


void Anti_Lean(void)
{
	if(PITCH<34000&&PITCH>18000)//车身后仰
	{
		Set_Speed_Show(-BASIC,-BASIC);
	}
	else if(PITCH>2000&&PITCH<18000)//车身前倾
	{
		Set_Speed_Show(BASIC,BASIC);
	}
	else if(ROLL<34000&&ROLL>18000)//车身右倾 左侧垫起
	{
		Set_Speed_Show(BASIC,-BASIC);
	}
	else if(ROLL>2000&&ROLL<18000)//车身左倾 右侧垫起
	{
		Set_Speed_Show(-BASIC,BASIC);
	}
}



void Attack_Defend(void)
{
	if(Len_Front_Left>1000&&Len_Front_Right>1000)        //如果正前方有敌人
	{
		while(Gray_Left>1200&&Gray_Mid>1200&&Gray_Right>1200)
		{
			Set_Speed(FIGHT,FIGHT);
		}
	}
	else if(Len_Front_Left >1000&&Len_Front_Right<1400)//如果左前方有敌人且右前方没有
	{
		Set_Speed_Safe_Show(-FOLLOW,FOLLOW);
//		Turn_to(20);
	}
	else if(Len_Front_Right >1000&&Len_Front_Left<1400)//如果右前方有敌人且左前方没有
	{
		Set_Speed_Safe_Show(FOLLOW,-FOLLOW);
//		Turn_to(-20);
	}
	else if(Len_Left>1000)//如果左侧有敌人
	{
	    Set_Speed_Safe_Show(-BASIC,BASIC);
		delay_ms(4500/BASIC);
		
	}
	else if(Len_Right>1000)//如果右侧有敌人
	{
	    Set_Speed_Safe_Show(BASIC,-BASIC);
		delay_ms(4500/BASIC);

	}
	else if(Len_Back>1200)//如果后方有敌人
	{
		Set_Speed_Safe_Show(-BASIC,BASIC);
		delay_ms(15000/BASIC);
//		Set_Speed(80,80);
//	    delay_ms(100);
//		Set_Speed(0,0);
//		delay_ms(50);
//	    Turn_to(180);
//		Set_Speed(0,0);
//		delay_ms(10);
	}
	else//如果未检查到敌人
	{
		Set_Speed_Show(BASIC,BASIC);
	}
		
}

