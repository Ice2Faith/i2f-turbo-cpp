#include"systick.h"

static u16 fac_us;
static u16 fac_ms;
void SysTick_Init(u8 SYSCLK)
{
	//need include mimc.c at StdPeriph_Driver
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//use div8 frequence 9MHz
	fac_us=SYSCLK/8;//get one us used tick times
	fac_ms=(u16)fac_us*1000;//get one ms used tick times
}
void delay_us(u32 nus)//max value is 2^24*8/fac_us
{
	u32 temp;
	SysTick->LOAD=nus*fac_us;//reload time
	SysTick->VAL=0x00;//clear tick
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//begin tick
	do
	{
		temp=SysTick->CTRL;//countflag is on bit 16
	}while((temp&0x01) && !(temp&(1<<16))); //wait time arrive
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//close tick
	SysTick->VAL=0x00;//clear tick
}
void delay_ms(u16 nms)//max value is 2^24*8*1000/SYSCLK=1864ms
{
	u32 temp;
	SysTick->LOAD=(u32)nms*fac_ms;//reload time
	SysTick->VAL=0x00;//clear tick
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//begin tick
	do
	{
		temp=SysTick->CTRL;//countflag is on bit 16
	}while((temp&0x01) && !(temp&(1<<16))); //wait time arrive
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;//close tick
	SysTick->VAL=0x00;//clear tick
}
void delay_anyms(u32 nms)
{
	while(nms>0)
	{
		if(nms>1000)
		{
			delay_ms(1000);
			nms-=1000;
		}else
		{
			delay_ms(nms);
			nms=0;
		}
	}
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
