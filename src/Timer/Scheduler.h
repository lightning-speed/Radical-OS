#pragma once
struct TASK
{
	int interval;
	int function;
	int curr_time;
	int index_in_array;
} __attribute__((packed));
struct TASK tasks[256];
int task_index;

struct TASK create_task(int func, int interval);
void run_tasks();
void dispose_task(struct TASK task);