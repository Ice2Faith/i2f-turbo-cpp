#include"key.h"
#include"systick.h"

void KEY_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin,uint8_t inputMode)
{
		//enable sys clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph,ENABLE);
	
	GPIO_InitTypeDef initStc;
	initStc.GPIO_Pin=GPIO_Pin;
	initStc.GPIO_Speed=GPIO_Speed_50MHz;//actually input is none nessasary,can remove
	initStc.GPIO_Mode=inputMode;
	
	//init gpiox
	GPIO_Init(GPIOx,&initStc);
}

// mode=0 single scan,mode=1 multiply scan
uint8_t KEY_scan(uint8_t scanMode,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin,uint8_t heighElec)
{	static int notDown=1;
	if(notDown==1 && GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==heighElec)
	{
		//delay_ms(10);//I don't kown why cannot work after add delay.
		notDown=0;
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==heighElec)
		{
			return 1;
		}
	}else if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)!=heighElec)
	{
		notDown=1;
	}
	if(scanMode==1)
	{
			notDown=1;
	}
	return 0;
}   