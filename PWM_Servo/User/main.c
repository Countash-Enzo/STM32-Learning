#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"
#include "Key.h"
#include "OLED.h"

float Angle;
uint8_t Key_Num;
int main(void)
{
	Servo_Init();
	Key_Init();
	Servo_SetAngle(0);
	OLED_Init();
	OLED_ShowString(1,1,"Angle:");
	while (1)
	{
   Key_Num=Key_GetNum();
		if(Key_Num==1)
		{
			Angle+=30;
			if(Angle>180)
			{
				Angle=0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1,7,Angle,3);
	}
}
