#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
int main(void)
{
	Buzzer_Init();
  LightSensor_Init();
	
	while (1)
	{
		if(LightSensor_Get()==1)
			
		{
			Buzzer_ON();
		}
		else{
			Buzzer_OFF();
		}
	}
}
//实现遮住光敏电阻，蜂鸣器响的功能