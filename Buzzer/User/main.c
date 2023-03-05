#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Instructure);
	
	
	while (1)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);//让蜂鸣器响
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);//让它别响，这样交替就形成了蜂鸣器
		Delay_ms(500);
		//若想有段落节奏的响，上面两行copy下来，改改延时即可
	}
}
