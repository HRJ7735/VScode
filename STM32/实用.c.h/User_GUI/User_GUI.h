#ifndef _USER_GUI_H
#define _USER_GUI_H

#include "stm32f4xx.h"   
#include "stdio.h"
#include "string.h"
#include "lcd.h"
#include "touch.h"

#define BlackColor 0x4248		//����ɫ

//��ʾ���ĳߴ磺320*240

#define lcd_Width  			240
#define lcd_height  		320		//LCD����
#define ButtonNumSIZE   	20		//��ť�������
#define LocationSize 		4		//��ť�����������ݷ�Χ4λ

#define StateArea 			1		//��ʼ/ֹͣ��������
#define NextMode 			2		//��һ��ģʽ��������
#define SetArea 			3		//���ý��津������
#define Return 				4		//������ҳ�津������

#define Start				0x21	//����ʼ
#define Stop				0x22	//�������

#define MastInterface  0x10		//��ҳ��
#define DepuInterface  0x11		//��ҳ��


struct control		//�����߼�
{
	uint8_t State;		//������״̬
	uint8_t Mode;		//������ģʽ
};

struct color		//�û�����������ɫ����
{
  	uint16_t StrColor;			//�ַ���ɫ
	uint16_t StrBlaColor;		//�ַ�����ɫ
	uint16_t RecColor;			//�����ɫ
};

typedef struct
{
	void (*LogicControl)(void);			//�߼����ƺ���
	void (*DrawButton)(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor);		//�����
	
	uint8_t ButtonNumber;		//��ť����
	uint16_t Interface;			//ҳ��
	uint16_t TouchButtonName;	//������������
	uint16_t *MasButtonPos[ButtonNumSIZE][LocationSize];	//��ҳ�水ť��λ�ã����꣩����
	uint16_t *DepButtonPos[ButtonNumSIZE][LocationSize];	//��ҳ�水ť��λ�ã����꣩����
	struct color SetColorButton[ButtonNumSIZE];				//���ô���������ɫ�Ľṹ��Ƕ��
	struct control Control;									//�߼����ƵĽṹ��Ƕ��
}GUI;

extern GUI User_Gui;

void Gui_Init(void);							//GUI�����ʼ��
static void CreateButton(int16_t Interface);	//������������
static void Master_Interface(void);				//��ҳ�����
static void Deputy_Interface(void);				//��ҳ�����
static void EffectView(uint8_t Interface,uint8_t buttonNumber);		//����������Ч����ʾ
void Gui_Control(void);												//GUI�����߼�
static void GuiMasInterface_Control(void);		//GUI��ҳ������߼�
static void GuiDepInterface_Control(void);		//GUI����������߼�
static void DrawRectangle_num(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor);	//�����β���ʾ�ַ� ��������ʽ��
static uint8_t Judge_Touch(uint16_t num[]); 	//�жϴ������� ���Ǹ����򷵻� 1�����򷵻� 0 
static void Gui_TouchAdjust(uint16_t *ButtonArea[ButtonNumSIZE][LocationSize],uint16_t *TouchName);	//��ȡ���б����´�������������

__weak void FunExecutive(uint8_t state,uint8_t mode);		//����ִ�к��������������ض��壩
__weak void MastRefreshData(void);							//��ҳ������ˢ�º��������������ض��壩
__weak void DepuRefreshData(void);							//��ҳ������ˢ�º��������������ض��壩

#endif

