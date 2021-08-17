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
		if(Len_Left>2500&&Len_Right>2500)
		{
			i++;
			delay_ms(50);
		}
		else
		{
			i=0;
		}
	}
	dengtai();
	return qidong;
}

void Avoid_Falling(void)
{
	if(Len_Edge_Left<2000&&Len_Edge_Right>2500)
	{
		
	}
	else if(Len_Edge_Right<2000&&Len_Edge_Left>2500)
	{
		
	}
	else
	{
		Set_Speed_Safe(-BASIC,-BASIC);
		delay_ms(300);
		Clockwise(180);
	}	
}
/////////////////////////////////////
void Avoid_Falling_180(void)
{
	LED_On;	
	Set_Speed_Safe_Show(-BASIC,-BASIC);
	delay_ms(200);
	Clockwise(180);
	LED_Off;
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
	if(Len_Front_Left>Length_Short&&Len_Front_Right>Length_Short)        //�����ǰ���е���
	{
		Set_Speed(FIGHT,FIGHT);
//		while(Gray_Left>1200&&Gray_Mid>1200&&Gray_Right>1200)
//		{
//			Set_Speed(FIGHT,FIGHT);
//		}
	}
	else if(Len_Front_Left >Length_Short&&Len_Front_Right<Length_Long)//�����ǰ���е�������ǰ��û��
	{
		Set_Speed_Safe_Show(-FOLLOW,FOLLOW);
//		Turn_to(20);
	}
	else if(Len_Front_Right >Length_Short&&Len_Front_Left<Length_Long)//�����ǰ���е�������ǰ��û��
	{
		Set_Speed_Safe_Show(FOLLOW,-FOLLOW);
//		Turn_to(-20);
	}
	else if(Len_Left>Length_Short)//�������е���
	{
	    Counterlockwise(90);
		
	}
	else if(Len_Right>Length_Short)//����Ҳ��е���
	{
	    Clockwise(90);
	}
	else if(Len_Back>Length_Short)//������е���
	{
		Clockwise(180);
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

void dengtai_auto2(void)
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
	else if(NumLenMore(CM40)>1)
	{
		if(Len_Front>CM40)
		{
			zhuanquan(-3,0);
		}
		else
		{
			zhuanquan(3,0);
		}
	}
	else
	{
		if(Len_Front<Len_Back)
		{
			Set_Speed_Show(BASIC,BASIC);
		}
		else
		{
			Set_Speed_Show(-BASIC,-BASIC);
		}
	
	}

}
