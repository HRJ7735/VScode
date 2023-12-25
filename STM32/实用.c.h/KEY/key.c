#include "key.h"


void KEY_Init()
{
	GPIO_InitTypeDef  GPIO_Initure;           //定义结构体对象
	__HAL_RCC_GPIOE_CLK_ENABLE();		   //开启（使能GPIOE时钟）
	
	GPIO_Initure.Pin = KEY1|KEY2|KEY3|KEY4;   //选择GPIOE引脚
	GPIO_Initure.Mode = GPIO_MODE_INPUT;      //选择GPIOE工作模式
	GPIO_Initure.Pull = GPIO_PULLUP;          //设置GPIOE的上拉下拉
	GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;//设置GPIOE的速率

	HAL_GPIO_Init(GPIOE , &GPIO_Initure);
	
}

//u8 Key_Scan(u8 mode)                 //按键扫描
//{ 
//	static u8 key_up = 1;             
//	if(mode == 1) key_up = 1;          //mode=1,支持按键连按，mode=0,不支持按键连按
//	if(key_up && (KEY1|KEY2|KEY3|KEY4))//进行按键扫描，返回键值
//	{
//		delay_ms(10);                  //消抖
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
