#ifndef _STM32F10X_REGISTER_H_
#define _STM32F10X_REGISTER_H_
/*
notice:
must care the pointer type when you add a value to pointer.
example:
add 1 to a int pointer equals add 4 to a byte pointer
code case:
int * pi=(int *)0x40000000;
p+=1;//pi==0x40000004

char * pb=(char *)0x40000000;
p+=4;//pb=0x40000004;

so,pi equals pb,must remmeber it.
*/
//find this address by chip document
//GPIO external device is on APB2 bus
#define PERIPH_BASE 		((unsigned int)0x40000000) 		//0x4000 0000 external divice base address
#define APB2PERIPH_BASE 	(PERIPH_BASE+0x00010000) 		//0x4001 0000 apb2 bus base address

//need a clock of APB2 bus to drive GPIO port
#define AHBPERIPH_BASE		(PERIPH_BASE+0x00020000)		//open gpio clock,clock base address
#define RCC_BASE			(AHBPERIPH_BASE+0x1000)		//rcc is sys clock
#define RCC_APB2ENR			(unsigned int *)(RCC_BASE+0x18)		//apb2 clock

//all these is GPIO group base address
#define GPIOA_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x0800) 		//0x4001 0800
#define GPIOB_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x0c00) 		//0x4001 0c00
#define GPIOC_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x1000) 		//0x4001 1000 gpioc base address
#define GPIOD_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x1400) 		//0x4001 1400
#define GPIOE_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x1800) 		//0x4001 1800
#define GPIOF_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x1c00) 		//0x4001 1c00
#define GPIOG_BASE 			(unsigned int *)(APB2PERIPH_BASE+0x2000) 		//0x4001 2000

//GPIO address struct
typedef struct _stm32f10x_gpio_register
{
	unsigned int * CRL;
	unsigned int * CRH;
	unsigned int * IDR;
	unsigned int * ODR;
	unsigned int * BSRR;
	unsigned int * BRR;
	unsigned int * LCKR;
}GPIORegister;
//filling GPIO struct by gpio base address which upon define GPIOx_BASE value
void InitRegister(GPIORegister * reg,unsigned int * gpioBaseAddress)
{
	unsigned int * regstc=(unsigned int *)reg;
	for(int i=0;i<sizeof(GPIORegister)/4;i++)
	{
		regstc[i]=(gpioBaseAddress+i);
	}
}

#endif // _STM32F10X_REGISTER_H_
