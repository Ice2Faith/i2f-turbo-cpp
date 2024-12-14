#include"led.h" //actually led.h include system.h
#include"systick.h"
//so only led.h is enough
/*
 Use Sys Tick Timer Flash LED light.
*/

int main()
{
	LED_Init_LED1();
	LED_Init_LED2();
	
	//default frequence is 72MHz
	SysTick_Init(72);

	while(1)
	{
		LED2=!LED2;
		delay_anyms(500);
		
		LED1=!LED1;
		delay_ms(500);
	}

}
