#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "ROTARYENCODER.h"
#include "lcd.h"

u32 counter;

int main(void)
{
	u16 currentCount = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LCD_Init();
	POINT_COLOR=RED;      //画笔颜色：红色
	rotaryEncoder_init();
	
	while(1)
	{
 		delay_ms(1000);
		currentCount = TIM3 -> CNT;
		printf("编码器计数值为：%d \n",currentCount+1);	   
	}
}
