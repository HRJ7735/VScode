#include "User_GUI.h"


/********************�û�����Ĳ���***********************/


/*********************************************************/

/*********************ϵͳĬ�ϲ���************************/

GUI User_Gui;		//GUI�û�����

uint8_t String[7];	//ģʽ��ʾ��������

uint16_t StartButton[4]={7,270,77,313};			//����ʼ/ֹͣ��������
uint16_t NextButton[4]=	{84,270,154,313};		//��һ��ģʽ��������
uint16_t SetButton[4]=	{161,270,231,313};		//���ý��津������

uint16_t ReturnButton[4]={7,270,77,313};		//������ҳ�津������

/*********************************************************/

/*****************************************
 * ��������		Gui_Init
 * �������ܣ�	GUI�����ʼ��
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
void Gui_Init(void)
{
	User_Gui.ButtonNumber = 4;					//������������
	User_Gui.Interface = 0x10;					//��ҳ��
	User_Gui.Control.Mode = 0;					//ģʽ��ʼ��
	User_Gui.Control.State = Stop;
	User_Gui.TouchButtonName = 0;				//�Ѱ��µĴ�������
	User_Gui.DrawButton = DrawRectangle_num;	//���򣨽ṹ�庯��ʵ������
	User_Gui.LogicControl = Gui_Control;		//�߼�����
	User_Gui.MasButtonPos[0][0] = StartButton;
	User_Gui.MasButtonPos[1][0] = NextButton;
	User_Gui.MasButtonPos[2][0] = SetButton;
	User_Gui.DepButtonPos[0][0] = ReturnButton;//�����������鸳ֵ
	Master_Interface();		//������ҳ��
}

/*****************************************
 * ��������		Master_Interface
 * �������ܣ�	������������
 * �βΣ�			Interface ������Ӧҳ�津��������MastInterface:��ҳ�� DepuInterface:��ҳ�棩
 * ����ֵ��		��	
******************************************/
static void CreateButton(int16_t Interface)
{
	switch(Interface)
	{
		case MastInterface:
			User_Gui.DrawButton(StartButton,(uint8_t*)"Start",LBBLUE,BlackColor,LBBLUE);	//��ʼ������ť����
			User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//ֹͣ������ť����	
			User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//���ô�����ť����
		break;
		
		case DepuInterface:
			User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//���ش�����ť����
		break;
	}
}

/*****************************************
 * ��������		Master_Interface
 * �������ܣ�	��ҳ�����
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
static void Master_Interface(void)
{
	CreateButton(User_Gui.Interface);		//������������
	sprintf((char*)String,"Mode %d",User_Gui.Control.Mode);
	LCD_ShowString(96, 10,(uint8_t*)String, BLACK, BlackColor);
	LCD_Fill(10,30,50,50,RED);
}

/*****************************************
 * ��������		Deputy_Interface
 * �������ܣ�	��ҳ�����
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
static void Deputy_Interface(void)
{
	CreateButton(User_Gui.Interface);		//������������
}

/*****************************************
 * ��������		EffectView
 * �������ܣ�	����������Ч����ʾ
 * �βΣ�			Interface ��ǰҳ�棬buttonNumber ���µ�����
 * ����ֵ��		��	
******************************************/
static void EffectView(uint8_t Interface,uint8_t buttonNumber)
{
	if(Interface == MastInterface)		//��ҳ��
	{
		switch(buttonNumber)
		{
			case MastInterface:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//ֹͣ������ť����	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//���ô�����ť����
			break;
		
			case 1: 
				if(User_Gui.TouchButtonName == 1)			//�����Ѿ���ʼ
					User_Gui.DrawButton(StartButton,(uint8_t*)" Stop ",BROWN,BlackColor,BROWN);	//��ʼ������ť����
				else		//�����Ѿ�ֹͣ									
					User_Gui.DrawButton(StartButton,(uint8_t*)"Start",BROWN,BlackColor,BROWN);	//��ʼ������ť����
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//ֹͣ������ť����	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//���ô�����ť����
			break;
			
			case 2:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",BROWN,BlackColor,BROWN);		//ֹͣ������ť����	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",LBBLUE,BlackColor,LBBLUE);			//���ô�����ť����
			break;
			
			case 3:
				User_Gui.DrawButton(NextButton,(uint8_t*)"Next",LBBLUE,BlackColor,LBBLUE);		//ֹͣ������ť����	
				User_Gui.DrawButton(SetButton,(uint8_t*)"Set",BROWN,BlackColor,BROWN);			//���ô�����ť����
			break;
			
			case 4:
				User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",BROWN,BlackColor,BROWN);	//��ʼ������ť����
			break;
			
			case DepuInterface:
				User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//��ʼ������ť����
			break;
		}
	}
	else
		if(Interface == DepuInterface)		//��ҳ��
		{
			switch(buttonNumber)
			{
				case DepuInterface:
					User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",LBBLUE,BlackColor,LBBLUE);	//��ʼ������ť����
				break;
			
				case 1: 
					User_Gui.DrawButton(ReturnButton,(uint8_t*)"Return",BROWN,BlackColor,BROWN);	//��ʼ������ť����
				break;
			}
		}
}

/*****************************************
 * ��������		Gui_Control
 * �������ܣ�	GUI�����߼�
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
void Gui_Control(void)
{
	if(User_Gui.Interface == MastInterface)
	{
		GuiMasInterface_Control();			//GUI��ҳ������߼�
	}
	else
		if(User_Gui.Interface == DepuInterface)
		{
			GuiDepInterface_Control();		//GUI����������߼�
		}
}

/*****************************************
 * ��������		GuiMasInterface_Control
 * �������ܣ�	GUI��ҳ������߼�
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
static void GuiMasInterface_Control(void)
{
	Gui_TouchAdjust(User_Gui.MasButtonPos, &User_Gui.TouchButtonName);		//���봥������������ȡ������������
	switch(User_Gui.TouchButtonName)
	{
		case StateArea: 
			if(User_Gui.Control.State != Start)
			{
				User_Gui.Control.State = Start;		//��ʼִ�г���
				User_Gui.DrawButton(StartButton,(uint8_t*)" Stop ",RED,BlackColor,RED);	//��ʼ������ť����
				LCD_Fill(10,30,50,50,GREEN);			//����ʼִ��״ָ̬ʾ
			}
			else
				if(User_Gui.Control.State == Start)
				{
					User_Gui.Control.State = Stop;	//ֹͣ����
					User_Gui.DrawButton(StartButton,(uint8_t*)"Start",LBBLUE,BlackColor,LBBLUE);	//��ʼ������ť����
					LCD_Fill(10,30,50,50,RED);				//����ִֹͣ��״ָ̬ʾ
				}
			User_Gui.TouchButtonName = 0;
		break;
		
		case NextMode: 	
			User_Gui.Control.Mode++;		//��һ������ģʽ
			sprintf((char*)String,"Mode %d",User_Gui.Control.Mode);
			LCD_ShowString(96, 10,(uint8_t*)String, BLACK, BlackColor);
			User_Gui.TouchButtonName = 0;
		break;
		
		case SetArea:			//�������ý���
			User_Gui.Interface = DepuInterface;					//�л�ҳ��
			LCD_Clear(BlackColor);											//����
			Deputy_Interface();													//���ظ�ҳ��
			User_Gui.TouchButtonName = 0;		
		break;
	}
	FunExecutive(User_Gui.Control.State,User_Gui.Control.Mode);		//����ִ�к���
}

/*****************************************
 * ��������		GuiDepInterface_Control
 * �������ܣ�	GUI����������߼�
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
static void GuiDepInterface_Control(void)
{
	Gui_TouchAdjust(User_Gui.DepButtonPos, &User_Gui.TouchButtonName);		//���봥������������ȡ������������
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
 * ��������		DrawRectangle_num
 * �������ܣ�	���ƾ��ο�����ַ�
 * �βΣ�		num�����ο��λ�����ꡣx1,y1,x2,y2
 * 					*string��		�ַ�
 * 					StrColor��		�ַ���ɫ
 * 					StrBlaColor��	�ַ�����ɫ
 * 					RecColor��		�����ɫ
 * ����ֵ��		��
******************************************/
static void DrawRectangle_num(uint16_t num[], uint8_t *string, uint16_t StrColor, uint16_t StrBlaColor,uint16_t RecColor)	//�����β���ʾ�ַ� ��������ʽ��
{
	uint8_t length;	//���ȣ��ַ���
	uint8_t breadth; //���
	
	length  = strlen((char*)string);	//�����ַ������鳤��
	breadth = 16;
	if(length > (num[2] - num[0]))	//�������ľ��γ���С����Ҫ��ʾ���ַ�ʱ���Զ����ӳ���
	{
		num[2] = length+2;
		if(breadth > num[3] - num[1])	//�������ľ��ο��С����Ҫ��ʾ���ַ�ʱ���Զ����ӿ��
		{
			num[3] = num[1] + breadth+2;
		LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[3]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);		//��ʾ�ַ�
		}
		else
			LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[2]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);	//��ʾ�ַ�
	}
	else
	{
		LCD_Fill(num[0],num[1],num[2],num[1]+1,RecColor);		//�Ϸ�����
		LCD_Fill(num[0],num[3],num[2],num[3]+1,RecColor);		//�·�����
		LCD_Fill(num[0],num[1],num[0]+1,num[3],RecColor);		//�󷽵���
		LCD_Fill(num[2],num[1],num[2]+1,num[3]+1,RecColor);	//�ҷ�����		����
		LCD_ShowString(num[0]+(num[2]-num[0]-length*8)/2,(num[3]-num[1]-breadth)/2+num[1],string,StrColor,StrBlaColor);	//�м���ַ�
	}
}

/*****************************************
 * ��������		Judge_Touch
 * �������ܣ�	�ж������Ƶ������Ƿ񱻰���
 * �βΣ�		num�����ο��λ�����ꡣx1,y1,x2,y2
 * ����ֵ��		1�����µ��Ǹ�����0�����µĲ��Ǹ�����
******************************************/
static uint8_t Judge_Touch(uint16_t num[]) //�жϴ������� ���Ǹ����򷵻� 1�����򷵻� 0 
{
	if((tp_dev.x[0]>num[0]) && (tp_dev.x[0]<num[2]) && (tp_dev.y[0]>num[1]) && (tp_dev.y[0]<num[3]))	//Ŀ������
	{
		return 1;
	}
	else
		return 0;
}

/*****************************************
 * ��������		Gui_TouchAdjust
 * �������ܣ�	��ȡ���б����´������������ơ����д���������һ�������봥������������ȡ������������
 * �βΣ�			ButtonArea:��ť���� TouchName����������������
 * ����ֵ��		��	
******************************************/
static void Gui_TouchAdjust(uint16_t *ButtonArea[ButtonNumSIZE][LocationSize],uint16_t *TouchName)
{
	static uint8_t i = 0;
	tp_dev.scan(0);			//����ɨ��
	if(tp_dev.sta&TP_PRES_DOWN)			//������������
	{	
		if(tp_dev.x[0]<lcd_Width&&tp_dev.y[0]<lcd_height)	//�жϰ��������Ƿ�����ʾ����
		{
			for(i = 0;i < User_Gui.ButtonNumber;i++)		//ѭ������Ѱ�Ҵ�������
			{
				if(Judge_Touch(*ButtonArea[i]))		//�жϴ�������
				{
					if(User_Gui.Control.State != Start || i == 0)		//��������ִ��
					{
						EffectView(User_Gui.Interface,i+1);
						while(!PEN);
						EffectView(User_Gui.Interface,User_Gui.Interface);	//��������Ч����ʾ
						*TouchName = i+1;		//������������
					}
				}			
			}
			if(User_Gui.Interface == DepuInterface)		//��ҳ��Ĵ����������Ʊ任
				*TouchName += 3;			
		}
	}
}

/*****************************************
 * ��������		FunExecutive
 * �������ܣ�	����ִ�к��������������ض��壩
 * �βΣ�			��
 * ����ֵ��		��	
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
 * ��������		MastRefreshData
 * �������ܣ�	��ҳ������ˢ�º��������������ض��壩
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
__weak void MastRefreshData(void)
{
	
}

/*****************************************
 * ��������		DepuRefreshData
 * �������ܣ�	��ҳ������ˢ�º��������������ض��壩
 * �βΣ�			��
 * ����ֵ��		��	
******************************************/
__weak void DepuRefreshData(void)
{
	
}
