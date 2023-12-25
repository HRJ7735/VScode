#ifndef __AD5676_H
#define __AD5676_H			    
#include "common.h"
#include "predef.h"

extern const float Range_Convert;
extern const float Ref_K;
extern const float Parameter_VS;
extern float Parameter_IS;

extern const u16 DAC_Sel_Map[4];

#define DAC_SELNONE()    (GPIOE->ODR |= 0xf00)
#define DAC_SEL(x)   	   (GPIOE->ODR &= DAC_Sel_Map[x])

void Ad5676_init(void);
void DaPortSend(u8 ADCx,u8 Chlx,u16 Value);
void Set_Chl_IV(u8 Chl,u16 VSet,u16 ISet);
int32_t Cali_SetValue(u8 I_V,u16 Set_Value,int32_t k,int16_t b);

#endif
