#ifndef __SERVOR_BC_H
#define __SERVOR_BC_H	 
#include "sys.h" 

#define CDS_SEVMODE			0			
#define CDS_MOTOMODE		1			

extern void UP_CDS_SetMode(u8 id, u8 mode);					
extern void UP_CDS_SetAngle(u8 id, u16 angle, u16 speed);															
extern void UP_CDS_SetSpeed(u8 id, s16 speed);				// -1023~+1023

#endif
