#include "stdio.h"
#pragma once
struct TASK
{
	int interval;
	int function;
	int curr_time;
	int index_in_array;
} __attribute__((packed));
void sleep(int ms)
{
	setAll(20, 0, 0, 0);
	asm("int $110");
	void (*func)(int t) = (void *)((int *)0x0)[0];
	func(ms);
}
struct TASK create_task(int func_address, int interval)
{
	setAll(20, 0, 0, 0);
	asm("int $110");
	struct TASK (*func)(int, int) = (void *)((int *)0x0)[1];
	return func(func_address, interval);
}
void dispose_task(struct TASK tsk)
{
	setAll(20, 0, 0, 0);
	asm("int $110");
	void (*func)(struct TASK) = (void *)((int *)0x0)[2];
	func(tsk);
}