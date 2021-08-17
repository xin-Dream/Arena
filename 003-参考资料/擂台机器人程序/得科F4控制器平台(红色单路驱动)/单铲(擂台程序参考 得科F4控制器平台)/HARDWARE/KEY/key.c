#include "key.h"
#include "delay.h" 
#include "beep.h" 
 

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //key2(keyConfirm)��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE6
	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //KEY0(KEYUP)��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB9
	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //KEY1(KEYDOWM)��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD7
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //KEY3(KEYOUT)��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOD7
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KeyUp==0||KeyDown==0||KeyConfirm==0||KeyOut==0))
	{
		#ifdef KEY_BEEP  
			beep();
		#endif
		
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KeyUp==0)return 3;
		else if(KeyDown==0)return 4;
		else if(KeyConfirm==0)return 1;
		else if(KeyOut==0)return 2;
	}else if(KeyUp==1&&KeyDown==1&&KeyConfirm==1&&KeyOut==1)key_up=1; 	    
 	return 0;// �ް�������
}




















