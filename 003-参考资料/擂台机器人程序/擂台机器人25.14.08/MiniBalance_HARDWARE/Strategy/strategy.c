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
	Set_Speed_Safe(-BASIC,-BASIC);
	delay_ms(150);
	
	Turn_to(180);
		
	Set_Speed_Safe(BASIC,BASIC);
}
//	左侧传感器测得数值比其他的大一些 大约大100左右
u8 NumLenMore(int len)
{
	u8 i=0;
	if(Len_Back>len)
		i++;
	if(Len_Front>len)
		i++;
	if(Len_Left-100>len)
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

void dengtai_auto(void)
{
	if(Len_Front>CM40&&Len_Back>CM40)
	{
		if(Len_Upback>1200)//如果尾部向上的传感器检测到边缘的木板，头部朝向台子
		{
			Set_Speed_Safe_Show(10,10);
			delay_ms(100);//向前一段距离
			Turn_to(180);
			Set_Speed_Safe_Show(10,10);
			delay_ms(200);//让机器人顶到围栏
			dengtai();
		}
		else//尾部向上的传感器未检测到边缘的木板，可能是机器人尾部朝向台子，也可能是头部朝向台子但是车身过于靠近台子
		{
			Set_Speed_Safe_Show(-10,-10);
			delay_ms(1000);//机器人前进直到尾部顶到台子或者围栏
			if(Len_Upback>1200)//如果尾部向上的传感器检测到边缘的木板，头部朝向台子
			{
			Set_Speed_Safe_Show(10,10);
			delay_ms(100);//后退一段距离
			Turn_to(180);
			Set_Speed_Safe_Show(10,10);
			delay_ms(200);//让机器人顶到围栏
			dengtai();			
			}
		}
	}
	
	else if(Len_Left>CM40&&Len_Right>CM40)
	{
		Turn_to(90);
		
		if(Len_Upback>1200)//如果尾部向上的传感器检测到边缘的木板，头部朝向台子
		{
			Set_Speed_Safe(10,10);
			delay_ms(100);//向前一段距离
			Turn_to(180);
			Set_Speed_Safe(10,10);
			delay_ms(200);//让机器人顶到围栏
			dengtai();
		}
		else//尾部向上的传感器未检测到边缘的木板，可能是机器人尾部朝向台子，也可能是头部朝向台子但是车身过于靠近台子
		{
			Set_Speed_Safe(-10,-10);
			delay_ms(1000);//机器人前进直到尾部顶到台子或者围栏
			if(Len_Upback>1200)//如果尾部向上的传感器检测到边缘的木板，头部朝向台子
			{
			Set_Speed_Safe(10,10);
			delay_ms(100);//后退一段距离
			Turn_to(180);
			Set_Speed_Safe(10,10);
			delay_ms(200);//让机器人顶到围栏
			dengtai();			
			}
		}
	}

}