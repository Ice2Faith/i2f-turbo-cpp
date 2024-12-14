#include"stm32f10x.h"
#include"led.h"
/*
 Use Sys clock Flash LED light.
*/

//u32 be included in stm32f10x.h by typedef
void delay(u32 t)
{
	while(t--);
}
//target frequence equals HSE frequence /div * pllm
void RCC_HSE_Config(u32 div,u32 pllm) // self set sys clock
	{
		RCC_DeInit(); //reset periph RCC register
		RCC_HSEConfig(RCC_HSE_ON); //open clock which external high speed
		if(RCC_WaitForHSEStartUp()==SUCCESS) //wait hse work
		{
			RCC_HCLKConfig(RCC_SYSCLK_Div1);//set AHB clock,HCLK
			RCC_PCLK1Config(RCC_HCLK_Div2);//set APB1 clock,PLCK1
			RCC_PCLK2Config(RCC_HCLK_Div1);//set APB2 clock,PLCK2
			RCC_PLLConfig(div,pllm);//set PLL clock source and multiply frequence number,function core code
			RCC_PLLCmd(ENABLE);//enable pll
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//check rcc flag bit done
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//set sysclock is pllclk
			while(RCC_GetSYSCLKSource()!=0x08);//use to return sysclock source
		}
	}

//change sys clock to reflect led flash
int main()
{
	//set use HSE div1 and 9mul frequence
	//because of our HSE is 8MHz,9mul=8/1*9=72Mhz
	//mul support:1-16,8*9=72MHz is standard frequence
	//if mul > 9 ,you can implement super frequence,but isn't stability.
	//max frq is 8/1*16=128MHz
	RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_3);//run after SystemInit
	
	LED_Init_LED2();
	int round=6;
	int fqc=0;
	while(1)
	{
		if(fqc==0)
		{
			//8/1*3=24Mhz
			RCC_HSE_Config(RCC_PLLSource_HSE_Div1,RCC_PLLMul_3);
		}
		if(fqc==round/2)
		{
			//8/2*12=48Mhz
			RCC_HSE_Config(RCC_PLLSource_HSE_Div2,RCC_PLLMul_12);
		}
		LED_Light_LED2();
		delay(8*1000*1000/5);
		
		LED_Dark_LED2();
		delay(8*1000*1000/5);
		
		fqc=(fqc+1)%round;
	}
}
