#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InternalClockConfig(TIM2);//选择TIM2为内部时钟,不写这也行，默认内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//很常见不是么，万能构造结构体进行初始化
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//相关参数配置建议GTD一下，然后去看注释并ctrl+f去找对应的值
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//选择向上计数，相关配置同上去查找
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;//这俩参数决定定时时间,此处设定定时时间为1秒，即定时频率为1hz（1Mhz=10^6hz）
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//公式：定时频率=72M/(PSC+1)/(ARR+1)
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