#include "IIC.h"
#include "delay.h"

void IIC_Init(void){

	GPIO_InitTypeDef  GPIO_InitStruct;
	//使能GPIPF
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	//初始GPIGB8 GPIGB9 
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_8 | GPIO_Pin_9; 	 //引脚9
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT; //输出
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD; //开漏输出
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz; //速度
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;   //上拉
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化总线->空闲状态
	SDA_OUTPUT();
	SCL = 1;
	SDA_OUT = 1;
	
}
	

void IIC_Start(void){

	//输出模式
	SDA_OUTPUT();
	
	//1.总线空闲
	SDA_OUT = 1;
	SCL = 1;
	delay_us(5);
	
	//2.SDA电平跳变	H -> L
	SDA_OUT = 0;
	delay_us(5);
	
	//3.占据时钟总线
	SCL = 0;
	
}


void IIC_Stop(void){

	//输出模式
	SDA_OUTPUT();
	
	//1.钳住总线同时SDA为零
	SDA_OUT = 0;
	SCL = 0;
	delay_us(5);
	
	//2.SCL、SDA电平跳变 L ->	H
	SCL = 1;
	SDA_OUT = 1;
	delay_us(5);

}
		
void IIC_Write_Byte(u8 data){

	int i = 7;
	//输出模式
	SDA_OUTPUT();
	
	
	//一个字节八位，循环八次
	SCL = 0;
	for(; i >= 0; i--){
		
		SCL = 0;
		//判断当前数据位：高位在前、低位在后
		if((data & (1<<i))){
		
			SDA_OUT = 1;
		}
		else{
		
			SDA_OUT = 0;
		}
		delay_us(5);	//此处不知道为什么要延时 1.构成脉冲周期
		SCL = 1;
		delay_us(5);
		
		//3.钳住总线
		SCL = 0;	
	}

	//3.占据时钟总线，释放数据总线
	SCL = 0;
	SDA_OUT	= 1;
}
	
u8	IIC_Read_Byte(void){

	u8 data = 0;
	int i = 7;
	
	//输入模式
	SDA_INPUT();
	
	//一个字节八位，循环八次
	SCL = 0;
	for(; i >= 0; i--){
		
		//低电平准备数据
		delay_us(5);
		
		//判断当前数据位：高位在前、低位在后
		SCL = 1;
		if(SDA_IN){
		
			data |= (1 << i);
		}
		delay_us(5);
		
		//3.钳住总线
		SCL = 0;	
	}

	//4.占据时钟总线，释放数据总线
	SCL = 0;
	SDA_OUT	= 1;
	return data;
}
	
	
u8	IIC_Wait_Ack(void){

	u8 ask = 0;
	
	//输入模式
	SDA_INPUT();

	//1.准备ask
	SCL = 0;
	delay_us(5);
	
	//2.读取ASK
	SCL = 1;
	if(SDA_IN == 1){
		ask = 1;
	}
	else ask = 0;
	delay_us(5);
	
	//3.占据时钟总线，释放数据总线
	SCL = 0;
	SDA_OUT	= 1;
	return ask;
	
	
}
	
void IIC_Send_Ack(void){

	//输出模式
	SDA_OUTPUT();
	
	//1.准备数据
	SCL = 0;
	SDA_OUT = 0;
	delay_us(5);	
	
	//2.发送ASK
	SCL = 1;
	delay_us(10);
	
	//3.占据时钟总线，释放数据总线
	SCL = 0;
	SDA_OUT	= 1;

}
	
	
	
void IIC_Send_NAck(void){

	//输出模式
	SDA_OUTPUT();
	
	//1.准备数据
	SCL = 0;
	SDA_OUT = 1;
	delay_us(5);	
	
	//2.发送NASK
	SCL = 1;
	delay_us(5);
	
	//3.占据时钟总线，释放数据总线
	SCL = 0;
	SDA_OUT	= 1;
}
