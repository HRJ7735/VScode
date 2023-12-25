#ifndef __DS18B20_H
#define	__DS18B20_H

#include "stm32f1xx_hal.h"
//#include "delay.h"


#define HIGH  1
#define LOW   0

#define DS18B20_PIN     GPIO_PIN_12                  
#define DS18B20_PORT	GPIOA 

//带参宏，可以像内联函数一样使用,输出高电平或低电平
#define DS18B20_DATA_OUT(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);\
					else		\
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)
 //读取引脚的电平
					#define  DS18B20_DATA_IN()	   HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)

typedef struct
{
	u8  humi_int;		//湿度的整数部分-DS18B20不能测湿度
	u8  humi_deci;	 	//湿度的小数部分-DS18B20不能测湿度
	u8  temp_int;	 	//温度的整数部分
	u8  temp_deci;	 	//温度的小数部分
	u8  check_sum;	 	//校验和
		                 
}DS18B20_Data_TypeDef;

u8 DS18B20_Init(void);
float DS18B20_Get_Temp(void);
#endif /* __DS18B20_H */


//如果懒得加delay.h可以用下面的粗延时
/*//对于stm32f1系列 72mhz大致是1ms
void Delay_ms(uint32_t ms)
{
		uint16_t i = 0;
		while(ms--)
		{
			i = 4050;
			while(i--);
		};
}
void Delay_us(uint32_t us)
{
		uint16_t i = 0;
		while(us--)
		{
			i = 2;
			while(i--);
		}
}

//对于stm32f4系列 168mhz大致是1us
void my_delay_us(u32 us)
{
		u8 i = 0;
		while(us--)
		{
			i = 42;
			while(i--);
		};
}
 
void delay_ms(u32 ms)
{
		u16 i = 0;
		while(ms--)
		{
			i = 41750;
			while(i--);
		};

}*/