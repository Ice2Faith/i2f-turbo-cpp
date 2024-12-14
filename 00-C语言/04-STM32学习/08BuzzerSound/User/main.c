#include"led.h" //actually led.h include system.h
#include"systick.h"
#include"beep.h"
#include<time.h>
#include<stdlib.h>
//so only led.h is enough
/*
 Use Sys Tick Timer Flash LED light.
*/

int main()
{
	LED_Init_LED2();
	
	BEEP_INIT();
	//default frequence is 72MHz
	SysTick_Init(72);
	
	srand(0x56);
	while(1)
	{
		BEEP=!BEEP;
		
		LED2=!LED2;
		delay_anyms(rand()%340+60);
		
	}

}
