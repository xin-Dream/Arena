#include "init.h"

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//字符串数显
#define ShowAI					display_GB2312_u16 //四位数显
#define ShowDI					display_GB2312_u1		//一位数显
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle

int st_get_edge();