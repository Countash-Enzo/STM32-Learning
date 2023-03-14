#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main(void)
{
	Timer_Init();
	OLED_Init();
	
	OLED_ShowString(1,1,"Num:");
	OLED_ShowString(2,1,"CNT:");
	
	while (1)
	{
		OLED_ShowNum(1,5,Num,5);
    OLED_ShowNum(2,5,Timer_GetCounter(),5);//看一下CNT计数器的计数变化，他会一直到自动重装值（这里我们写的10000-1）
	}

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//获取中断标志位
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位，这很重要！！
	}
}
//本项目是个简单的定时器计数，利用外部时钟。
//根据红外对射传感器手动模拟的外部时钟，频率由手动来模拟
//遮挡一次，CNT会+1（因为没有预分频，如果有预分频比如2分频就是遮挡2次CNT+1），到自动重载值上限9的时候，Num+1
