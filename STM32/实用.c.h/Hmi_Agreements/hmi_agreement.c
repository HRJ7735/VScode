#include "hmi_agreement.h"
#include "stdlib.h"
#include "stdio.h"

_usarthmi UHMI;

// _User HMI_User;		//�û�����

/******************************
**** �������ܣ�HMI��λ
**** �βΣ�			��
**** ����ֵ��		��
*******************************/
void HMI_Usart_Rest(void)		//��ʾ����λ
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t Rest[4] = "rest";
	HAL_UART_Transmit(&uart, (uint8_t*)&Rest, 4, 0xffff);				//��������
	HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//���ͽ���λ
}

/******************************
**** �������ܣ�ˢ��HMI����
**** �βΣ�				Page����Ҫˢ�µ�ҳ�棨�ַ�����ʽ��
**** ����ֵ��			��
*******************************/
void HMI_Usart_Refresh(uint8_t *Page)		//ˢ��ҳ��
{
	uint8_t End_Bit[3] = {0xff,0xff,0xff};
	uint8_t Head[5] = "page ";
	uint8_t *str;
	uint16_t size = strlen((char*)Page);
	str = (uint8_t*)malloc(size + 5);		//�����ڴ�
	if(str != NULL)	//�����ڴ�ɹ�
	{
		// sprintf((char*)str,"%s %s",Head,Page);
		memcpy(str,Head,5);
		memcpy(str + 5,Page,size);		
		HAL_UART_Transmit(&uart, (uint8_t*)str, size + 5, 0xffff);	//��������
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//���ͽ���λ
		free(str);	//�ͷ��ڴ�
	}
}

// /******************************
// **** �������ܣ��������ݵ�HMI��Ļ
// **** �βΣ�				SData����Ҫ���͵���ֵ���ַ�����ʽ��
// **** ����ֵ��			��
// *******************************/
// void HMI_Usart_SendDataValue(uint8_t *SData)		//���ڷ�����ֵ���ݵ�HMI��Ļ
// {
// 	uint8_t End_Bit[3] = {0xff,0xff,0xff};
// 	HAL_UART_Transmit(&uart, (uint8_t*)&SData, strlen((char*)SData), 0xffff);				//��������
// 	HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, sizeof(End_Bit), 0xffff);		//���ͽ���λ
// }

/******************************
**** �������ܣ����ػ���ʾ�ؼ�
**** �βΣ�				Obj���ؼ�����,State��״̬��1����ʾ��0�����أ�
**** ����ֵ��			��
*******************************/
void HMI_Usart_ShowHideobj(uint8_t *Obj,uint8_t State)		//��ָ���Ŀؼ�����ʾ�����ؽ��в���
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
		HAL_UART_Transmit(&uart, (uint8_t*)str, size + 6, 0xffff);	//��������
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);		//���ͽ���λ
		free(str);	//�ͷ��ڴ�
	}
}

/******************************
**** �������ܣ������ַ����ݵ�HMI
**** �βΣ�				Head���ؼ������֣�SData����ʾ���ַ�
**** ����ֵ��			��
*******************************/
void HMI_Usart_SendDataText(uint8_t *Head, uint8_t *SData)		//���ڷ����ַ����ݵ�HMI��Ļ
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
		HAL_UART_Transmit(&uart, (uint8_t*)str, size1 + size2 + 3, 0xffff);				//��������
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);			//���ͽ���λ
		free(str);	//�ͷ��ڴ�
	}
}

/******************************
**** �������ܣ��������ݵ��ؼ���value��
**** �βΣ�				Head���ؼ������֣�data������
**** ����ֵ��			��
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
		str = (uint8_t*)realloc(str,size1 + 1 + size2);		//�������ڴ�
		memcpy(str + size1 + 1, buf,size2);
		HAL_UART_Transmit(&uart, (uint8_t*)str, size1 + size2 + 1, 0xffff);	//��������
		HAL_UART_Transmit(&uart, (uint8_t*)&End_Bit, 3, 0xffff);			//���ͽ���λ
		free(str);	//�ͷ��ڴ�
	}
}

/******************************
**** �������ܣ�	���ݽ���
**** �βΣ�		_DA���յ�������
**** ����ֵ��	����
*******************************/
static float ResolvingData(uint8_t *_DA)
{
	int16_t DataBUf = 0;
	switch (_DA[2])		//�������ŵȼ���0(0)��1(10)��2(100)��
	{
		case _1E_0:		//������
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf;		//��������

		case _1E_1:		//10������
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf / 10.f;		//��������

		case _1E_2:		//100������
			DataBUf = *((int16_t*)(&_DA[3]));
			return (float)DataBUf / 100.f;		//��������
	
		default:
			return -1.f;
	}
}

/******************************
**** �������ܣ�	�������ݴ���
**** �βΣ�		_DA���յ�������
**** ����ֵ��	��
*******************************/
static void Acceptance_Data(uint8_t *_DA)
{
	float DataBuf = 0;
	DataBuf = ResolvingData(_DA);		//���ݽ���
	if(DataBuf != -1)		//����ɹ�
	{
		UHMI.ID = _DA[1];		
		switch (_DA[1])	//����ID
		{
			case _INT_VAID1: UHMI._IntRecData->_Data01 = (int16_t)DataBuf; break;
			case _INT_VAID2: UHMI._IntRecData->_Data02 = (int16_t)DataBuf; break;
			case _INT_VAID3: UHMI._IntRecData->_Data03 = (int16_t)DataBuf; break;
			case _INT_VAID4: UHMI._IntRecData->_Data04 = (int16_t)DataBuf; break;
			case _INT_VAID5: UHMI._IntRecData->_Data05 = (int16_t)DataBuf; break;	//��������

			case _FLO_VAID1: UHMI._FloatRecData->_Data10 = DataBuf; break;
			case _FLO_VAID2: UHMI._FloatRecData->_Data20 = DataBuf; break;
			case _FLO_VAID3: UHMI._FloatRecData->_Data30 = DataBuf; break;
			case _FLO_VAID4: UHMI._FloatRecData->_Data40 = DataBuf; break;
			case _FLO_VAID5: UHMI._FloatRecData->_Data50 = DataBuf; break;	//С������
		}
	}
}

/******************************
**** �������ܣ�HMI�������ݺ���
**** �βΣ�				RData�����յ�������
**** ����ֵ��			��
*******************************/
void HMI_Usart_ReciveData(uint8_t *RData,uint8_t size)
{
	if(size == 7)	//���ݳ�����ȷ
	{
		if(RData[0] == 0xCC)			//��ֵ��֡��֡ͷ��ȷ
			Acceptance_Data(RData);		//���ݴ���
		else if(RData[0] == 0xDD)		//�����࣬֡ͷ��ȷ
			HMI_Usart_FunctionSelect(&RData[1]);	//����ִ��
	}
}

/******************************
**** �������ܣ�HMI������ִ�к���ѡ��
**** �βΣ�				Rfun�����յ�����
**** ����ֵ��			��
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
