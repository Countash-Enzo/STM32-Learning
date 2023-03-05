#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;//仍然是推挽输出
	GPIO_Instructure.GPIO_Pin=GPIO_Pin_All;//配置GPIOA的所有Pin
	//GPIO_Instructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//初始化三个端口，按位或，同理RCC_APB2Periph_GPIOA以及SetBits也能这么操作，不信go to defination
	GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Instructure);//别忘了初始化上面的配置，用结构体GPIO_Instructure的好处在于，初始化这个结构体就行了，不用一句一句初始化
	while (1)
	{
		//GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
		GPIO_Write(GPIOA,~0x0001);//0000 0000 0000 0001这16个2进制对应PA0到PA15共16个端口，可以去gpio.h里看Pin对应的地址，因为低电平点亮，前面加上“~”按位取反的符号，此段让第一个LED亮
		Delay_ms(1000);
			GPIO_Write(GPIOA,~0x0002);//0000 0000 0000 0010
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0004);//0000 0000 0000 0100
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0008);//0000 0000 0000 1000
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0010);//0000 0000 0001 0000
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0020);//0000 0000 0010 0000
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0040);//0000 0000 0100 0000
		Delay_ms(1000);
		GPIO_Write(GPIOA,~0x0080);//0000 0000 1000 0000
		Delay_ms(1000);

	}
}
