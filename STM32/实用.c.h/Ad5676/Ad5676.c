#include "Ad5676.h"

void Ad5676_init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE, ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);            
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_15;                       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                    
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIOE->ODR |= 0x8f00;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                    
  GPIO_Init(GPIOB, &GPIO_InitStructure);                          
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);           
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);           
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);           

	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);             
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE);            

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                    
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                      
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	                      
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                        
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                
	SPI_InitStructure.SPI_CRCPolynomial = 7;	                          
	SPI_Init(SPI2, &SPI_InitStructure);                                 

	SPI_Cmd(SPI2, ENABLE);
}

void DaPortSend(u8 DACx,u8 Chlx,u16 Value)
{	
	DAC_SELNONE();
	delay_us(1);
	DAC_SEL(DACx);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(0x30 + Chlx));
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(Value >> 8));
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2,(Value & 0xff));
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_BSY) == SET);
	DAC_SELNONE();
}


void Set_Chl_IV(u8 Chl,u16 VSet,u16 ISet)
{
	u8 i,j,k;
	
	for(i=0;i<4;i++)
	{
		j = (Chl & 0xf)/4;
		k = (Chl & 0xf)%4;
		k *= 2;
		DaPortSend(j,k,ISet);
		k += 1;
		DaPortSend(j,k,VSet);
	}
}

int32_t Cali_SetValue(u8 I_V,u16 Set_Value,int32_t k,int16_t b)
{
	int32_t Set_Temp;
	
	Set_Temp = Set_Value*(k/Ref_K) + b;
	Set_Temp *= Range_Convert;
	if(I_V == V_TYPE)
	{
		Set_Temp *= Parameter_VS;
		Set_Temp = Set_Temp > (65536*1.1*Parameter_VS) ? 
		(65536*1.1*Parameter_VS) : Set_Temp < 0 ? 0 : Set_Temp;
	}
	else
	{
		Set_Temp *= Parameter_IS;
		Set_Temp = Set_Temp > (65536*1.1*Parameter_IS) ? 
		(65536*1.1*Parameter_IS) : Set_Temp < 0 ? 0 : Set_Temp;
	}
	
	return Set_Temp;
}
