#include"stm32f10x.h"
#include"led.h"
/*
 Use Sys Function Flash LED light.
*/
void delay(unsigned int t)
{
	while(t--);
}

int main()
{
#if 1
	LED_Init_LED1();
	LED_Init_LED2();
	
	int turnId=0;
	while(1)
	{
		if(turnId)
			LED_Light_LED1();
		else
			LED_Light_LED2();
		delay(8*1000*1000/3);
			
		if(turnId)
			LED_Dark_LED1();
		else
			LED_Dark_LED2();
		delay(8*1000*1000/3);
		turnId=(turnId+1)%2;
			
	}
#else
	
	//enable PB and PE clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//fill struct
	GPIO_InitTypeDef initStc;
	initStc.GPIO_Pin=GPIO_Pin_5;
	initStc.GPIO_Speed=GPIO_Speed_50MHz;
	initStc.GPIO_Mode=GPIO_Mode_Out_PP;
	
	//because of LED1:PB5 LED2:PE5 both equals output args
	GPIO_Init(GPIOB,&initStc);
	GPIO_Init(GPIOE,&initStc);
	
	//control LED1 and LED2 turn light
	int trunId=0;
	while(1)
	{
		//light LED
		if(trunId)
			GPIO_SetBits(GPIOB,GPIO_Pin_5);
		else
			GPIO_SetBits(GPIOE,GPIO_Pin_5);
		delay(8*1000*1000/4);
		
		//dark LED
		if(trunId)
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		delay(8*1000*1000/2);
		
		trunId=!trunId;
	}
	
#endif
}
