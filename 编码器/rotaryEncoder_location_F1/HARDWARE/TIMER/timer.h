#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
	  

//通过改变TIM3->CCR2的值来改变占空比，从而控制LED0的亮度
#define LED0_PWM_VAL TIM3->CCR2 
#define ENCODER_TIM_PERIOD (u16)(65000)   // number of pulses per revolution
#define COUNTER_RESET   (u16)0
#define MAX_COUNT 3000
#define B_Dir PBout(5)	// PB5

void TIM4_Init(u16 arr, u16 psc ,u32 count);
void Timerx_Init(u16 arr,u16 psc);
void PWM_Init(u16 arr,u16 psc);
void Encoder_Init(void);
s16  Enc_GetCount(void);

#endif























