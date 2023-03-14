#include "stm32f10x.h"                  // Device header
#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H
void CountSensor_Init(void);
void EXTI15_10_IRQHandler(void);
uint16_t CountSensor_Get(void);

#endif