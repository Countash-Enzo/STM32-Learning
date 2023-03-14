#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;//手册里建议浮空输入，但我们选择上拉，若外部输入信号很小，可以选择浮空输入
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);//选择TIM2为外部时钟,建议GTD看注释，第二个参数是不选择外部触发预分频器，最后一个参数是外部触发滤波器有关，这里直接拉满嘿嘿（主要是消抖），要用对照手册去看
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//很常见不是么，万能构造结构体进行初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//相关参数配置建议GTD一下，然后去看注释并ctrl+f去找对应的值
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//选择向上计数，相关配置同上去查找
	TIM_TimeBaseInitStructure.TIM_Period=10-1;//自动重载值，这俩参数决定定时时间,此处设定CNT加到10就清0，然后中断进去加1
	TIM_TimeBaseInitStructure.TIM_Prescaler=1-1;//预分频给1，不分频
	//公式：定时频率=72M/(PSC+1)/(ARR+1)
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器，这里不需要，置零
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化时基单元，老操作了
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清除更新中断标志位，避免刚初始化完就进中断
	//不加这句会导致上电直接从1开始计时而非0开始计时，为什么会这样呢？TIM_TimeBaseInit函数里最后有一句
	//TIMx->EGR = TIM_PSCReloadMode_Immediate; 
	//注释里写的是更新中断后立刻重新加载预分频器与重复计数器，意味着一旦初始化完成，更新中断就会立刻进入
	
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;//配置中断优先级（抢占中断）
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=1;//配置响应中断
	NVIC_Init(&NVIC_Initstructure);

  TIM_Cmd(TIM2,ENABLE);//启动定时器
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//获取中断标志位
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位，这很重要！！
//	}
//}

//如果想在main.c里使用TIM2_IRQHandler这个函数，只能把TIM2_IRQHandler这函数部分完整的复制过去，然后在上面加功能！！
//比如执行Num++啥的，这个函数只是一个读取标志位后清除标志位的功能，函数内部是没有其它功能的！
//相当于一个框架，往里面加东西得靠自己，所以注释掉这个函数，要用时放入main.c里，自己加功能