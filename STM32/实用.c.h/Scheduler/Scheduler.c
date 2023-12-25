#include "Scheduler.h"
//�򵥵�����
static void Loop_100Hz(void) //10msִ��һ��
{
    
}

static void Loop_50Hz(void) //20msִ��һ��
{
	
}

static void Loop_20Hz(void) //50msִ��һ��
{
	
}

static void Loop_10Hz(void) //100msִ��һ��
{
	
}

static void Loop_5Hz(void) //200msִ��һ��
{
    
}

static void Loop_2Hz(void) //500msִ��һ��
{
	
}

static void Loop_1Hz(void) //1000msִ��һ��
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
}

//ϵͳ�������ã�������ִͬ��Ƶ��
static task_t sched_tasks[] =
	{
		{Loop_100Hz, 100, 0, 0},
		{Loop_50Hz, 50, 0, 0},
		{Loop_20Hz, 20, 0, 0},
		{Loop_10Hz, 10, 0, 0},
		{Loop_5Hz, 5, 0, 0},
		{Loop_2Hz, 2, 0, 0},
		{Loop_1Hz, 1, 0, 0}};

#define TASK_NUM (sizeof(sched_tasks) / sizeof(task_t))

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	//��ʼ�������
	for (index = 0; index < TASK_NUM; index++)
	{
		//����ÿ���������ʱ������
		sched_tasks[index].interval = TICK_PER_SECOND / sched_tasks[index].task_hz;
		//�������Ϊ1��Ҳ����1ms
		if (sched_tasks[index].interval < 1)
		{
			sched_tasks[index].interval = 1;
		}
	}
}

//��������ŵ�main������while(1)�У���ͣ�ж��Ƿ����߳�Ӧ��ִ��
uint32_t Task_num_ms = 0; 
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��

	for (index = 0; index < TASK_NUM; index++)
	{
		//��ȡϵͳ��ǰʱ�䣬��λMS
		uint32_t tnow = Task_num_ms;
		//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
		if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval)
		{
			//�����̵߳�ִ��ʱ�䣬������һ���ж�
			sched_tasks[index].last_run = tnow;
			//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
			sched_tasks[index].task_func();
		}
	}
}
