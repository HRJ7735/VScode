#include "User_GUI.h"


/********************用户定义的参数***********************/


/*********************************************************/

/*********************系统默认参数************************/

GUI User_Gui;		//GUI用户参数

uint8_t String[7];	//模式显示缓存数组

uint16_t StartButton[4]={7,270,77,313};			//程序开始/停止触摸热区
uint16_t NextButton[4]=	{84,270,154,313};		//下一个模式触摸热区
uint16_t SetButton[4]=	{161,270,231,313};		//设置界面触摸热区

uint16_t ReturnButton[4]={7,270,77,313};		//返回主页面触摸热区

/*********************************************************/

/*****************************************
 * 函数名：		Gui_Init
 * 函数功能：	GUI界面初始化
 * 形参：			无
 * 返回值：		无	
******************************************/
void Gui_Init(void)
{
	User_Gui.ButtonNumber = 4;					//触摸热区数量
	User_Gui.Interface = 0x10;					//主页面
	User_Gui.Control.Mode = 0;					//模式初始化
	User_Gui.Control.State = Stop;
	User_Gui.TouchButtonName = 0;				//已按下的触摸热区
	User_Gui.DrawButton = DrawRectangle_num;	//画框（结构体函数实例化）
	User_Gui.LogicControl = Gui_Control;		//逻辑控制
	User_Gui.MasButtonPos[0][0] = StartButton;
	User_Gui.MasButtonPos[1][0] = NextButton;
	User_Gui.MasButtonPos[2][0] = SetButton;
	User_Gui.DepButtonPos[0][0] = ReturnButton;//触摸热区数组赋值
	Master_Interface();		//加载主页面
}

/*****************************************
 * 函数名：		Master_Interface
 * 函数功能：	创建触摸热区
 * 形参：			Interface 创建对应页面触摸热区（MastInterface:主页面 DepuInterface:副页面）
 * 返回值：		无	
******************************************/
static void CreateButton(int16_t Interface)
{
	switch(Interface)
	{
		case MastInterface:
			User_Gui.DrawButton(StartButton,(uint8_t*)"Start",LBBLUE,BlackColor,LBBLUE);	//开始触摸按钮热区
			User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//停止触摸按钮热区	
			User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//设置触摸按钮热区
		break;
		
		case DepuInterface:
			User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//返回触摸按钮热区
		break;
	}
}

/*****************************************
 * 函数名：		Master_Interface
 * 函数功能：	主页面加载
 * 形参：			无
 * 返回值：		无	
******************************************/
static void Master_Interface(void)
{
	CreateButton(User_Gui.Interface);		//创建触摸热区
	sprintf((char*)String,"Mode %d",User_Gui.Control.Mode);
	LCD_ShowString(96, 10,(uint8_t*)String, BLACK, BlackColor);
	LCD_Fill(10,30,50,50,RED);
}

/*****************************************
 * 函数名：		Deputy_Interface
 * 函数功能：	副页面加载
 * 形参：			无
 * 返回值：		无	
******************************************/
static void Deputy_Interface(void)
{
	CreateButton(User_Gui.Interface);		//创建触摸热区
}

/*****************************************
 * 函数名：		EffectView
 * 函数功能：	触摸区域按下效果显示
 * 形参：			Interface 当前页面，buttonNumber 按下的区域。
 * 返回值：		无	
******************************************/
static void EffectView(uint8_t Interface,uint8_t buttonNumber)
{
	if(Interface == MastInterface)		//主页面
	{
		switch(buttonNumber)
		{
			case MastInterface:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//停止触摸按钮热区	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//设置触摸按钮热区
			break;
		
			case 1: 
				if(User_Gui.TouchButtonName == 1)			//程序已经开始
					User_Gui.DrawButton(StartButton,(uint8_t*)" Stop ",BROWN,BlackColor,BROWN);	//开始触摸按钮热区
				else		//程序已经停止									
					User_Gui.DrawButton(StartButton,(uint8_t*)"Start",BROWN,BlackColor,BROWN);	//开始触摸按钮热区
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//停止触摸按钮热区	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//设置触摸按钮热区
			break;
			
			case 2:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",BROWN,BlackColor,BROWN);		//停止触摸按钮热区	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//设置触摸按钮热区
			break;
			
			case 3:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//停止触摸按钮热区	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",BROWN,BlackColor,BROWN);			//设置触摸按钮热区
			break;
			
			case 4:
				User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",BROWN,BlackColor,BROWN);	//开始触摸按钮热区
			break;
			
			case DepuInterface:
				User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//开始触摸按钮热区
			break;
		}
	}
	else
		if(Interface == DepuInterface)		//副页面
		{
			switch(buttonNumber)
			{
				case DepuInterface:
					User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//开始触摸按钮热区
				break;
			
				case 1: 
					User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",BROWN,BlackColor,BROWN);	//开始触摸按钮热区
				break;
			}
		}
}

/*****************************************
 * 函数名：		Gui_Control
 * 函数功能：	GUI控制逻辑
 * 形参：			无
 * 返回值：		无	
******************************************/
void Gui_Control(void)
{
	if(User_Gui.Interface == MastInterface)
	{
		GuiMasInterface_Control();			//GUI主页面控制逻辑
	}
	else
		if(User_Gui.Interface == DepuInterface)
		{
			GuiDepInterface_Control();		//GUI副界面控制逻辑
		}
}

/*****************************************
 * 函数名：		GuiMasInterface_Control
 * 函数功能：	GUI主页面控制逻辑
 * 形参：			无
 * 返回值：		无	
******************************************/
static void GuiMasInterface_Control(void)
{
	Gui_TouchAdjust(User_Gui.MasButtonPos, &User_Gui.TouchButtonName);		//传入触摸热区，并获取触摸热区名称
	switch(User_Gui.TouchButtonName)
	{
		case StateArea: 
			if(User_Gui.Control.State != Start)
			{
				User_Gui.Control.State = Start;		//开始执行程序
				User_Gui.DrawButton(StartButton,(uint8_t*)" Stop ",RED,BlackColor,RED);	//开始触摸按钮热区
				LCD_Fill(10,30,50,50,GREEN);			//程序开始执行状态指示
			}
			else
				if(User_Gui.Control.State == Start)
				{
					User_Gui.Control.State = Stop;	//停止程序
					User_Gui.DrawButton(StartButton,(uint8_t*)"Start",LBBLUE,BlackColor,LBBLUE);	//开始触摸按钮热区
					LCD_Fill(10,30,50,50,RED);				//程序停止执行状态指示
				}
			User_Gui.TouchButtonName = 0;
		break;
		
		case NextMode: 	
			User_Gui.Control.Mode++;		//下一个运行模式
			sprintf((char*)String,"Mode %d",User_Gui.Control.Mode);
			LCD_ShowString(96, 10,(uint8_t*)String, BLACK, BlackColor);
			User_Gui.TouchButtonName = 0;
		break;
		
		case SetArea:			//进入设置界面
			User_Gui.Interface = DepuInterface;					//切换页面
			LCD_Clear(BlackColor);											//清屏
			Deputy_Interface();													//加载副页面
			User_Gui.TouchButtonName = 0;		
		break;
	}
	FunExecutive(User_Gui.Control.State,User_Gui.Control.Mode);		//功能执行函数
}

/*****************************************
 * 函数名：		GuiDepInterface_Control
 * 函数功能：	GUI副界面控制逻辑
 * 形参：			无
 * 返回值：		无	
******************************************/
static void GuiDepInterface_Control(void)
{
	Gui_TouchAdjust(User_Gui.DepButtonPos, &User_Gui.TouchButtonName);		//传入触摸热区，并获取触摸热区名称
	switch(User_Gui.TouchButtonName)
	{
		case Return: 
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			User_Gui.Interface = MastInterface;
			LCD_Clear(BlackColor);
			Master_Interface();
			User_Gui.TouchButtonName = 0;
		break;
	}
}

/*****************************************
 * 函数名：		DrawRectangle_num
 * 函数功能：	绘制矩形框并填充字符
 * 形参：		num：矩形框的位置坐标。x1,y1,x2,y2
 * 					*string：		字符
 * 					StrColor：		字符颜色
 * 					StrBlaColor：	字符背景色
 * 					RecColor：		框的颜色
 * 返回值：		无
******************************************/
static void DrawRectangle_num(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor)	//画矩形并显示字符 （数组形式）
{
	uint8_t length;	//长度（字符）
	uint8_t breadth; //宽度
	
	length  = strlen((char*)string);	//计算字符串数组长度
	breadth = 16;
	if(length > (num[2] - num[0]))	//当所画的矩形长度小于所要显示的字符时，自动增加长度
	{
		num[2] = length+2;
		if(breadth > num[3] - num[1])	//当所画的矩形宽度小于所要显示的字符时，自动增加宽度
		{
			num[3] = num[1] + breadth+2;
		LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[3]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);		//显示字符
		}
		else
			LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[2]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);	//显示字符
	}
	else
	{
		LCD_Fill(num[0],num[1],num[2],num[1]+1,RecColor);		//上方的线
		LCD_Fill(num[0],num[3],num[2],num[3]+1,RecColor);		//下方的线
		LCD_Fill(num[0],num[1],num[0]+1,num[3],RecColor);		//左方的线
		LCD_Fill(num[2],num[1],num[2]+1,num[3]+1,RecColor);	//右方的线		画线
		LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[3]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);	//中间的字符
	}
}

/*****************************************
 * 函数名：		Judge_Touch
 * 函数功能：	判断所绘制的区域是否被按下
 * 形参：		num：矩形框的位置坐标。x1,y1,x2,y2
 * 返回值：		1：按下的是该区域。0：按下的不是该区域
******************************************/
static uint8_t Judge_Touch(uint16_t num[]) //判断触摸区域 若是该区域返回 1，否则返回 0 
{
	if((tp_dev.x[0]>num[0]) && (tp_dev.x[0]<num[2]) && (tp_dev.y[0]>num[1]) && (tp_dev.y[0]<num[3]))	//目标区域
	{
		return 1;
	}
	else
		return 0;
}

/*****************************************
 * 函数名：		Gui_TouchAdjust
 * 函数功能：	获取所有被按下触摸热区的名称。所有触摸热区归一处理，传入触摸热区，并获取触摸热区名称
 * 形参：			ButtonArea:按钮区域 TouchName所触发的区域名称
 * 返回值：		无	
******************************************/
static void Gui_TouchAdjust(uint16_t *ButtonArea[ButtonNumSIZE][LocationSize],uint16_t *TouchName)
{
	static uint8_t i = 0;
	tp_dev.scan(0);			//触摸扫描
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]<lcd_Width&&tp_dev.y[0]<lcd_height)	//判断按下区域是否在显示屏内
		{
			for(i = 0;i < User_Gui.ButtonNumber;i++)		//循环遍历寻找触摸区域
			{
				if(Judge_Touch(*ButtonArea[i]))		//判断触摸区域
				{
					if(User_Gui.Control.State != Start || i == 0)		//程序正在执行
					{
						EffectView(User_Gui.Interface,i+1);
						while(!PEN);
						EffectView(User_Gui.Interface,User_Gui.Interface);	//触摸热区效果显示
						*TouchName = i+1;		//触摸热区名称
					}
				}			
			}
			if(User_Gui.Interface == DepuInterface)		//副页面的触摸热区名称变换
				*TouchName += 3;			
		}
	}
}

/*****************************************
 * 函数名：		FunExecutive
 * 函数功能：	功能执行函数（弱函数可重定义）
 * 形参：			无
 * 返回值：		无	
******************************************/
__weak void FunExecutive(uint8_t state,uint8_t mode)
{
	if(state == Start)
	{
		switch(mode)
		{
			case 1:
				
			break;
			
			case 2:
				
			break;
		}
	}
}

/*****************************************
 * 函数名：		MastRefreshData
 * 函数功能：	主页面数据刷新函数（弱函数可重定义）
 * 形参：			无
 * 返回值：		无	
******************************************/
__weak void MastRefreshData(void)
{
	
}

/*****************************************
 * 函数名：		DepuRefreshData
 * 函数功能：	副页面数据刷新函数（弱函数可重定义）
 * 形参：			无
 * 返回值：		无	
******************************************/
__weak void DepuRefreshData(void)
{
	
}
