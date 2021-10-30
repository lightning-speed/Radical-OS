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
	setAll(11, 0, 0, 0);
	char *memu = (char *)io_adrress;
	for (int i = 0; i < name[i] != 0; i++)
	{
		memu[i] = name[i];
		memu[i + 1] = 0;
	}
	asm("int $110");
	return memu[0];
}
int get_file_size_of(char name[])
{
	setAll(40, 0, 0, 0);
	asm("int $110");
	int (*func)(char *) = (void *)((int *)0x0)[3];
	int out = func(name);
	return out;
}
void read_f(char *out, char name[], int length)
{
	setAll(10, 0, 0, 0);
	char *memu = (char *)io_adrress;
	for (int i = 0; i < name[i] != 0; i++)
	{
		memu[i] = name[i];
		memu[i + 1] = 0;
	}
	asm("int $110");
	for (int i = 0; i < length; i++)
		out[i] = ((char *)io_adrress)[i];
}
void write_file(char *name, char *text, int till)
{
	char *mem = (char *)io_adrress;
	for (int i = 0; i <= 32; i++)
	{
		mem[i] = name[i];
	}
	for (int i = 0; i < till; i++)
	{
		mem[i + 32] = text[i];
	}
	((int *)0x0)[0] = till;
	setAll(13, 0, 0, 0);
	asm("int $110");
}
void create_file(char *name)
{
	write_io(name);
	setAll(14, 0, 0, 0);
	asm("int $110");
}