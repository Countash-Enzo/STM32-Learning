#include "stm32f10x.h"                  // Device header
#ifndef __PWM_H
#define __PWM_H
void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare);
#endif