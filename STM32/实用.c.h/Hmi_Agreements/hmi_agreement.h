#ifndef __HMI_AGREEMENT_H
#define __HMI_AGREEMENT_H	 

#include "stm32h7xx.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "usart.h"

#define uart		huart2		//使用的串口
#define _DataNum	5			//可接收数据数量		

enum _Var		
{
	Start 	=	0x00,
	Stop 	= 	0x01,	//工作状态

	mode1 	= 	0x11,
	mode2 	= 	0x12,
	mode3 	= 	0x13,
	mode4 	= 	0x14,
	mode5 	= 	0x15,	//模式

	_1E_0	= 	0,		//数据缩放等级
	_1E_1,
	_1E_2,

	_INT_VAID1 	= 	0x01,	//整型数据ID
	_INT_VAID2,
	_INT_VAID3,
	_INT_VAID4,
	_INT_VAID5,

	_FLO_VAID1	=	0x10,	//小数数据ID
	_FLO_VAID2,
	_FLO_VAID3,
	_FLO_VAID4,
	_FLO_VAID5,
};

struct IntRecData	//接收的数据缓存(整数)
{
	int16_t _Data01;
	int16_t _Data02;
	int16_t _Data03;
	int16_t _Data04;
	int16_t _Data05;
};

struct FloatRecData	//接收的数据缓存(小数)
{
	float _Data10;
	float _Data20;
	float _Data30;
	float _Data40;
	float _Data50;
};

typedef struct 
{
	uint8_t StartFlag;			//程序开始运行标志位
	uint8_t ID;					//数据ID	
	uint8_t Mode;				//工作模式
	struct IntRecData _IntRecData[_DataNum/5];		//接收的数据结构体
	struct FloatRecData _FloatRecData[_DataNum/5];		//接收的数据结构体
}_usarthmi;

extern _usarthmi UHMI;

/********************** 用户上传指令 ********************/

void HMI_Usart_Rest(void);										//HMI显示屏复位
void HMI_Usart_Refresh(uint8_t *Page);							//HMI刷新页面
void HMI_Usart_SendDataValue(uint8_t *Head, int16_t data);		//串口发送数据到HMI屏幕
void HMI_Usart_SendDataText(uint8_t *Head, uint8_t *SData);		//串口发送字符数据到HMI屏幕
void HMI_Usart_ShowHideobj(uint8_t *Obj,uint8_t State);			//对指定的控件的显示和隐藏进行操作

/********************* 用户接收数据处理 *******************/

static float ResolvingData(uint8_t *_DA);						//数据解算
static void Acceptance_Data(uint8_t *_DA);						//接收数据处理

/********************* 用户可调用的函数 *******************/

void HMI_Usart_ReciveData(uint8_t *RData,uint8_t size);			//HMI接收数据函数
void HMI_Usart_FunctionSelect(uint8_t *Rfun);					//HMI功能类执行函数选择


#endif
