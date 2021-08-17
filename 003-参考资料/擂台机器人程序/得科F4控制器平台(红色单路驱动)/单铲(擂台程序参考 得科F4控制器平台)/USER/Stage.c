#include "lcd.h"
#include "pwm.h"
#include "sensor.h"
#include <stdarg.h>
#include <stdio.h>
#include "codelib.h"

# define AI analog
# define DI digital
# define TimeGo start_time
# define TimeStop stop_time
# define ResetTime reset_time


unsigned char sum = 0;

u8 Stage(void){
	//卡台判断
	if(FF_G_R||L_G_R||R_G_R) 	sum++;
	if(L90_G_R||BLX_G_R)			sum++;
	if(R90_G_R||BRX_G_R)			sum++;
	if(BL_G_R||B_G_R||BR_G_R)	sum++;
	
	if(sum>1)	return 0;	//2，3，4在台下
	else return 1;			//0，1在台上
}