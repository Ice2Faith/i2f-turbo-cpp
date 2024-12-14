#ifndef _SMG_H_
#define _SMG_H_
#include"system.h"

#define SMG_PF0TO7_RCCCLK 		RCC_APB2Periph_GPIOF
#define SMG_PF0TO7_GPIOX			GPIOF
#define SMG_PF0TO7_GPIO_PIN 	(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)

// use before please:
//extern u8 g_smg_digarr[];
//it max index is 16
//value is 0-9 and a-f display code of smg
//SMG_SetDigital() func second arg will be used

void SMG_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);
void SMG_SetDigital(GPIO_TypeDef * GPIOx,u8 data);

#define SMG_INIT() SMG_Init(SMG_PF0TO7_RCCCLK,SMG_PF0TO7_GPIOX,SMG_PF0TO7_GPIO_PIN)
#define SMG_SETDIGITAL(data) SMG_SetDigital(SMG_PF0TO7_GPIOX,data)

#endif // _SMG_H_
