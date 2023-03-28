#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Instructure);
	PWM_Init();
}

void Motor_SetSpeed(int8_t Speed)
{
	if(Speed>=0)//正转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(Speed);
	}
	else//反转
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		PWM_SetCompare3(-Speed);//此处Speed为负数，而SetCompare只能传正数，所以加负号
	}
}