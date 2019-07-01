#include "stm32f4xx.h"
#include "usart.h"
#include "at24c02.h"
#include "delay.h"
#include "string.h" 

int main(void)
{
	u8 ch;
	u8 str1[20] =  "12345678";
	u8 str2[50] = "1234567890ABCDEF";
	u8 str[50] = {0};
	u8 str3[50] = {0};
	
	//初始化
	uart_init(115200);
	delay_init(168);
	AT24C02_Init();
	
//	AT24C02_WriteOneByte(0x03, '6');
//	delay_ms(50);	//必须延时不然出错
//	ch = AT24C02_ReadOneByte(0x03);
//	printf("\nch=%c", ch);
	
	AT24C02_WriteLenByte(0x00, str1, 8);
	delay_ms(50);
	AT24C02_ReadLenByte(0x00, str, 8);
	delay_ms(50);
	printf("str=%s\n", str);
	
	
	AT24C02_WriteLenByte_S(0x10, str2, 16);
	delay_ms(50);
	AT24C02_ReadLenByte_S(0x10, str3, 16);
	delay_ms(50);
	printf("str3=%s\n", str3);
	
	
	
	while(1);

}
