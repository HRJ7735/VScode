#include "hmi_agreement.h"
#include "stdlib.h"
#include "stdio.h"

_usarthmi UHMI;

// _User HMI_User;		//用户数据

/******************************
**** 函数功能：HMI复位
**** 形参：			无
**** 返回值：		无
*******************************/
void HMI_Usart_Rest(void)		//显示屏复位
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t Rest[4] = "rest";
	HAL_UART_Transmit(&uart, (uint8_t*)&Rest, 4, 0xffff);				//发送数据
	HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//发送结束位
}

/******************************
**** 函数功能：刷新HMI界面
**** 形参：				Page：需要刷新的页面（字符串形式）
**** 返回值：			无
*******************************/
void HMI_Usart_Refresh(uint8_t *Page)		//刷新页面
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t Head[5] = "page ";
	uint8_t *str;
	uint16_t size = strlen((char*)Page);
	str = (uint8_t*)malloc(size + 5);		//申请内存
	if(str != NULL)	//申请内存成功
	{
		// sprintf((char*)str,"%s %s",Head,Page);
		memcpy(str,Head,5);
		memcpy(str + 5,Page,size);		
		HAL_UART_Transmit(&uart, (uint8_t*)str, size + 5, 0xffff);	//发送数据
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//发送结束位
		free(str);	//释放内存
	}
}

// /******************************
// **** 函数功能：发送数据到HMI屏幕
// **** 形参：				SData：需要发送的数值（字符串形式）
// **** 返回值：			无
// *******************************/
// void HMI_Usart_SendDataValue(uint8_t *SData)		//串口发送数值数据到HMI屏幕
// {
// 	uint8_t End_Bit[3] = {0xff,0xff,0xff};
// 	HAL_UART_Transmit(&uart, (uint8_t*)&SData, strlen((char*)SData), 0xffff);				//发送数据
// 	HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, sizeof(End_Bit), 0xffff);		//发送结束位
// }

/******************************
**** 函数功能：隐藏或显示控件
**** 形参：				Obj：控件名字,State：状态（1，显示。0，隐藏）
**** 返回值：			无
*******************************/
void HMI_Usart_ShowHideobj(uint8_t *Obj,uint8_t State)		//对指定的控件的显示和隐藏进行操作
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t Sho[4] = "vis ";
	uint8_t *str;
	uint16_t size = sizeof(Obj);
	str = (uint8_t*)malloc(size + 6);
	if(str != NULL)
	{
		memcpy(str,Sho,4);
		memcpy(str + 4,Obj,size);
		memcpy(str + 4 + size,(uint8_t*)",",1);
		if(State)
			memcpy(str + 5 + size,(uint8_t*)"1",1);
		else
			memcpy(str + 5 + size,(uint8_t*)"0",1);
		HAL_UART_Transmit(&uart, (uint8_t*)str, size + 6, 0xffff);	//发送数据
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//发送结束位
		free(str);	//释放内存
	}
}

/******************************
**** 函数功能：发送字符数据到HMI
**** 形参：				Head：控件的名字，SData：显示的字符
**** 返回值：			无
*******************************/
void HMI_Usart_SendDataText(uint8_t *Head, uint8_t *SData)		//串口发送字符数据到HMI屏幕
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t *str;
	uint16_t size1 = strlen((char*)Head);
	uint16_t size2 = strlen((char*)SData);
	str = (uint8_t*)malloc(size1 + size2 + 3);
	if(str != NULL)
	{
		memcpy(str,Head,size1);
		memcpy(str + size1,(uint8_t*)"=",1);
		memcpy(str + size1 + 1,(uint8_t*)"\"",1);
		memcpy(str + size1 + 2,SData,size2);
		memcpy(str + size1 + size2 + 2,(uint8_t*)"\"",1);
		HAL_UART_Transmit(&uart, (uint8_t*)str, size1 + size2 + 3, 0xffff);				//发送数据
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);			//发送结束位
		free(str);	//释放内存
	}
}

/******************************
**** 函数功能：发送数据到控件（value）
**** 形参：				Head：控件的名字，data：数据
**** 返回值：			无
*******************************/
void HMI_Usart_SendDataValue(uint8_t *Head, int16_t data)
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t buf[10];
	uint8_t *str;
	uint16_t size1 = strlen((char*)Head);
	sprintf((char*)&buf,"%d",data);
	uint16_t size2 = strlen((char*)buf);

	str = (uint8_t*)malloc(size1 + 1);
	if(str != NULL)
	{
		memcpy(str,Head,size1);
		memcpy(str + size1,(uint8_t*)"=",1);
		str = (uint8_t*)realloc(str,size1 + 1 + size2);		//再申请内存
		memcpy(str + size1 + 1, buf,size2);
		HAL_UART_Transmit(&uart, (uint8_t*)str, size1 + size2 + 1, 0xffff);	//发送数据
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);			//发送结束位
		free(str);	//释放内存
	}
}

/******************************
**** 函数功能：	数据解算
**** 形参：		_DA接收到的数据
**** 返回值：	数据
*******************************/
static float ResolvingData(uint8_t *_DA)
{
	int16_t DataBUf = 0;
	switch (_DA[2])		//数据缩放等级（0(0)，1(10)，2(100)）
	{
		case _1E_0:		//无缩放
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf;		//解算数据

		case _1E_1:		//10倍缩放
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf / 10.f;		//解算数据

		case _1E_2:		//100倍缩放
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf / 100.f;		//解算数据
	
		default:
			return -1.f;
	}
}

/******************************
**** 函数功能：	接收数据处理
**** 形参：		_DA接收到的数据
**** 返回值：	无
*******************************/
static void Acceptance_Data(uint8_t *_DA)
{
	float DataBuf = 0;
	DataBuf = ResolvingData(_DA);		//数据解算
	if(DataBuf != -1)		//解算成功
	{
		UHMI.ID = _DA[1];		
		switch (_DA[1])	//数据ID
		{
			case _INT_VAID1: UHMI._IntRecData->_Data01 = (int16_t)DataBuf; break;
			case _INT_VAID2: UHMI._IntRecData->_Data02 = (int16_t)DataBuf; break;
			case _INT_VAID3: UHMI._IntRecData->_Data03 = (int16_t)DataBuf; break;
			case _INT_VAID4: UHMI._IntRecData->_Data04 = (int16_t)DataBuf; break;
			case _INT_VAID5: UHMI._IntRecData->_Data05 = (int16_t)DataBuf; break;	//整型数据

			case _FLO_VAID1: UHMI._FloatRecData->_Data10 = DataBuf; break;
			case _FLO_VAID2: UHMI._FloatRecData->_Data20 = DataBuf; break;
			case _FLO_VAID3: UHMI._FloatRecData->_Data30 = DataBuf; break;
			case _FLO_VAID4: UHMI._FloatRecData->_Data40 = DataBuf; break;
			case _FLO_VAID5: UHMI._FloatRecData->_Data50 = DataBuf; break;	//小数数据
		}
	}
}

/******************************
**** 函数功能：HMI接收数据函数
**** 形参：				RData：接收到的数据
**** 返回值：			无
*******************************/
void HMI_Usart_ReciveData(uint8_t *RData,uint8_t size)
{
	if(size == 7)	//数据长度正确
	{
		if(RData[0] == 0xCC)			//数值类帧，帧头正确
			Acceptance_Data(RData);		//数据处理
		else if(RData[0] == 0xDD)		//功能类，帧头正确
			HMI_Usart_FunctionSelect(&RData[1]);	//功能执行
	}
}

/******************************
**** 函数功能：HMI功能类执行函数选择
**** 形参：				Rfun：接收的数据
**** 返回值：			无
*******************************/
void HMI_Usart_FunctionSelect(uint8_t *Rfun)
{
	switch (*Rfun)
	{
		case Start:	UHMI.StartFlag = 1;	 break;	
		case Stop:	UHMI.StartFlag = 0;  break;
		case mode1:	UHMI.Mode = 1;	break;
		case mode2:	UHMI.Mode = 2;	break;
		case mode3:	UHMI.Mode = 3;	break;
		case mode4:	UHMI.Mode = 4;	break;
		case mode5:	UHMI.Mode = 5;	break;
		default: UHMI.Mode = 0; UHMI.StartFlag = 0; break;
	}
}
