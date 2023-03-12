#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

//----------CountSensor_Init说明-------------
//初始化时，先配置RCC，把涉及的外设都打开
//第二步，配置GPIO，选择为输入模式
//然后配置AFIO，选择所用的一路GPIO，连接到后面的EXTI
//配置EXTI，选择边沿触发方式
//配置NVIC，选择合适的优先级
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO时钟
	//EXTI时钟不用开。NVIC也是（内核外设）
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	//配置EXIT
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);//连接PB14号口的第14个中断线路
	EXTI_InitTypeDef EXTI_Initstructure;
	EXTI_Initstructure.EXTI_Line=EXTI_Line14;//建议GTD一下EXIT_Line函数，再ctrl+F
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;//建议同上
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_Initstructure);
	
	//配置NVIC，建议GTD一下下列出现的函数，再对应说明里crtl+F一下
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//（相关函数去misc.h找)
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;//配置中断优先级（抢占中断）
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;//配置响应中断
	NVIC_Init(&NVIC_Initstructure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}
	
	
	//以IRQHandler结尾的字符串是中断函数有关的,去startup里看看
	void EXTI15_10_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line14)==SET)	//读取EXTI_Line14的标志位，判断中断标志位是否为1
		{
			
			CountSensor_Count++;
			//每次中断结束，一定要清除中断标志位
			EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志位
		}
	}
	
