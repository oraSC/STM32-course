#ifndef _IIC_H_
#define _IIC_H_
/*
*author:oraSC
*github:https://github.com/oraSC
*功能描述：使用IO模拟的IIC总线接口
*日期：2019/6/26
*/
#include "stm32F4xx.h"
#include "sys.h"

#define SDA_OUTPUT()	{GPIOB->MODER &= ~(((uint32_t)GPIO_MODER_MODER0) << (GPIO_Pin_9 * 2));GPIOB->MODER |= (((uint32_t)GPIO_Mode_OUT) << (GPIO_Pin_9 * 2));}
#define SDA_INPUT()		{GPIOB->MODER &= ~(((uint32_t)GPIO_MODER_MODER0) << (GPIO_Pin_9 * 2));GPIOB->MODER |= (((uint32_t)GPIO_Mode_IN) << (GPIO_Pin_9 * 2));}

#define SCL		PBout(8)
#define SDA_IN	PBin(9)
#define SDA_OUT	PBout(9)


void 	IIC_Init(void);
void 	IIC_Start(void);
void 	IIC_Stop(void);
void 	IIC_Write_Byte(u8 data);
u8		IIC_Read_Byte(void);
u8		IIC_Wait_Ack(void);
void 	IIC_Send_Ack(void);
void	IIC_Send_NAck(void);

#endif
