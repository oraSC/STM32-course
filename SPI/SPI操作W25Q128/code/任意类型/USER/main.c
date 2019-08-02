#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "spi.h"
#include "w25qxx.h"
#include "key.h"  


//ALIENTEK 探索者STM32F407开发板 实验25
//SPI通信接口实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK
 
 
 
//要写入到W25Q16的字符串数组
const u8 TEXT_Buffer[]={"Explorer STM32F4 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
	
int main(void)
{ 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);     //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	//LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化 
	//KEY_Init(); 				//按键初始化  
	W25QXX_Init();			//W25QXX初始化
 	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"SPI TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	LCD_ShowString(30,130,200,16,16,"KEY1:Write  KEY0:Read");	//显示提示信息		
	while(W25QXX_ReadID()!=W25Q128)								//检测不到W25Q128
	{
		LCD_ShowString(30,150,200,16,16,"W25Q128 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,"Please Check!      ");
		delay_ms(500);
		LED0=!LED0;		//DS0闪烁
	}
	LCD_ShowString(30,150,200,16,16,"W25Q128 Ready!"); 
	FLASH_SIZE=16*1024*1024;	//FLASH 大小为16字节
  	POINT_COLOR=BLUE;			//设置字体为蓝色	  
	//while(1)
	{
		
		
		
		//写入数据
		{
			char num_char = 'a';
			int num_int = 100;
			float num_float = -1.456;
			
			W25QXX_Write((u8*)&num_char, 0, sizeof(char));	
			printf("FLASH写入字符型数据完成:%c\n", num_char);
			
			W25QXX_Write((u8*)&num_int, 10, sizeof(int));	
			printf("FLASH写入整型数据完成:%d\n", sizeof(double));
			
			W25QXX_Write((u8*)&num_float, 20, sizeof(float));	
			printf("\nFLASH写入浮点型数据完成:%f\n\n", num_float);
		
		
		}
		delay_ms(5000);
		//读出数据
		{
			char num_char_out = 0;
			int num_int_out = 0;
			float num_float_out = 0.0;
			
			W25QXX_Read((u8*)&num_char_out, 0, sizeof(char));
			printf("FLASH读入字符型数据完成:%c\n", num_char_out);
			delay_ms(20);			//串口不加延时，会换行失败（仅仅美观）
			
			W25QXX_Read((u8*)&num_int_out, 10, sizeof(int));
			printf("FLASH读入整型数据完成:%d\n", num_int_out);
			delay_ms(20);			//串口不加延时，会换行失败（仅仅美观）
			
			W25QXX_Read((u8*)&num_float_out, 20, sizeof(float));
			printf("FLASH读入浮点型数据完成:%f\n", num_float_out);
		} 
		
			   
	}
		while(1);
}

