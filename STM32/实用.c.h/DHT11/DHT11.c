#include "dht11.h"

uint8_t Data[5]={0x00,0x00,0x00,0x00,0x00};   //Data�洢��ȡ����ʪ����Ϣ
//extern uint8_t Data[5];
//Data[0]ʪ��Data[2]�¶�Data[4]��     Data[1]��Data[3]�¶Ⱥ�ʪ�ȵ�С�����֣�����Ϊ0
//����stm32f1ϵ�� 72mhz������1ms
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
/*//����stm32f4ϵ�� 168mhz������1us
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
void DHT_GPIO_SET_OUTPUT(void)     //����GPIOxΪ���ģʽ��MCU��IO����DHT11�������źţ�
{
	GPIO_InitTypeDef GPIO_InitStructure;    //��GPIO_InitTypeDef�ṹ�����޸�IO�ڲ������ṹ���Ա��
	GPIO_InitStructure.Pin=DHT11_PIN;      //���õĸ�ʽ�����ϸ���ѭע�ͣ�����GPIO_PIN_define
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStructure.Pull=;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_IO,&GPIO_InitStructure);
}

void DHT_GPIO_SET_INPUT(void)     //����GPIOxΪ����ģʽ��DHT11��MUC��IO����ƽ�źţ��ź����������ʪ����Ϣ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin=DHT11_PIN;
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DHT11_IO,&GPIO_InitStructure);
}

/*------------------------------*/

/*
     uint8_t DHT_Read_Byte(void)����ת��ɼ�DHT11���͸�IO�ڵĵ�ƽ�źţ�8λ����
*/
uint8_t DHT_Read_Byte(void)  //��DHT11��ȡһλ��8�ֽڣ��ź�
{
	 uint8_t ReadData=0;  //ReadData���ڴ��8bit���ݣ���8�����ζ�ȡ��1bit���ݵ����
	 uint8_t temp;      //��ʱ����źŵ�ƽ��0��1��
	 uint8_t retry=0;   //retry���ڷ�ֹ����
	 uint8_t i;    
	 for(i=0; i<8; i++)   //һ����ʪ���źŶ�ȡ��λ
	 {
			while(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==0 && retry<100)  
			//�ȴ�ֱ��DHT11����ߵ�ƽ����PA5=1�������أ���ʾ��ʼ�������ݣ������ж�0 or 1������ѭ����ִ�к����жϣ���PA5=0����һֱѭ���ȴ���
			{
					Delay_us(1);
				  retry++;             //retry��ֹPA5��ȡ�������ݿ�������һ����������100us��retry������100������ѭ����
			}
			retry=0;
			
			Delay_us(40);    //��ʱ30us
			//����ʱ��ͼ��DHT���ظߵ�ƽ�ź�ά��26us~28us��ʾ0��	ά��70us��ʾ1
		  //��ʱ30us�����IO��ȡ�����Ǹߵ�ƽ��˵���ɼ���1�����IO��ȡ���͵�ƽ��˵���ɼ���0
			//��ȡ��ƽ�ź��ݴ�temp�ڣ�����ѹ��ReadData��
			if(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==1)   temp=1;
			 else   temp=0;

			 while(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==1 && retry<100)
			//�ȴ�ֱ��DHT11����͵�ƽ����ʾ�˳�������1bit�źŽ�����ϡ�
			 {
				 Delay_us(1);
				 retry++;
			 }
			 retry=0;
			 
			 ReadData<<=1;    //ReadData���ź���ȫ������һλ���ճ�ĩβλ��
			 ReadData |= temp;        //��tempд��ReadData
	 }

		return ReadData;
}

/*------------------------------*/

/*
     uint8_t DHT_Read(void)�������ʱ��
*/
uint8_t DHT_Read(void)
{
	 uint8_t retry=0;
	 uint8_t i;
		
	 DHT_GPIO_SET_OUTPUT();    //IO����Ϊ���ģʽ���ڴ�����ʼ��MCUҪ��DHT11�����ź�
	 HAL_GPIO_WritePin(DHT11_IO,DHT11_PIN,GPIO_PIN_RESET);   //IO->DHT11:�����͵�ƽ18ms��Ӧʱ��Ҫ��
	 HAL_Delay(18);
	 HAL_GPIO_WritePin(DHT11_IO,DHT11_PIN,GPIO_PIN_SET);   //IO->DHT11:������ߵ�ƽ20us
	 Delay_us(20);
	
	//MCUͨ��IO��DHT11����������ϡ�������DHT11��IO������Ӧ,IOתΪ����ģʽ������֮��Ϳ�ʼ�źŵ�ת���ȡ��
	DHT_GPIO_SET_INPUT();
	Delay_us(20);
	if(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==0) //DHT11���ص͵�ƽ��Ӧ����ȡ���͵�ƽ��˵��DHT11����Ӧ��
	{
		//��������DHT11���͵�ƽһ��ʱ������ߵ�ƽһ��ʱ��
		while(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==0 && retry<100)  
		{
		   Delay_us(1);
			 retry++;
		}
		retry=0;
		while(HAL_GPIO_ReadPin(DHT11_IO,DHT11_PIN)==1 && retry<100) 
		{
		   Delay_us(1);
			 retry++;
		}
		retry=0;
		
		//һ������40λ��һ��DHT_Read_Byte����8λ������ȡ5�Ρ��洢��Data[]�С���Data[]����Ϊȫ�֣�
		for(i=0; i<5; i++)
		{
			 Data[i] = DHT_Read_Byte();  //ÿ�ζ�ȡһ�ֽڣ�8λ��
		}
		Delay_us(50);
		//˵����Data[0]ʪ�ȣ� Data[2]�¶ȡ�Data[1]��Data[3]�ֱ�Ϊ0��2��С��λ��Data[4]����У�顣
	}
	
	 uint32_t sum=Data[0]+Data[1]+Data[2]+Data[3];  //У��
	 if((sum)==Data[4])    return 1;  
	   else   return 0;
	
}




