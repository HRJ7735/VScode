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
void IIC_ACK(void);//确认字符，表示发来的数据已经确认接收无误
void IIC_NACK(void);//无确认字符，表示数据接收有误或者还未接收完成
uint8_t IIC_wait_ACK(void);//等待接收确认字符
void IIC_Start(void);//等待IIC传输数据开始
void IIC_Stop(void);//IIC传输数据停止
void IIC_SendByte(uint8_t byte);//IIC发送数据
uint8_t IIC_RcvByte(void);//IIC接收数据
void SHT30_read_result(uint8_t addr);//SHT30温湿度传感器开始读取数据
//SHT30_read_result(0x44);//ADDR寄存器，地址选择引脚，接GND地址为0x44，接VDD地址为0x45
#endif

