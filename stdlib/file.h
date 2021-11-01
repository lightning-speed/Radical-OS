#include "stdio.h"
#pragma once
void read_file(char out[], char name[], int length)
{
	setAll(40, 0, 0, 0);
	asm("int $110");
	char *(*func)(char *) = (void *)((int *)0x0)[2];
	for (int i = 0; i < length; i++)
	{
		out[i] = func(name)[i];
	}
}
int does_file_exists(char name[])
{
	setAll(41, 0, 0, 0);
	asm("int $110");
	int (*func)(char *) = (void *)((int *)0x0)[1];
	int out = func(name);
	return out;
}
int get_file_size_of(char name[])
{
	setAll(40, 0, 0, 0);
	asm("int $110");
	int (*func)(char *) = (void *)((int *)0x0)[3];
	int out = func(name);
	return out;
}
void write_file(char *name, char *text, int till)
{
	setAll(41, 0, 0, 0);
	asm("int $110");
	void (*func)(char *, char *, int) = (void *)((int *)0x0)[2];
	func(name, text, till);
}
void create_file(char *name)
{
	setAll(42, 0, 0, 0);
	asm("int $110");
	void (*func)(char *, char *, int) = (void *)((int *)0x0)[1];
	char n[0];
	func(name, n, 0);
}