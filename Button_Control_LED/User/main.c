#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h" 
#include "Key.h"
//该项目实现按下PB1按键点亮，按下PB11按键关闭
uint8_t KeyNum;

int main(void)
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ENABLE是个枚举值，也可以GTD一下
	//GPIO_InitTypeDef GPIO_Instructure;//如果你忘记了如何使用结构体，不妨GTD一下GPIO_InitTypeDef去看看
	//GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
	//GPIO_Instructure.GPIO_Pin=GPIO_Pin_1;
	//GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	//GPIO_Init(GPIOC,&GPIO_Instructure);
	//该项目将上面一大段初始化封装扔进了Hardware里的LED
	LED_Init;
	Key_Init;
	while (1)
	{
		//没有外部上拉电源的情况下，采用上拉输入方式控制按键，若有外部上拉，则可以使用浮空输出
		//一般采用下接按键的方式，及按键接地（按下低电平，松开高电平），因为大多单片机有上拉输入模式，但有的没有下拉输入模式
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			LED_ON();
			//LED_Turn();这是实现按一下按钮亮一次的功能，很明显不能和LED_ON什么的同时用
		}
		if(KeyNum==2)
		{
			LED_OFF;
			//LED_Turn();
		}

	}
}
