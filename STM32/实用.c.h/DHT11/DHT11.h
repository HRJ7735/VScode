#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f1xx.h"

#define DHT11_IO 		GPIOA
#define DHT11_PIN		GPIO_PIN_5

uint8_t DHT_Read_Byte(void);
uint8_t DHT_Read(void);

void Delay_us(uint32_t us);//延时us粗
void Delay_ms(uint32_t ms);//延时ms粗

void DHT_GPIO_SET_OUTPUT(void);
void DHT_GPIO_SET_INPUT(void);



/* 初始化函数，如果DHT11存在响应则返回1，否则0 */
/* 从DHT11读取数据，没有小数部分 */


#endif
