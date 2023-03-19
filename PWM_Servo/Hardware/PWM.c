#include "stm32f10x.h"                  // Device header

//1、RCC开启时钟，把TIM外设和GPIO外设时钟打开
//2、配置时基单元，包含ARR CNT PSC等参数
//3、配置输出比较单元，包括CCR值 输出比较模式、极性选择、输出使能等参数
//4、配置GPIO，推挽输出模式（PWM与GPIO的对应关系看引脚图）
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择复用推挽输出，因为要让定时器来控制引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;//周期ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;//PSC，现在是频率为1khz，要占空比为50%的波形，则CCR为50
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//给结构体一个初始值，如果不想給所有结构体成员都单独列一遍赋值就这么干，后面再单独对要修改的结构体成员进行赋值
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//设置输出比较极性，High为有效电平为高电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable ;//设置输出使能（当然是ENABLE咯）
	TIM_OCInitStructure.TIM_Pulse=0;//设置CCR，建议GTD一下，同时可以看到以上多个成员的值
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);//初始化输出比较通道2（一个通道对应一个PWM，需要多个的话，同时初始化其它的）
	//不同通道占空比可以自己设定（改变CCR），但是共用一个计数器，频率必须是一样的，同一定时器多个通道就是这样（当然驱动舵机没啥事）
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);//设置CCR寄存器的值
}