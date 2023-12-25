/*

*********************************************************
作者：小菜狗的逆袭

作者QQ：1204470386

时间：2021年7月14日

声明：程序仅供参考，不可用于商业目的
*********************************************************

*/
#ifndef _HC_SR04_H_
#define _HC_SR04_H_
#include "stm32f1xx_hal.h"
void HC_SR04_Init(void); //IO口的初始化，配置两个引脚分别为Output和Input
void Delay_us(uint16_t time);//延时
void soner_startrange(void);//从trig引脚生成一个宽度为20个单位的方波
float soner_getdistance(void);//获取与目标之间的距离
uint16_t soner_gettime(void);//通过定时器获取当前时间
#endif
/*
	#include "HC_SR04.h"
	HC_SR04_Init();
	float dis;
	HAL_TIM_Base_Start_IT(&htim3);
  while (1)
  {
		soner_startrange();
		dis = soner_getdistance();
		if(dis <= 1000)
			printf("距离是：%0.3fcm\r\n",dis/10);
		HAL_Delay(100);
  }
*/