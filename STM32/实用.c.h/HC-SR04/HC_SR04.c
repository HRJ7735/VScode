/*

*********************************************************
���ߣ�С�˹�����Ϯ

����QQ��1204470386

ʱ�䣺2021��7��14��

��������������ο�������������ҵĿ��
*********************************************************

*/
#include "main.h"
#include "HC_SR04.h"

/*

*********************************************************

�궨��IO��

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

����ԭ�ͣ�void HC_SR04_Init(void)

�������룺��

�����������

�������ܣ�IO�ڵĳ�ʼ���������������ŷֱ�ΪOutput��Input

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

����ԭ�ͣ�void Delay_us(uint16_t time)

�������룺�޷�������

�����������

�������ܣ���ʱ����HAL_Delay���ƣ�����ʹ���˶�ʱ����Delay_us�ĵ�λ��1*e-5s

*********************************************************

*/

void Delay_us(uint16_t time)
{
	uint16_t a1=TIM3->CNT;
	while(TIM3->CNT-a1<time);
}

/*

*********************************************************

����ԭ�ͣ�void soner_startrange(void)

�������룺��

�����������

�������ܣ���trig��������һ�����Ϊ20����λ�ķ���

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

����ԭ�ͣ�uint16_t soner_gettime(void)

�������룺��

����������޷�������

�������ܣ�ͨ����ʱ����ȡ��ǰʱ��

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

����ԭ�ͣ�float soner_getdistance(void)

�������룺��

���������������

�������ܣ���ȡ��Ŀ��֮��ľ���

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

//����ģ�鱾������⣬���ݿ��ܴ���������������һ���޷��˲�������ԭ���ڴ˴�������׸��

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

 
