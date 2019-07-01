#include "sys.h"
#include "delay.h"
#include "usart.h"


void TIM3_init(void);

#define START_TIMING	TIM_Cmd(TIM3, ENABLE)

int main(void)
{
	float float_num = 0.01;
	int	counter = 0;
	delay_init();	    //延时函数初始化	  
	uart_init(115200);
	TIM3_init(); 
	
	printf("stm32F103测试浮点型运算程序\n");
	delay_ms(100);
	while(1){
		
		TIM3->CNT = 0;
		START_TIMING;
		float_num += 0.01f + 0.1*0.1*0.1*0.1*0.1*0.1;
		counter = TIM3->CNT;
		printf("result:%f; time:%d\n", float_num, counter);
		delay_ms(500);
	
	}

}



void TIM3_init(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	//初始化时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	TIM_TimeBaseInitStruct.TIM_Prescaler = 3;	//12M的计数频率
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
}

