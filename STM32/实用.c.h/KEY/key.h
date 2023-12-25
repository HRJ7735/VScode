#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "delay.h"

#include "stm32f4xx_hal.h"

#define  KEY1 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_0)
#define  KEY2 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_1)
#define  KEY3 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)
#define  KEY4 HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)


#define KEY1_RE 		1
#define KEY2_RE	    2
#define KEY3_RE	    3
#define KEY4_RE     4


void KEY_Init(void);
u8 Key_Scan(u8 mode);


#endif
