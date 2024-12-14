#include"beep.h"

void Beep_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	//enable sys clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
	
	GPIO_InitTypeDef initStc;
	initStc.GPIO_Pin=GPIO_Pin;
	initStc.GPIO_Speed=GPIO_Speed_50MHz;
	initStc.GPIO_Mode=GPIO_Mode_Out_PP;
	
	//init gpiox
	GPIO_Init(GPIOx,&initStc);
	//init led to dark
	Beep_off(GPIOx,GPIO_Pin);
}
void Beep_off(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	//by BSRR register
	GPIO_SetBits(GPIOx,GPIO_Pin);
}
void Beep_on(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}