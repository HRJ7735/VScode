#ifndef __HMI_AGREEMENT_H
#define __HMI_AGREEMENT_H	 

#include "stm32h7xx.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "usart.h"

#define uart		huart2		//ʹ�õĴ���
#define _DataNum	5			//�ɽ�����������		

enum _Var		
{
	Start 	=	0x00,
	Stop 	= 	0x01,	//����״̬

	mode1 	= 	0x11,
	mode2 	= 	0x12,
	mode3 	= 	0x13,
	mode4 	= 	0x14,
	mode5 	= 	0x15,	//ģʽ

	_1E_0	= 	0,		//�������ŵȼ�
	_1E_1,
	_1E_2,

	_INT_VAID1 	= 	0x01,	//��������ID
	_INT_VAID2,
	_INT_VAID3,
	_INT_VAID4,
	_INT_VAID5,

	_FLO_VAID1	=	0x10,	//С������ID
	_FLO_VAID2,
	_FLO_VAID3,
	_FLO_VAID4,
	_FLO_VAID5,
};

struct IntRecData	//���յ����ݻ���(����)
{
	int16_t _Data01;
	int16_t _Data02;
	int16_t _Data03;
	int16_t _Data04;
	int16_t _Data05;
};

struct FloatRecData	//���յ����ݻ���(С��)
{
	float _Data10;
	float _Data20;
	float _Data30;
	float _Data40;
	float _Data50;
};

typedef struct 
{
	uint8_t StartFlag;			//����ʼ���б�־λ
	uint8_t ID;					//����ID	
	uint8_t Mode;				//����ģʽ
	struct IntRecData _IntRecData[_DataNum/5];		//���յ����ݽṹ��
	struct FloatRecData _FloatRecData[_DataNum/5];		//���յ����ݽṹ��
}_usarthmi;

extern _usarthmi UHMI;

/********************** �û��ϴ�ָ�� ********************/

void HMI_Usart_Rest(void);										//HMI��ʾ����λ
void HMI_Usart_Refresh(uint8_t *Page);							//HMIˢ��ҳ��
void HMI_Usart_SendDataValue(uint8_t *Head, int16_t data);		//���ڷ������ݵ�HMI��Ļ
void HMI_Usart_SendDataText(uint8_t *Head, uint8_t *SData);		//���ڷ����ַ����ݵ�HMI��Ļ
void HMI_Usart_ShowHideobj(uint8_t *Obj,uint8_t State);			//��ָ���Ŀؼ�����ʾ�����ؽ��в���

/********************* �û��������ݴ��� *******************/

static float ResolvingData(uint8_t *_DA);						//���ݽ���
static void Acceptance_Data(uint8_t *_DA);						//�������ݴ���

/********************* �û��ɵ��õĺ��� *******************/

void HMI_Usart_ReciveData(uint8_t *RData,uint8_t size);			//HMI�������ݺ���
void HMI_Usart_FunctionSelect(uint8_t *Rfun);					//HMI������ִ�к���ѡ��


#endif
