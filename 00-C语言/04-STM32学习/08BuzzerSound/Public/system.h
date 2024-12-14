#ifndef _SYSTEM_H_
#define _SYSTEM_H_
//unify coretex3
#include"stm32f10x.h"

#define BITBAND(addr,bitNum) 	((addr & 0xf0000000)+0x02000000+((addr&0x000fffff)<<5)+(bitNum<<2))
#define MEM_ADDR(addr)			*((volatile unsigned long *)(addr))
#define BIT_ADDR(addr,bitNum)	MEM_ADDR(BITBAND(addr,bitNum))

#define GPIOA_ODR_ADDR (GPIOA_BASE+12) //0x4001080c
#define GPIOB_ODR_ADDR (GPIOB_BASE+12) //0x40010c0c
#define GPIOC_ODR_ADDR (GPIOC_BASE+12) //0x4001100c
#define GPIOD_ODR_ADDR (GPIOD_BASE+12) //0x4001140c
#define GPIOE_ODR_ADDR (GPIOE_BASE+12) //0x4001180c
#define GPIOF_ODR_ADDR (GPIOF_BASE+12) //0x40011a0c
#define GPIOG_ODR_ADDR (GPIOG_BASE+12) //0x40011e0c

#define GPIOA_IDR_ADDR (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_ADDR (GPIOB_BASE+8) //0x40010c08
#define GPIOC_IDR_ADDR (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_ADDR (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_ADDR (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_ADDR (GPIOF_BASE+8) //0x40011a08
#define GPIOG_IDR_ADDR (GPIOG_BASE+8) //0x40011e08

//n between 0-15 both
#define PAout(n)	BIT_ADDR(GPIOA_ODR_ADDR,n)
#define PAin(n)		BIT_ADDR(GPIOA_IDR_ADDR,n)

#define PBout(n)	BIT_ADDR(GPIOB_ODR_ADDR,n)
#define PBin(n)		BIT_ADDR(GPIOB_IDR_ADDR,n)

#define PCout(n)	BIT_ADDR(GPIOC_ODR_ADDR,n)
#define PCin(n)		BIT_ADDR(GPIOC_IDR_ADDR,n)

#define PDout(n)	BIT_ADDR(GPIOD_ODR_ADDR,n)
#define PDin(n)		BIT_ADDR(GPIOD_IDR_ADDR,n)

#define PEout(n)	BIT_ADDR(GPIOE_ODR_ADDR,n)
#define PEin(n)		BIT_ADDR(GPIOE_IDR_ADDR,n)

#define PFout(n)	BIT_ADDR(GPIOF_ODR_ADDR,n)
#define PFin(n)		BIT_ADDR(GPIOF_IDR_ADDR,n)

#define PGout(n)	BIT_ADDR(GPIOG_ODR_ADDR,n)
#define PGin(n)		BIT_ADDR(GPIOG_IDR_ADDR,n)
#endif // _SYSTEM_H_
