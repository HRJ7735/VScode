#ifndef _SHT3X_H
#define _SHT3X_H

#include "stm32f1xx_hal.h"
#include "delay.h"
#include "sys.h"
#include "stdio.h"
#include "usart.h"
#include "string.h"
 
extern uint8_t humiture_buff1[20];

void SHT30_Init(void);
void IIC_ACK(void);//ȷ���ַ�����ʾ�����������Ѿ�ȷ�Ͻ�������
void IIC_NACK(void);//��ȷ���ַ�����ʾ���ݽ���������߻�δ�������
uint8_t IIC_wait_ACK(void);//�ȴ�����ȷ���ַ�
void IIC_Start(void);//�ȴ�IIC�������ݿ�ʼ
void IIC_Stop(void);//IIC��������ֹͣ
void IIC_SendByte(uint8_t byte);//IIC��������
uint8_t IIC_RcvByte(void);//IIC��������
void SHT30_read_result(uint8_t addr);//SHT30��ʪ�ȴ�������ʼ��ȡ����
//SHT30_read_result(0x44);//ADDR�Ĵ�������ַѡ�����ţ���GND��ַΪ0x44����VDD��ַΪ0x45
#endif

