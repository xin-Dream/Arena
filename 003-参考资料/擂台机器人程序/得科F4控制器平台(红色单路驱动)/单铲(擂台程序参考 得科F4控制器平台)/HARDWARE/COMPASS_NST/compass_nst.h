#ifndef __COMPASS_NST_H
#define __COMPASS_NST_H	 
#include "sys.h" 


#define  CPS_SCL        PCin(10)
#define  CPS_SDA      PCin(11)

void COMPASS_NST_Init(void);	//IO≥ı ºªØ
u8 compassRead(void);


#endif
