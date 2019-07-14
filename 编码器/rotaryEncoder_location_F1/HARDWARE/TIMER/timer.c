


#include "timer.h"


void Encoder_Init(void)
{
	/* TIM3 clock source enable */ 
	RCC->APB1ENR|=1<<1;       //TIM3时钟使能
	/* Enable GPIOA, clock */
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟

	/* Configure PA.06,07 as encoder input */
	GPIOA->CRL&=0XF0FFFFFF;//PA6
	GPIOA->CRL|=0X04000000;//浮空输入
	GPIOA->CRL&=0X0FFFFFFF;//PA7
	GPIOA->CRL|=0X40000000;//浮空输入


	/* Timer configuration in Encoder mode */ 
	TIM3->PSC = 0x0;//预分频器
	TIM3->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
	TIM3->CR1 &=~(3<<8);// 选择时钟分频：不分频
	TIM3->CR1 &=~(3<<5);// 选择计数模式:边沿对齐模式
		
	TIM3->CCMR1 |= 1<<0; //CC1S='01' IC1FP1映射到TI1
	TIM3->CCMR1 |= 1<<8; //CC2S='01' IC2FP2映射到TI2
	TIM3->CCER &= ~(1<<1);	 //CC1P='0'	 IC1FP1不反相，IC1FP1=TI1
	TIM3->CCER &= ~(1<<5);	 //CC2P='0'	 IC2FP2不反相，IC2FP2=TI2
	TIM3->CCMR1 |= 3<<4; //	IC1F='1000' 输入捕获1滤波器
	TIM3->SMCR |= 3<<0;	 //SMS='011' 所有的输入均在上升沿和下降沿有效
	TIM3->CNT = COUNTER_RESET;
	TIM3->CR1 |= 0x01;    //CEN=1，使能定时器
}
















