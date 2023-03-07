#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Instructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_1);//设置高电平让LED熄灭
}

void LED_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
}

void LED_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
}

void LED_Turn(void)//实现端口电平翻转
{
	if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1)==0)//读取当前端口电平输出状态，输出为1就置0
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	}
}