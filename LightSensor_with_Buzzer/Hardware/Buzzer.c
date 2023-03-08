#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Instructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_11)==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}