#include"stm32f10x.h"
/*
	About:
		implement the most simple use case which flash a led on PB5 port.
		
*/
//system initial function before main() execute must be declared although not any code in it.
void SystemInit()
{
	
}

//need it to implement flash led light
//virtual a delay method by vacant running cpu clock although not exactness
void delay(unsigned int time)
{
	while(time--);
}

int main()
{
	//first,need to enable GPIO bus clock for GPIOB
	//GPIOB clock on APB2 bus,APB2ENR is the clock manager address
	//GPIOB be controled by APB2ENR register 3rd bit,which 1 open clock,0 close it.
	//this bit and register can get by chip doc.
	*RCC_APB2ENR |=0x01 <<(2+1);
	
	//second,to configue port register for need to use PB5 output
	//use GPIOB config register low 8 bit by CRL register for PB5's 5 in low 8 bit
	//set output mode is vary output mode value to b00
	//set output speed to 50MHz value to b11
	//so set 4bit value to b0011
	//and,5,so left move 5*4 bit ,because of every 4bit control a port mode
	//CRL control low 8bit,CRH control heigh 8bit(4bit*8=32bit)
	*GPIOB_CRL &=~(0xf<<(4*5)); //0xf==b1111 ~0xf=1111...110000 set 4bit from 4bit*5 begin value to b0000 
	*GPIOB_CRL|=(0x3<<(4*5));
	
	//now,flashing a led PB5 port , light and dark 1 sec vary one time.
	while(1)
	{
		//BSRR register is control port bit set/reset
		//heigh 16bit set 1 to set output 1
		//low 16bit set 1 to set output 0
		//because of PB5,so to control 5th bit(and 16+5th)
		*GPIOB_BSRR |=(0x01<<(16+5));
		delay(8*1000*1000);//chip clock is 8MHz,every second triger 8M times,1M=1000K 1K=1000
		
		*GPIOB_BSRR |=(0x01<<(0+5));
		delay(8*1000*1000);
	}
	
	return 0;
}

