#include "at24c02.h"
#include "IIC.h"
#include "usart.h"
#include "delay.h"

void AT24C02_Init(void){

	IIC_Init();

}

u8 	AT24C02_ReadOneByte(u8 addr){

	u8 ask;
	u8 data;
	
	//1.开始
	IIC_Start();
	
	//2.写设备地址（写操作）
	IIC_Write_Byte(0xA0);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return 0;
	}

	//3.写数据地址
	IIC_Write_Byte(addr);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return 0;
	}

	//4.开始
	IIC_Start();
	
	//5.写设备地址（读操作）
	IIC_Write_Byte(0xA1);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return 0;
	}

	//6.读数据
	data = IIC_Read_Byte();
	IIC_Send_NAck();
	
	//7.停止
	IIC_Stop();
	printf("读成功\n");
	return data;
}


void AT24C02_ReadLenByte(u8 addr, u8 *buffer, u16 len){

	u8 ask;
	u16 i = 0;
	
//	for(; i < len; i++){
//	
//		*buffer = AT24C02_ReadOneByte(addr + i);
//		buffer++;
//	}
	
	
	//1.开始
	IIC_Start();
	
	//2.写设备地址（写操作）
	IIC_Write_Byte(0xA0);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return;
	}

	//3.写数据地址
	IIC_Write_Byte(addr);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return;
	}

	//4.开始
	IIC_Start();
	
	//5.写设备地址（读操作）
	IIC_Write_Byte(0xA1);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return;
	}

	//6.读数据
	for(; i < len - 1; i++){
	
		buffer[i] = IIC_Read_Byte();		//连续读取出第一个字符外均为空
		IIC_Send_Ack();

	}
	
	buffer[i] = IIC_Read_Byte();
	IIC_Send_NAck();
	
	
	//7.停止
	IIC_Stop();
	printf("读成功\n");

}
void AT24C02_ReadLenByte_S(u8 addr, u8 *buffer, u16 len){

	u8 ask;
	u16 i = 0;
	
	for(; i < len; i++){
	
		*buffer = AT24C02_ReadOneByte(addr + i);
		buffer++;
		delay_us(5);	//保证器件反应
	}
	
}




void AT24C02_WriteOneByte(u8 addr, u8 data){

	u8 ask;
	
	//1.开始
	IIC_Start();
	
	//2.写设备地址（写操作）
	IIC_Write_Byte(0xA0);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return ;
	}

	//3.写数据地址
	IIC_Write_Byte(addr);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return ;
	}

	//4.写数据
	IIC_Write_Byte(data);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return ;
	}
	
	//5.停止
	IIC_Stop();
	printf("写成功\n");
}

void AT24C02_WriteLenByte(u8 addr, u8 *data, u16 len){

	u8 ask;
	u16 i = 0;
	
	//1.开始
	IIC_Start();
	
	//2.写设备地址（写操作）
	IIC_Write_Byte(0xA0);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return ;
	}

	//3.写数据地址
	IIC_Write_Byte(addr);
	ask = IIC_Wait_Ack();
	if(ask == 1){
		return ;
	}

	//4.写数据
	for(; i < len; i++){
		
		IIC_Write_Byte(data[i]);
		ask = IIC_Wait_Ack();
		if(ask == 1){
			return ;
		}
		
	}

	//5.停止
	IIC_Stop();
	printf("写成功\n");
}

void AT24C02_WriteLenByte_S(u8 addr, u8 *data, u16 len){

	int i = 0;
	
	for(i = 0; i < len; i++){
	
		AT24C02_WriteOneByte(addr++, *(data+i));
		delay_us(5);	//保证器件反应
	}
	

}



