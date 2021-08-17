#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
//#include "24cxx.h" 
#include "usmart.h"
#include "vl53l0x.h"
#include "stmflash.h"
u16 flashdata[10];
u16 resettime;


/************************************************
 stm32f103c8t6
 ATK-VL53L0X������ģ�� �ۺϲ���ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

student hetianfang;

//������
int main(void)
{	 

	 delay_init();	    	    //��ʱ������ʼ��	  
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart3_init(115200);	 	    //���ڳ�ʼ��Ϊ115200
	 usmart_dev.init(72);	    //��ʼ��USMART	
//	 KEY_Init();                //������ʼ��
	 //LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	 //LCD_Init();			   	//��ʼ��LCD 		
// AT24CXX_Init();			//IIC��ʼ�� 
//	Flash_Read();
//	hetianfang.resettime++;
//	Flash_Write();
	 USART_SendData(USART3,0x53);
	 while(1)
	 {
//	 USART_SendData(USART1,hetianfang.resettime);

     vl53l0x_test();//vl53l0x����
		
	 }
	
}

