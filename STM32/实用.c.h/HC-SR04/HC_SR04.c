/*

*********************************************************
作者：小菜狗的逆袭

作者QQ：1204470386

时间：2021年7月14日

声明：程序仅供参考，不可用于商业目的
*********************************************************

*/
#include "main.h"
#include "HC_SR04.h"

/*

*********************************************************

宏定义IO口

*********************************************************

*/
#define SONER_TRIG					GPIOB
#define SONER_TRIG_PIN			GPIO_PIN_11
#define SONER_ECHO				GPIOB
#define SONER_ECHO_PIN		GPIO_PIN_10

static float distance_temp=0;

static float distance_last=0;

static float distance_result;
/*

*********************************************************

函数原型：void HC_SR04_Init(void)

函数输入：无

函数输出：无

函数功能：IO口的初始化，配置两个引脚分别为Output和Input

*********************************************************

*/
void HC_SR04_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//__HAL_RCC_GPIOA_CLK_ENABLE();

	//TRIG
		GPIO_InitStruct.Pin = SONER_TRIG_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SONER_TRIG, &GPIO_InitStruct);

	//ECHO
  GPIO_InitStruct.Pin = SONER_ECHO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SONER_ECHO, &GPIO_InitStruct);
}

/*

*********************************************************

函数原型：void Delay_us(uint16_t time)

函数输入：无符号整形

函数输出：无

函数功能：延时，与HAL_Delay类似，但是使用了定时器，Delay_us的单位是1*e-5s

*********************************************************

*/

void Delay_us(uint16_t time)
{
	uint16_t a1=TIM3->CNT;
	while(TIM3->CNT-a1<time);
}

/*

*********************************************************

函数原型：void soner_startrange(void)

函数输入：无

函数输出：无

函数功能：从trig引脚生成一个宽度为20个单位的方波

*********************************************************
*/

void soner_startrange(void)
{
	HAL_GPIO_WritePin(SONER_TRIG,SONER_TRIG_PIN,GPIO_PIN_SET);
	Delay_us(20);
	HAL_GPIO_WritePin(SONER_TRIG,SONER_TRIG_PIN,GPIO_PIN_RESET);
}
/*

*********************************************************

函数原型：uint16_t soner_gettime(void)

函数输入：无

函数输出：无符号整型

函数功能：通过定时器获取当前时间

*********************************************************

*/

uint16_t soner_gettime(void)
{
	uint32_t a;
	a=TIM3->CNT;
	return a;
}
/*

*********************************************************

函数原型：float soner_getdistance(void)

函数输入：无

函数输出：浮点型

函数功能：获取与目标之间的距离

*********************************************************

*/

float soner_getdistance(void)

{   

	uint16_t time_node1;

  uint16_t time_node2;

  uint16_t measure;

  soner_startrange();

  while(HAL_GPIO_ReadPin(SONER_ECHO,SONER_ECHO_PIN)==RESET);

	time_node1=soner_gettime();

	while(HAL_GPIO_ReadPin(SONER_ECHO,SONER_ECHO_PIN)==SET);

	time_node2=soner_gettime();

	measure=time_node2-time_node1;

	distance_temp = measure * 17.0/100;

//由于模块本身的问题，数据可能存在噪声，因此添加一个限幅滤波，具体原理在此处不加以赘述

	if(distance_last==0)

		distance_last = distance_temp;

	if(distance_last-distance_temp>100 || distance_temp-distance_last>100)

	{

		distance_result =distance_last;

		distance_last=distance_temp;

	}

	else

	{

		distance_result=distance_temp;

		distance_last=distance_temp;

	}

  return distance_result;

}

 
