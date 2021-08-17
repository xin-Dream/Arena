#include "strategy.h"

/******************����*****************/

/**************************************************************************
�������ܣ��ǽӴ�ʽ����
��ڲ�������
����  ֵ��unsigned int
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
//	��ഫ���������ֵ�������Ĵ�һЩ ��Լ��100����
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
	if(Len_Upback>1200)//���β�����ϵĴ�������⵽��Ե��ľ�壬ͷ������̨��
	{
		while(Len_Front>1500)//������ǰ�ƶ�ֱ������Χ����Զ,����ת��ռ�
		{
		Set_Speed_Safe_Show(15,15);
		}
		Turn_to(180);
		while(Len_Front<2200)//������ǰ�ƶ�ֱ������̨�ӻ�Χ���Ͻ���������̾���
		{
		Set_Speed_Safe_Show(15,15);
		}
		baizheng();//��̨���֮ǰ����֤��������̨��
		dengtai();
	}
	else//β�����ϵĴ�����δ��⵽��Ե��ľ�壬�����ǻ�����β������̨�ӣ�Ҳ������ͷ������̨�ӵ��ǳ�����ڿ���̨��
	{
		while(Len_Back<2200)//��������ƶ�ֱ������̨�ӻ�Χ���Ͻ�
		{
		Set_Speed_Safe_Show(-15,-15);
		}
		
		if(Len_Upback>1200)//���β�����ϵĴ�������⵽Χ����ľ�壬ͷ������̨��
		{
			while(Len_Front>1500)//������ǰ�ƶ�ֱ������Χ����Զ,����ת��ռ�
			{
			Set_Speed_Safe_Show(15,15);
			}
			Turn_to(180);
			while(Len_Front<2200)//������ǰ�ƶ�ֱ������Χ���Ͻ���������̾���
			{
			Set_Speed_Safe_Show(15,15);
			}
			baizheng();//��̨���֮ǰ����֤��������̨��
			dengtai();
		}
		else
		{
			while(Len_Front<2500)//���β�����ϵĴ�����δ�ܹ���⵽Χ����ľ�壬β������̨��
			{
				Set_Speed_Safe_Show(15,15);//������ǰ�ƶ�ֱ������Χ���Ͻ���������̾���
			}
			baizheng();//��̨���֮ǰ����֤��������̨��
			dengtai();
		}
	}
}

void Front_Left(void)
{
	while(Len_Front<1500)//������ǰ�ƶ�ֱ������Χ���Ͻ������ܹ���֤��ת��ռ�
	{
	Set_Speed_Safe_Show(15,15);
	}
	Turn_to(-90);//˳ʱ��ת��
	while(Len_Back>700)//������ǰ�ƶ�ֱ����֤�ܹ�����λ�������εġ��ߡ���
	{
	Set_Speed_Safe_Show(15,15);
	}
	delay_ms(1000);//����������ǰ�ƶ�ֱ����֤�ܹ�����λ�������εġ��ߡ���
	Turn_to(90);//��ʱ��ת��
	while(Len_Front<2200)//������ǰ�ƶ�ֱ������Χ���Ͻ���������̾���
	{
	Set_Speed_Safe_Show(15,15);
	}		
	baizheng();//��̨���֮ǰ����֤��������̨��
	dengtai();
}

void Run_Free(void)
{
	if(Len_Front>CM40|Len_Back>CM40)
	{
		if(Len_Left>Len_Right)//�����߸�����ĳ����Ե������ת����ǰ��һ��
		{
			Turn_to(90);
			Set_Speed(15,15);
			delay_ms(100);
		}
		else//����ұ߸�����ĳ����Ե������ת����ǰ��һ��
		{
			Turn_to(-90);
			Set_Speed(15,15);
			delay_ms(100);			
		}
	}
	else if(Len_Left>CM40|Len_Right>CM40)
	{
		if(Len_Front>Len_Back)//���ǰ��������ĳ����Ե������ǰ��һ��
		{
			Set_Speed(15,15);
			delay_ms(100);			
		}
		else//����󷽸�����ĳ����Ե���������һ��
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
	else//�����ų�δ�ܹ���������������ȡ�ľ������������鵽��Ե��һ����������ʱ��һ����⵽��Ե
	{
		Run_Free();
	}
}


void Anti_Lean(void)
{
	if(PITCH<34000&&PITCH>18000)//�������
	{
		Set_Speed_Show(-BASIC,-BASIC);
	}
	else if(PITCH>2000&&PITCH<18000)//����ǰ��
	{
		Set_Speed_Show(BASIC,BASIC);
	}
	else if(ROLL<34000&&ROLL>18000)//�������� ������
	{
		Set_Speed_Show(BASIC,-BASIC);
	}
	else if(ROLL>2000&&ROLL<18000)//�������� �Ҳ����
	{
		Set_Speed_Show(-BASIC,BASIC);
	}
}



void Attack_Defend(void)
{
	if(Len_Front_Left>1000&&Len_Front_Right>1000)        //�����ǰ���е���
	{
		while(Gray_Left>1200&&Gray_Mid>1200&&Gray_Right>1200)
		{
			Set_Speed(FIGHT,FIGHT);
		}
	}
	else if(Len_Front_Left >1000&&Len_Front_Right<1400)//�����ǰ���е�������ǰ��û��
	{
		Set_Speed_Safe_Show(-FOLLOW,FOLLOW);
//		Turn_to(20);
	}
	else if(Len_Front_Right >1000&&Len_Front_Left<1400)//�����ǰ���е�������ǰ��û��
	{
		Set_Speed_Safe_Show(FOLLOW,-FOLLOW);
//		Turn_to(-20);
	}
	else if(Len_Left>1000)//�������е���
	{
	    Set_Speed_Safe_Show(-BASIC,BASIC);
		delay_ms(4500/BASIC);
		
	}
	else if(Len_Right>1000)//����Ҳ��е���
	{
	    Set_Speed_Safe_Show(BASIC,-BASIC);
		delay_ms(4500/BASIC);

	}
	else if(Len_Back>1200)//������е���
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
	else//���δ��鵽����
	{
		Set_Speed_Show(BASIC,BASIC);
	}
		
}

