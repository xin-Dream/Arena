#include "servor_bc.h"
#include "delay.h"  
#include "usart.h"
 

#define CMD_READ			0x02		//¨ºy¡Á????¨²?¨¢?¨¹¨¢?
#define CMD_WRITE			0x03		//¨ºy¡Á????¨²D¡ä?¨¹¨¢?
#define CMD_SWRITE		0x83		//¨ºy¡Á????¨²¨ª?2?D¡ä?¨¹¨¢?

void UP_CDS_SetMode(u8 id, u8 mode)
{
	u8 buf[5];
	if(mode > 1)	return;
	buf[0] = 0x06;
	if(mode == CDS_SEVMODE)
	{
		buf[1] = 0;		
		buf[2] = 0;
		buf[3] = 0xff;
		buf[4] = 0x03;
	}
	else if(mode == CDS_MOTOMODE)
	{
		buf[1] = 0;		
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
	}
	UP_Uart3_SendCDSFrame(id,0x07,CMD_WRITE,buf);
	delay_ms(30);
}

void UP_CDS_SetAngle(u8 id, u16 angle, u16 speed)
{
	u8 buf[5];
	if(angle > 1023 || speed > 1023)
		return;
	buf[0] = 0x1E;
	buf[1] = angle;		
	buf[2] = angle>>8;
	buf[3] = speed;
	buf[4] = speed>>8;
	UP_Uart3_SendCDSFrame(id,0x07,CMD_WRITE,buf);
}

void UP_CDS_SetSpeed(u8 id, s16 speed)
{
	u8 buf[5];
	u16 temp;
	if(speed > 1023 || speed < -1023)
		return;
	temp = speed>0?speed:-speed;
	buf[0] = 0x20;
	buf[1] = temp;
	buf[2] = temp>>8;
	if(speed < 0)
		buf[2] |= 0x04;
	UP_Uart3_SendCDSFrame(id,0x05,CMD_WRITE,buf);
}
