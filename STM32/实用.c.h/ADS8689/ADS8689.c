#include "ADS8689.h"
//对于stm32f1系列 72mhz大致是1ms
void Delay_ms(uint32_t ms)
{
		uint16_t i = 0;
		while(ms--)
		{
			i = 4050;
			while(i--);
		};
}
void Delay_us(uint32_t us)
{
		uint16_t i = 0;
		while(us--)
		{
			i = 2;
			while(i--);
		}
}
/*//对于stm32f4系列 168mhz大致是1us
void my_delay_us(u32 us)
{
		u8 i = 0;
		while(us--)
		{
			i = 42;
			while(i--);
		};
}
 
void delay_ms(u32 ms)
{
		u16 i = 0;
		while(ms--)
		{
			i = 41750;
			while(i--);
		};

}*/


/*
      #include "ADS8689.h"
#include <stdio.h>
#include "delay.h"
//初始化ADS8689，并且检验读入寄存器数据和写入的是否一样
//返回TURE则说明初始化正常，否则错误
uint8_t receive[4] = {0};
#ifdef SOFT_ADC
void ADS8689_Init(void)	
{
	GPIO_SetMode(PD, BIT0 | BIT1 | BIT3 | BIT4, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PD, BIT2, GPIO_PMD_INPUT);
	ADS8689_CS = 1;
	ADS8689_SCLK = 0;
	ADS8689_SDIN = 1;
	ADS8689_RST = 0;
	delay_ms(10);
	ADS8689_RST = 1;
	delay_ms(10);
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0040);	// 外部双极性24.576
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0041);	// 双极性20.48
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0042);	// 双极性12.889
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0043);	// 双极性10.24
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0044);	// 双极性5.12
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0048);	// 单极性12.889
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0049);	// 单极性10.24
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x004A);	// 单极性6.144
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x004B);	// 单极性5.12

	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0000);	// 内部双极性24.576
	 ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0001);	// 双极性20.48
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0002);	// 双极性12.889
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0003);	// 双极性10.24
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0004);	// 双极性5.12
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0008);	// 单极性12.889
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x0009);	// 单极性10.24
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x000A);	// 单极性6.144
	// ADS8689_ReadWrite(ADS8689_WRITE_FULL, ADS8689_RANGE_SEL_REG, 0x000B);	// 单极性5.12
}

uint8_t *ADS8689_ReadWrite(uint8_t command, uint8_t address, uint16_t data)
{
	uint8_t buff[4] = {0};
	uint8_t rece_byte = 0;
	uint8_t i = 0, j = 0, byte = 0;
	buff[0] = (command << 1);
    buff[1] = address;
    buff[2] = ((data >> 8) & 0xff);
    buff[3] = (data & 0xff);
	ADS8689_CS = 0;
	delay_us(1);
	for (i = 0; i < 4; i++)
	{
		byte = buff[i];
		for (j = 0; j < 8; j++)
		{
			// rece_byte = 0;
			if(byte & 0x80)
			{
				ADS8689_SDIN = 1;
			}
			else
			{
				ADS8689_SDIN = 0;
			}
			byte <<= 1;
			delay_us(1);
			ADS8689_SCLK = 1;
			rece_byte <<= 1;
			rece_byte |= ADS8689_SDO;
			delay_us(1);
			ADS8689_SCLK = 0;
		}
		receive[i] = rece_byte;
	}
	ADS8689_SCLK = 0;
	ADS8689_CS = 1;
	delay_us(1);
	return receive;
}

#else
void ADS8689_Init(void)
{
	/* Select HCLK as the clock source of SPI0 */
    CLK_SetModuleClock(SPI2_MODULE, CLK_CLKSEL1_SPI2_S_HCLK, MODULE_NoMsk);
    /* Enable SPI0 peripheral clock */
    CLK_EnableModuleClock(SPI2_MODULE);
	/* Setup SPI0 multi-function pins */
    SYS->GPD_MFP &= ~(SYS_GPD_MFP_PD0_Msk | SYS_GPD_MFP_PD1_Msk | SYS_GPD_MFP_PD2_Msk | SYS_GPD_MFP_PD3_Msk);
    SYS->GPD_MFP |= SYS_GPD_MFP_PD0_SPI2_SS0 | SYS_GPD_MFP_PD1_SPI2_CLK | SYS_GPD_MFP_PD2_SPI2_MISO0 | SYS_GPD_MFP_PD3_SPI2_MOSI0;
    SYS->ALT_MFP &= ~(SYS_ALT_MFP_PD0_Msk | SYS_ALT_MFP_PD1_Msk | SYS_ALT_MFP_PD2_Msk | SYS_ALT_MFP_PD3_Msk);
    SYS->ALT_MFP |= SYS_ALT_MFP_PD0_SPI2_SS0 | SYS_ALT_MFP_PD1_SPI2_CLK | SYS_ALT_MFP_PD2_SPI2_MISO0 | SYS_ALT_MFP_PD3_SPI2_MOSI0;
	SPI_Open(SPI2, SPI_MASTER, SPI_MODE_0, 8, 2000000);
	SPI_EnableAutoSS(SPI2, SPI_SS0, SPI_SS_ACTIVE_LOW);
}

void ADS8689_Write(uint8_t command, uint16_t address, uint16_t data)
{
	int timeout = 10000;
	uint8_t buf[4] = {0};
	uint8_t i = 0, j = 0, byte = 0;
	buf[0] = (command << 1) | ((address >> 8) & 1);
    buf[1] = (address & 0xFF);
    buf[2] = ((data >> 8) & 0xFF);
    buf[3] = (data & 0xFF);
	for (int i = 0; i < 4; i++)
	{
		SPI_WRITE_TX0(SPI2, buf[i]);
		SPI_TRIGGER(SPI2);			// 没有使用FIFO就需要使用此句
		while (SPI_IS_BUSY(SPI2))	// 等待发送完成
		{
			if(timeout--){}
			else break;
		}
	}
}

#endif
*/