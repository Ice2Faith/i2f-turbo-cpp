#include"smg.h"
#include"led.h" 
/*
 Use Bit Belt Flash LED light.
*/
void delay(unsigned int t)
{
	while(t--);
}
extern u8 g_smg_digarr[];
int main()
{
	LED_Init_LED2();
	SMG_INIT();
	u8 i=0;
	while(1)
	{
		LED2=!LED2;
		SMG_SETDIGITAL(g_smg_digarr[i]);
		delay(8*1000*1000/3);
		i=(i+1)%17;
	}
}
