#include"smg.h"
//nagtive union
u8 g_smg_digarr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,//0-9
0x77,0x7c,0x39,0x5e,0x79,0x71,//a-f
0x00};//none

void SMG_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
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
	SMG_SetDigital(GPIOx,g_smg_digarr[16]);
}
void SMG_SetDigital(GPIO_TypeDef * GPIOx,u8 data)
{
	GPIO_Write(GPIOx,data);
}