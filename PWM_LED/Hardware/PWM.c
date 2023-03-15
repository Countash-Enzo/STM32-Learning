#include "stm32f10x.h"                  // Device header

//1、RCC开启时钟，把TIM外设和GPIO外设时钟打开
//2、配置时基单元，包含ARR CNT PSC等参数
//3、配置输出比较单元，包括CCR值 输出比较模式、极性选择、输出使能等参数
//4、配置GPIO，推挽输出模式（PWM与GPIO的对应关系看引脚图）
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO时钟
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//查一下重映射和引脚更改的关系表,这里选择部分重映射1，把PA0换到PA15
	//还需要关闭PA15端口作为调试端口的复用
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//这里我关闭了SWD调试，因为我没STLINK，只能用J-Tag烧录，如果选择GPIO_Remap_SWJ_JTAGDisable，那玩个锤子
	//上面这两句重映射有关的，把PA15 PB3 PB4三个引脚当做GPIO来使用，如果想测试代码效果，解除注释，将GPIO_Pin_0改成GPIO_Pin_15
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//选择复用推挽输出，因为要让定时器来控制引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//周期ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//PSC，现在是频率为1khz，要占空比为50%的波形，则CCR为50
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//给结构体一个初始值，如果不想給所有结构体成员都单独列一遍赋值就这么干，后面再单独对要修改的结构体成员进行赋值
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//设置输出比较极性，High为有效电平为高电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable ;//设置输出使能（当然是ENABLE咯）
	TIM_OCInitStructure.TIM_Pulse=0;//设置CCR，建议GTD一下，同时可以看到以上多个成员的值
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);//初始化输出比较通道
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);//设置CCR寄存器的值
}