#include "stm32f10x.h" 
#include "Delay.h"// Device header
void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Instructure);
}

uint8_t LightSensor_Get()
{
	
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
	
	
}