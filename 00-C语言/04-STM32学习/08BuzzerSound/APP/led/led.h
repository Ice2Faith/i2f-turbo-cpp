//#pragma once
#ifndef _LED_H_
#define _LED_H_
#include"system.h"
//when PB5/PE5 low light
#define LED_PB5_LED1_RCCCLK 		RCC_APB2Periph_GPIOB
#define LED_PB5_LED1_GPIOX			GPIOB
#define LED_PB5_LED1_GPIO_PIN 	GPIO_Pin_5

#define LED_PE5_LED2_RCCCLK			RCC_APB2Periph_GPIOE
#define LED_PE5_LED2_GPIOX			GPIOE
#define LED_PE5_LED2_GPIO_PIN 	GPIO_Pin_5

void LED_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);
void LED_light(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);
void LED_dark(GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin);

#define LED_Init_LED1()			LED_Init(LED_PB5_LED1_RCCCLK,LED_PB5_LED1_GPIOX,LED_PB5_LED1_GPIO_PIN)
#define LED_Light_LED1()		LED_light(LED_PB5_LED1_GPIOX,LED_PB5_LED1_GPIO_PIN)
#define LED_Dark_LED1()			LED_dark(LED_PB5_LED1_GPIOX,LED_PB5_LED1_GPIO_PIN)

#define LED_Init_LED2()			LED_Init(LED_PE5_LED2_RCCCLK,LED_PE5_LED2_GPIOX,LED_PE5_LED2_GPIO_PIN)
#define LED_Light_LED2()		LED_light(LED_PE5_LED2_GPIOX,LED_PE5_LED2_GPIO_PIN)
#define LED_Dark_LED2()			LED_dark(LED_PE5_LED2_GPIOX,LED_PE5_LED2_GPIO_PIN)

#define LED1 PBout(5)
#define LED2 PEout(5)

#endif // _LED_H_
