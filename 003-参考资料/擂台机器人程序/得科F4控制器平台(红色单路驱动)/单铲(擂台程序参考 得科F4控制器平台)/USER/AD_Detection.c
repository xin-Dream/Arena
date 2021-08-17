#include "key.h"
#include "delay.h" 
#include "beep.h" 
#include "lcd.h"
#include <stdarg.h>
#include <stdio.h>
#include "codelib.h"

#define ClearScreen clear_screen
#define display_AI		display_GB2312_u16
#define display_DI		display_GB2312_u1
#define display_str	display_GB2312_string
#define AI analog
#define DI digital

extern void AD_Detection(void)
{
	
	u8 key_temp = 1;
	u8 key = 0;
	unsigned char j = 0;
	unsigned char i = 1;
		while (1)
	{	
		key = KEY_Scan(0);
		if(key != 0) {key_temp = key; i = key;}
		
		if(i==KeyUp_PRES){
			ClearScreen();
			display_str(0,1," -AD Detection- ");
			
			display_str(2,1,"A0=");
			display_str(4,1,"A1=");
			display_str(6,1,"A2=");
			
			display_str(2,66,"A3=");
			display_str(4,66,"A4=");
			display_str(6,66,"A5=");
			i=0;
		}
		else if(i==KeyDown_PRES){
			ClearScreen();
			display_str(0,1," -AD Detection- ");
			
			display_str(2,1,"A6=");
			display_str(4,1,"A7=");
			display_str(6,1,"A8=");
			
			display_str(2,66,"A9 =");
			display_str(4,66,"A10=");
			display_str(6,66,"A11=");
			i=0;
		}
		else if(i==KeyConfirm_PRES){
			ClearScreen();
			display_str(0,1," -AD Detection- ");
			
			display_str(2,1,"A12=");
			display_str(4,1,"A13=");
			display_str(6,1,"D1=");
			display_str(2,71,"D2=");
			display_str(4,71,"D3=");
			display_str(6,71,"D4=");
			i=0;
		}
		
		j++;
		if(j>=100)	j=0;
		if(j%5==0)
		{
			if(key_temp==KeyConfirm_PRES)
			{
				display_DI(6,26,digital(1));
				display_DI(2,96,digital(2));
				display_DI(4,96,digital(3));
				display_DI(6,96,digital(4));
			}
		}
		if(!j)
		{
			if(key_temp==KeyUp_PRES)
			{
				display_AI(2,26,analog(0));	
				display_AI(4,26,analog(1));	
				display_AI(6,26,analog(2));	
				
				display_AI(2,96,analog(3));
				display_AI(4,96,analog(4));
				display_AI(6,96,analog(5));
			}
			else if(key_temp==KeyDown_PRES)
			{
				display_AI(2,26,analog(6));	
				display_AI(4,26,analog(7));	
				display_AI(6,26,analog(8));	
				
				display_AI(2,96,analog(9));
				display_AI(4,96,analog(10));
				display_AI(6,96,analog(11));
			}
			else if(key_temp==KeyConfirm_PRES)
			{
				display_AI(2,31,analog(12));	
				display_AI(4,31,analog(13));	
				display_DI(6,26,digital(1));
				display_DI(2,96,digital(2));
				display_DI(4,96,digital(3));
				display_DI(6,96,digital(4));
			}
		}
		else if(key_temp==KeyOut_PRES)	break;
		delay_ms(5);
	} 
}
