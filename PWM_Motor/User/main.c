#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "Key.h"
#include "OLED.h"

int8_t Speed;
uint8_t Key_Num;
int main(void)
{
	Motor_Init();
	Key_Init();
	//Motor_SetSpeed(50);//通过加大频率来避免电机发出的蜂鸣器般的声音被人耳听到，故修改分频，减小预分频器，使频率去到20khz以上
	OLED_ShowString(1,1,"Speed");
	
	while (1)
	{
   Key_Num=Key_GetNum();
		if(Key_Num==1)//有点像档位不是么
		{
			Speed+=20;
			if(Speed>100)
			{
				Speed=-100;
			}
			Motor_SetSpeed(50);
			OLED_ShowSignedNum(1,7,Speed,3);
		}
	}
}
//用到了TB啥电机驱动模块，注意接线什么的，参考PPT相关