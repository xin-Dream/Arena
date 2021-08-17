#include "window.h"

//初始界面 初始化
void window_init(void)
{
	POINT_COLOR=BLUE;
	LCD_Clear(WHITE);
	LCD_ShowString(25 ,2,100,24,24,"skydrive");
	LCD_ShowString(142,9,200,16,16,"flight parameters");	
	LCD_Fill(160,30 ,161,207,BLACK);
	LCD_Fill(0  ,28 ,319,29 ,BLACK);
	LCD_Fill(0  ,208,319,209,BLACK);
	LCD_Fill(0  ,235,319,239,BLACK);
	LCD_ShowString(10 ,30 ,200,24,24,"PITCH");
	LCD_ShowString(10 ,60 ,200,24,24," YAW ");
	LCD_ShowString(10 ,90 ,200,24,24," ROLL");
	LCD_ShowWord(10 ,120,6 ,24,0); LCD_ShowWord(34 ,120,7 ,24,0); LCD_ShowNum(70 ,120,1000,4,24);LCD_ShowString(126,120,200,24,24,"mV");
	LCD_ShowWord(10 ,150,8 ,24,0); LCD_ShowWord(34 ,150,9 ,24,0); LCD_ShowNum(70 ,150,0   ,4,24);LCD_ShowWord(126,150,10,24,0);
	LCD_ShowWord(10 ,180,17,24,0); LCD_ShowWord(34 ,180,18,24,0); LCD_ShowNum(70 ,180,50  ,4,24);LCD_ShowString(126,180,200,24,24,"%");
	LCD_ShowWord(170,30 ,0 ,24,0); LCD_ShowWord(194,30 ,1 ,24,0); LCD_ShowNum(218,30 ,2   ,1,24);LCD_ShowString(260,30 ,200,24,24,"off");
	LCD_ShowWord(170,60 ,2 ,24,0); LCD_ShowWord(194,60 ,3 ,24,0); LCD_ShowWord(230,60,13 ,24,0);
	LCD_ShowWord(170,90 ,4 ,24,0); LCD_ShowWord(194,90 ,5 ,24,0); LCD_ShowNum(230,90 ,1000,4,24);LCD_ShowString(286,90 ,200,24,24,"Hz");
	LCD_ShowWord(170,120,6 ,24,0); LCD_ShowWord(194,120,7 ,24,0); LCD_ShowNum(230,120,1000,4,24);LCD_ShowString(286,120,200,24,24,"mV");
	LCD_ShowWord(170,150,8 ,24,0); LCD_ShowWord(194,150,9 ,24,0); LCD_ShowNum(230,150,0   ,4,24);LCD_ShowWord(286,150,10,24,0);
	LCD_ShowWord(170,180,17,24,0); LCD_ShowWord(194,180,18,24,0); LCD_ShowNum(230,180,50  ,4,24);LCD_ShowString(286,180,200,24,24,"%");
	LCD_ShowString(130,210,100,24,24,"start");
}

