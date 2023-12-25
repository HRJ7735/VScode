#ifndef _USER_GUI_H
#define _USER_GUI_H

#include "stm32f4xx.h"   
#include "stdio.h"
#include "string.h"
#include "lcd.h"
#include "touch.h"

#define BlackColor 0x4248		//背景色

//显示屏的尺寸：320*240

#define lcd_Width  			240
#define lcd_height  		320		//LCD参数
#define ButtonNumSIZE   	20		//按钮最多数量
#define LocationSize 		4		//按钮矩形区域数据范围4位

#define StateArea 			1		//开始/停止触摸热区
#define NextMode 			2		//下一个模式触摸热区
#define SetArea 			3		//设置界面触摸热区
#define Return 				4		//返回主页面触摸热区

#define Start				0x21	//程序开始
#define Stop				0x22	//程序结束

#define MastInterface  0x10		//主页面
#define DepuInterface  0x11		//副页面


struct control		//控制逻辑
{
	uint8_t State;		//程序工作状态
	uint8_t Mode;		//程序工作模式
};

struct color		//用户触摸热区颜色设置
{
  	uint16_t StrColor;			//字符颜色
	uint16_t StrBlaColor;		//字符背景色
	uint16_t RecColor;			//外框颜色
};

typedef struct
{
	void (*LogicControl)(void);			//逻辑控制函数
	void (*DrawButton)(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor);		//绘框函数
	
	uint8_t ButtonNumber;		//按钮数量
	uint16_t Interface;			//页面
	uint16_t TouchButtonName;	//触摸热区名称
	uint16_t *MasButtonPos[ButtonNumSIZE][LocationSize];	//主页面按钮的位置（坐标）数据
	uint16_t *DepButtonPos[ButtonNumSIZE][LocationSize];	//副页面按钮的位置（坐标）数据
	struct color SetColorButton[ButtonNumSIZE];				//设置触摸热区颜色的结构体嵌套
	struct control Control;									//逻辑控制的结构体嵌套
}GUI;

extern GUI User_Gui;

void Gui_Init(void);							//GUI界面初始化
static void CreateButton(int16_t Interface);	//创建触摸热区
static void Master_Interface(void);				//主页面加载
static void Deputy_Interface(void);				//副页面加载
static void EffectView(uint8_t Interface,uint8_t buttonNumber);		//触摸区域按下效果显示
void Gui_Control(void);												//GUI控制逻辑
static void GuiMasInterface_Control(void);		//GUI主页面控制逻辑
static void GuiDepInterface_Control(void);		//GUI副界面控制逻辑
static void DrawRectangle_num(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor);	//画矩形并显示字符 （数组形式）
static uint8_t Judge_Touch(uint16_t num[]); 	//判断触摸区域 若是该区域返回 1，否则返回 0 
static void Gui_TouchAdjust(uint16_t *ButtonArea[ButtonNumSIZE][LocationSize],uint16_t *TouchName);	//获取所有被按下触摸热区的名称

__weak void FunExecutive(uint8_t state,uint8_t mode);		//功能执行函数（弱函数可重定义）
__weak void MastRefreshData(void);							//主页面数据刷新函数（弱函数可重定义）
__weak void DepuRefreshData(void);							//副页面数据刷新函数（弱函数可重定义）

#endif

