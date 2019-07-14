//author:ora
//email:1301912993@qq.com

#include "ROTARYENCODER.h"
#include "usart.h"
#include "lcd.h"


#define ENCODER_TIM_PERIOD (u16)(65000)
#define COUNTER_RESET   (u16)30000

void rotaryEncoder_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//PA6、PA7输入模式
	GPIO_InitStructure.GPIO_Speed         = GPIO_Speed_100MHz;       
	GPIO_InitStructure.GPIO_Mode         = GPIO_Mode_AF;       
	GPIO_InitStructure.GPIO_OType         = GPIO_OType_OD;       
	GPIO_InitStructure.GPIO_Pin         = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//启动GPIO复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	

	/* Timer configuration in Encoder mode */ 
//	TIM3->PSC = 0x0;//预分频器
//	TIM3->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
//	TIM3->CR1 &=~(3<<8);// 选择时钟分频：不分频
//	TIM3->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
	
	//配置定时器
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//配置编码器模式
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
	
	//设置输入捕获滤波器
	TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 6;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);	
		
	//设置初始值、使能计时器
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1，使能定时器

}

