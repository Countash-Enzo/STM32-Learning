#include "stm32f10x.h"                  // Device header
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Instructure);
}

uint8_t Key_GetNum(void)//读取键码
{
	uint8_t KeyNum=0;//键码
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	//GPIO_ReadInputDataBit读取输入数据寄存器的某一位，去掉函数后的Bit则是读取在整个输入数据寄存器
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);//消抖
		Delay_ms(20);
		KeyNum=1;
	}
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);//消抖
		Delay_ms(20);
		KeyNum=2;
	}
	return KeyNum;
}