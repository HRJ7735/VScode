#include "Scheduler.h"
//简单调度器
static void Loop_100Hz(void) //10ms执行一次
{
    
}

static void Loop_50Hz(void) //20ms执行一次
{
	
}

static void Loop_20Hz(void) //50ms执行一次
{
	
}

static void Loop_10Hz(void) //100ms执行一次
{
	
}

static void Loop_5Hz(void) //200ms执行一次
{
    
}

static void Loop_2Hz(void) //500ms执行一次
{
	
}

static void Loop_1Hz(void) //1000ms执行一次
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
}

//系统任务配置，创建不同执行频率
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
	//初始化任务表
	for (index = 0; index < TASK_NUM; index++)
	{
		//计算每个任务的延时周期数
		sched_tasks[index].interval = TICK_PER_SECOND / sched_tasks[index].task_hz;
		//最短周期为1，也就是1ms
		if (sched_tasks[index].interval < 1)
		{
			sched_tasks[index].interval = 1;
		}
	}
}

//这个函数放到main函数的while(1)中，不停判断是否有线程应该执行
uint32_t Task_num_ms = 0; 
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//循环判断所有线程，是否应该执行

	for (index = 0; index < TASK_NUM; index++)
	{
		//获取系统当前时间，单位MS
		uint32_t tnow = Task_num_ms;
		//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
		if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval)
		{
			//更新线程的执行时间，用于下一次判断
			sched_tasks[index].last_run = tnow;
			//执行线程函数，使用的是函数指针
			sched_tasks[index].task_func();
		}
	}
}
