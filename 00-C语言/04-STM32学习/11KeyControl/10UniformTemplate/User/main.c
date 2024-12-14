#include"smg.h"
#include"led.h" 
#include"systick.h"
#include"beep.h"
/*
 Use Bit Belt Flash LED light.
*/

extern u8 g_smg_digarr[];
int main()
{
	RCC_HSE_CONFIG(1,12);
	SysTick_Init(8/1*12);
	LED_INIT();
	SMG_INIT();
	BEEP_INIT();
	u8 i=0;
	while(1)
	{
		LED2=!LED2;
		LED1=!LED1;
		SMG_SETDIGITAL(g_smg_digarr[i]);
		BEEP=!BEEP;
		delay_anyms(300);
		i=(i+1)%17;
	}
}
