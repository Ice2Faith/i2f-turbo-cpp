#include"stm32f10x.h"
#include"system.h" //actually system.h include stm32f10x.h
#include"led.h" //actually led.h include system.h
//so only led.h is enough
/*
 Use Bit Belt Flash LED light.
*/
void delay(unsigned int t)
{
	while(t--);
}

int main()
{
	LED_Init_LED1();
	LED_Init_LED2();
	
#if 0
	//direct use bit belt
	while(1)
	{
		PBout(5)=0;
		delay(8*1000*1000/5);
		
		PBout(5)=1;
		delay(8*1000*1000/5);
	}
#else
	//use bit belt by define in led.h
	while(1)
	{
		LED2=!LED2;
		delay(8*1000*1000/3);
		
		LED1=!LED1;
		delay(8*1000*1000/3);
	}
#endif
}
