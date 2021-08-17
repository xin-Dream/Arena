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
 ATK-VL53L0X激光测距模块 综合测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

student hetianfang;

//主函数
int main(void)
{	 

	 delay_init();	    	    //延时函数初始化	  
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	 uart3_init(115200);	 	    //串口初始化为115200
	 usmart_dev.init(72);	    //初始化USMART	
//	 KEY_Init();                //按键初始化
	 //LED_Init();		  		//初始化与LED连接的硬件接口
	 //LCD_Init();			   	//初始化LCD 		
// AT24CXX_Init();			//IIC初始化 
//	Flash_Read();
//	hetianfang.resettime++;
//	Flash_Write();
	 USART_SendData(USART3,0x53);
	 while(1)
	 {
//	 USART_SendData(USART1,hetianfang.resettime);

     vl53l0x_test();//vl53l0x测试
		
	 }
	
}

