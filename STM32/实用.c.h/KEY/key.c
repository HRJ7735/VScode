#include "key.h"


void KEY_Init()
{
	GPIO_InitTypeDef  GPIO_Initure;           //����ṹ�����
	__HAL_RCC_GPIOE_CLK_ENABLE();		   //������ʹ��GPIOEʱ�ӣ�
	
	GPIO_Initure.Pin = KEY1|KEY2|KEY3|KEY4;   //ѡ��GPIOE����
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //ѡ��GPIOE����ģʽ
	GPIO_Initure.Pull = GPIO_PULLUP;          //����GPIOE����������
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;//����GPIOE������

	HAL_GPIO_Init(GPIOE , &GPIO_Initure);
	
}

//u8 Key_Scan(u8 mode)                 //����ɨ��
//{ 
//	static u8 key_up = 1;             
//	if(mode == 1) key_up = 1;          //mode=1,֧�ְ���������mode=0,��֧�ְ�������
//	if(key_up && (KEY1|KEY2|KEY3|KEY4))//���а���ɨ�裬���ؼ�ֵ
//	{
//		delay_ms(10);                  //����
//		key_up=0;
//		if(KEY1 == 0) return KEY1_RE;
//		else if(KEY2 == 0) return KEY2_RE;
//		else if(KEY3 == 0) return KEY3_RE;
//		else if(KEY4 == 0) return KEY4_RE;
//	}
//	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1) key_up=1;
//	return 0;
//	
//}
