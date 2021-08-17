#ifndef __STRATEGY_H
#define __STRATEGY_H
#include "sys.h"
/**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
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
