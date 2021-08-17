#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED端口定义
#define LED PAout(12)	// DS0
#define EMAGNET PEout(11)

void LED_Init(void);//初始化		
void led_on(void);
void led_off(void);
void emagnet_on(void);
void emagnet_off(void);
#endif
