#include "./GPIO/GPIO.h"
//利用IO口B4-B8作输入
//利用IO口B9作继电器控制输出
void GPIO_IN_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

}	
//利用IO口B4-B8作输入
u8 readio(void)
{
	u8 temp=0;
	temp=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);//MHQ
	temp=temp<<1|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);//MHT
	temp=temp<<1|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6);//GG
	
	
	temp=temp<<1|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);//SHZ 水壶灶
	temp=temp<<1|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);//GZ  锅灶
	temp=temp<<1|GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);//ZKG 总开关
	return temp;
}
/*********************************************END OF FILE**********************/
