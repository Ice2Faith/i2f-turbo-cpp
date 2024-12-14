#ifndef _KEY_H_
#define _KEY_H_
#include"system.h"

#define KEY_PA0_KEY_WKUP_RCCCLK 		RCC_APB2Periph_GPIOA
#define KEY_PA0_KEY_WKUP_GPIOX			GPIOA
#define KEY_PA0_KEY_WKUP_GPIO_PIN 	GPIO_Pin_0
#define KEY_PA0_KEY_WKUP_GPIO_MODE 	GPIO_Mode_IPD //inoput down mode,for key down is high

#define KEY_PE3_KEY1_RCCCLK 		RCC_APB2Periph_GPIOE
#define KEY_PE3_KEY1_GPIOX			GPIOE
#define KEY_PE3_KEY1_GPIO_PIN 	GPIO_Pin_3
#define KEY_PE3_KEY1_GPIO_MODE 	GPIO_Mode_IPU //input up mode,for key down is low

#define KEY_PE4_KEY0_RCCCLK 		RCC_APB2Periph_GPIOE
#define KEY_PE4_KEY0_GPIOX			GPIOE
#define KEY_PE4_KEY0_GPIO_PIN 	GPIO_Pin_4
#define KEY_PE4_KEY0_GPIO_MODE 	GPIO_Mode_IPU

void KEY_Init(uint32_t RCC_APB2Periph,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin,uint8_t inputMode);
// mode=0 single scan,mode=1 multiply scan
uint8_t KEY_scan(uint8_t scanMode,GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin,uint8_t heighElec);

#define KEY_INIT_KEYWK() KEY_Init(KEY_PA0_KEY_WKUP_RCCCLK,KEY_PA0_KEY_WKUP_GPIOX,KEY_PA0_KEY_WKUP_GPIO_PIN,GPIO_Mode_IPD)
#define KEY_INIT_KEY1() KEY_Init(KEY_PE3_KEY1_RCCCLK,KEY_PE3_KEY1_GPIOX,KEY_PE3_KEY1_GPIO_PIN,GPIO_Mode_IPU)
#define KEY_INIT_KEY0() KEY_Init(KEY_PE4_KEY0_RCCCLK,KEY_PE4_KEY0_GPIOX,KEY_PE4_KEY0_GPIO_PIN,GPIO_Mode_IPU)

#define KEY_INIT() do{KEY_INIT_KEYWK();KEY_INIT_KEY1();KEY_INIT_KEY0();}while(0);

#define KEY_WKUP		PAin(0)
#define KEY_KEY1		PEin(3)
#define KEY_KEY0		PEin(4)

#define KEY_CK_WKUP		(GPIO_ReadInputDataBit(KEY_PA0_KEY_WKUP_GPIOX,KEY_PA0_KEY_WKUP_GPIO_PIN)==1)
#define KEY_CK_KEY1		(GPIO_ReadInputDataBit(KEY_PE3_KEY1_GPIOX,KEY_PE3_KEY1_GPIO_PIN)==0)
#define KEY_CK_KEY0		(GPIO_ReadInputDataBit(KEY_PE4_KEY0_GPIOX,KEY_PE4_KEY0_GPIO_PIN)==0)

#define KEY_SCAN_WKUP(mode) KEY_scan(mode,KEY_PA0_KEY_WKUP_GPIOX,KEY_PA0_KEY_WKUP_GPIO_PIN,1)
#define KEY_SCAN_KEY1(mode) KEY_scan(mode,KEY_PE3_KEY1_GPIOX,KEY_PE3_KEY1_GPIO_PIN,0)
#define KEY_SCAN_KEY0(mode) KEY_scan(mode,KEY_PE4_KEY0_GPIOX,KEY_PE4_KEY0_GPIO_PIN,0)
#endif // _KEY_H_
