#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//启动时钟，对应GPIOA
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//PP代表推挽输出，此处高低电平都可以点灯
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//设置时钟速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);//设置为低电平
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);//设置为高电平
	while (1)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(1000);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
		Delay_ms(1000);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);//若想将Bit_Set写成1，需要强制类型转换成BitAction的枚举类型，否则会有警告
		Delay_ms(1000);
	}
}
