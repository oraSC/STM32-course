#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "timer.h"	 	 
	  
int main(void)
{			
 	u16 currentCount;
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	Encoder_Init();

   	while(1)
	{
 		delay_ms(1000);
		currentCount = TIM3 -> CNT;
		printf("编码器计数值为：%d \n",currentCount+1);	   
	}	 
}

























