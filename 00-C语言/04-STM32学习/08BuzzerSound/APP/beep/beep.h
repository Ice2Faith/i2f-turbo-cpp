#ifndef _BEEP_H_
#define _BEEP_H_
#include"system.h"
//when pb8 low beep on

#define BEEP_PB8_RCCCLK 		RCC_APB2Periph_GPIOB
#define BEEP_PB8_GPIOX			GPIOB
#define BEEP_PB8_GPIO_PIN 	GPIO_Pin_8


void Beep_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);
void Beep_on(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);
void Beep_off(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);

#define BEEP_INIT()			Beep_Init(BEEP_PB8_RCCCLK,BEEP_PB8_GPIOX,BEEP_PB8_GPIO_PIN)
#define BEEP_ON()			Beep_on(BEEP_PB8_GPIOX,BEEP_PB8_GPIO_PIN)
#define BEEP_OFF()			Beep_off(BEEP_PB8_GPIOX,BEEP_PB8_GPIO_PIN)


#define BEEP PBout(8)

#endif // _BEEP_H_
