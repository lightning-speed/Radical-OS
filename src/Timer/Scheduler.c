#include "Scheduler.h"
struct TASK create_task(int func, int interval)
{
	struct TASK out;
	out.interval = interval;
	out.function = func;
	out.curr_time = 0;
	tasks[task_index] = out;
	out.index_in_array = task_index;
	task_index++;
	return out;
}
void run_tasks()
{
	for (int i = 0; i < task_index; i++)
	{
		if (tasks[i].curr_time == tasks[i].interval)
		{
			asm volatile("call *%0"
									 :
									 : "r"(tasks[i].function));
			tasks[i].curr_time = 0;
		}
		tasks[i].curr_time++;
	}
}
void dispose_task(struct TASK task)
{
	for (int i = task.index_in_array; i < task_index; i++)
		tasks[i] = tasks[i + 1];
	task_index--;
}