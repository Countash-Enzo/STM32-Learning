#include "stm32f10x.h"                  // Device header

#ifndef __LED_H //避免头文件重复包含（if no define)
#define __LED_H



void LED_Init(void);
void LED_ON(void);
void LED_OFF(void);
void LED_Turn(void);
	
#endif	