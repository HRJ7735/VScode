#ifndef __ADS8689_H__
#define __ADS8689_H__	
//#include "sys.h" 
#include "stm32f1xx.h"

#define ADS8689_SCLK_IO 	GPIOA
#define ADS8689_SCLK_PIN	GPIO_PIN_1
#define ADS8689_CS_IO 		GPIOC
#define ADS8689_CS_PIN		GPIO_PIN_4
#define ADS8689_SDI_IO 		GPIOA
#define ADS8689_SDI_PIN		GPIO_PIN_7
#define ADS8689_SDD_1_IO 	GPIOA
#define ADS8689_SDD_1_PIN	GPIO_PIN_4
#define ADS8689_SDD_0_IO 	GPIOA
#define ADS8689_SDD_0_PIN	GPIO_PIN_6

void Delay_us(uint32_t us);//延时us粗
void Delay_ms(uint32_t ms);//延时ms粗

#endif
  