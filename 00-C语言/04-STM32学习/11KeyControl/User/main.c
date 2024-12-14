#include"led.h" 
#include"key.h"
#include"systick.h"
/*
 Use Key Flash LED light.
*/

extern u8 g_smg_digarr[];
int main()
{
	LED_INIT();
	KEY_INIT();
	

	while(1)
	{
		if(KEY_SCAN_KEY1(0))
			LED1=0;
		else
			LED1=1;
		
		if(KEY_SCAN_KEY0(0))
			LED2=0;
		else
			LED2=1;
		
		if(KEY_CK_WKUP)
			LED2=0,LED1=0;
		else
			LED2=1,LED1=1;
		
		//delay_ms(10); //I don't kown why cannot work after add delay.
		
	}
}
