#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f1xx.h"

#define DHT11_IO 		GPIOA
#define DHT11_PIN		GPIO_PIN_5

uint8_t DHT_Read_Byte(void);
uint8_t DHT_Read(void);

void Delay_us(uint32_t us);//��ʱus��
void Delay_ms(uint32_t ms);//��ʱms��

void DHT_GPIO_SET_OUTPUT(void);
void DHT_GPIO_SET_INPUT(void);



/* ��ʼ�����������DHT11������Ӧ�򷵻�1������0 */
/* ��DHT11��ȡ���ݣ�û��С������ */


#endif
