#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include"stm32f10x.h"

void SysTick_Init(u8 SYSCLK);
void delay_us(u32 nus);//max value is 2^24*8/SYSCLK
void delay_ms(u16 nms);//max value is 2^24*8*1000/SYSCLK=1864ms
void delay_anyms(u32 nms);

#endif // _SYSTICK_H_
