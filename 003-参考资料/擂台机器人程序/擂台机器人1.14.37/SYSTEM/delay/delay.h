#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void delay_us_for(u16 us);
void delay_ms_for(u16 ms);

#endif





























