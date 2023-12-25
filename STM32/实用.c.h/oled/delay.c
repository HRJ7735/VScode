#include "stm32f4xx_hal.h"
#include "tim.h"
#include "delay.h"
void delay_ms(uint32_t ms)
{
    delay_us(ms*1000);
}

void delay_us(uint16_t us)
{
	uint16_t differ = 0xffff-us-5;
	
	HAL_TIM_Base_Start(&htim6);
	__HAL_TIM_SET_COUNTER(&htim6, differ);
	
	while(differ < 0xffff - 5)
	{
		differ = __HAL_TIM_GET_COUNTER(&htim6);
	}
	HAL_TIM_Base_Stop(&htim6);
}
