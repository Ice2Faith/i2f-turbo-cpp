#include"stm32f10x_register.h"

#if 1
//boot function first run before main function on system on
//usually to init sysclock or io port etc.
void SystemInit()
{
	
}

void delay(unsigned int time)
{
	while(time--);
}

void enableClockPi(int i) //open gpio clock i(i==0 mean PA ,1=PB,...)
{
	//open gpio clock,4th bit set 1 to open,0 to close
	*RCC_APB2ENR |=0x01 <<(2+i); //A==2,b==3,...
}
void setPijOutput(unsigned int * pi_bssr,int num,int is1)
{
		if(is1)
			*pi_bssr |=(0x01<<(16+num));//GPIOx_BSRR high 16 bit set 1 hight elec out
		else
			*pi_bssr |=(0x01<<(0+num));//GPIOx_BSRR low 16 bit set 1 low elec out
}
void setOutputEnable(unsigned int * pi_crl,int num)
{
	if(num<=7)
	{
		*pi_crl &=~(0xf<<(4*num)); //set target 4 bit to b0000,every 4 bit control a mode
		*pi_crl|=(0x3<<(4*num));//set target 4bit's low 2 bit to b11
	}else
	{
		//int pointer add 4 byte actually only add 1 for int pointer,1 int==4byte
		*(pi_crl+0x01) &=~(0xf<<(4*(num-8))); //set target 4 bit to b0000,every 4 bit control a mode
		*(pi_crl+0x01)|=(0x3<<(4*(num-8)));//set target 4bit's low 2 bit to b11
	}
}
// enable a port
enum GPI{GPA,GPB,GPC,GPD,GPE,GPF,GPG};
int main()
{
	//default led light
	GPIORegister regB;
	InitRegister(&regB,GPIOB_BASE);
	GPIORegister regE;
	InitRegister(&regE,GPIOE_BASE);
	enableClockPi(GPB);
	setOutputEnable(regB.CRL,5);
	setPijOutput(regB.BSRR,5,1);
	enableClockPi(GPE);
	setOutputEnable(regE.CRL,5);
	setPijOutput(regE.BSRR,5,1);
	int trunLed=0;
	
	GPIORegister reg;
	InitRegister(&reg,GPIOF_BASE);
	int num=14;
	
	
	enableClockPi(GPF);
	
	//set gpio work mode
	setOutputEnable(reg.CRL,num);
	
	unsigned int delaytm=8*1000*1000/5; //1Mhz=1Khz=1000Hz 1hz means vary times during one second
	//light dark loop
	while(1)
	{
		//delay some time
		delay(delaytm);
		
		//set out put
		if(trunLed==0)
			setPijOutput(reg.BSRR,num,1);
		else if (trunLed==1)
			setPijOutput(regB.BSRR,5,1);
		else
			setPijOutput(regE.BSRR,5,1);
	
		delay(delaytm);
		
		setPijOutput(reg.BSRR,num,0);
		setPijOutput(regB.BSRR,5,0);
		setPijOutput(regE.BSRR,5,0);
		
		trunLed=(trunLed+1)%3;
	}
	
	return 0;
}

#endif


