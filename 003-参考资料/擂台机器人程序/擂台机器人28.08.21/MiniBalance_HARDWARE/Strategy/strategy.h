#ifndef __STRATEGY_H
#define __STRATEGY_H
#include "sys.h"
/**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
u8 Start_untouch(void);
void Avoid_Falling(void);
void Avoid_Falling_180(void);
u8 NumLenMore(int len);
u8 NumLenLess(int len);
u8 NumGrayMore(int len);
u8 NumGrayLess(int len);
void dengtai_auto(void);
void Run_Free(void);
void Anti_Lean(void);
void Attack_Defend(void);

#endif
