#include "key.h"
#include "delay.h" 
#include "beep.h" 
 

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //key2(keyConfirm)对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE6
	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //KEY0(KEYUP)对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB9
	
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //KEY1(KEYDOWM)对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD7
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //KEY3(KEYOUT)对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOD7
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KeyUp==0||KeyDown==0||KeyConfirm==0||KeyOut==0))
	{
		#ifdef KEY_BEEP  
			beep();
		#endif
		
		delay_ms(10);//去抖动 
		key_up=0;
		if(KeyUp==0)return 3;
		else if(KeyDown==0)return 4;
		else if(KeyConfirm==0)return 1;
		else if(KeyOut==0)return 2;
	}else if(KeyUp==1&&KeyDown==1&&KeyConfirm==1&&KeyOut==1)key_up=1; 	    
 	return 0;// 无按键按下
}




















