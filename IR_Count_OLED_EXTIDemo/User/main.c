#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CounterSensor.h"
int main(void)
{
	OLED_Init();
	CountSensor_Init();
	//OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,1,"Count:");
	//OLED_ShowNum(2,1,12345,5);
	//OLED_ShowSignedNum(2,7,-66,2);
	
	
	//OLED_Clear();
	while (1)
	{
		OLED_ShowNum(1,7,CountSensor_Get(),5);
	}
}

//本项目是个简单的中断触发项目。
//当移开对射式红外传感器前的挡光片时，OLED上显示的计数+1
//移开+1采用的下降沿触发，若要改为挡住+1则采用上升沿（当然你也可以改成上升下降都触发）