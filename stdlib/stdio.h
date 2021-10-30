#pragma once
#include <util_string.h>
const int io_adrress = 0xA00000;
char *mem = (char *)0x0;
const int passing_address = 81;
void setAll(char type, char arg1, char arg2, char arg3);
void printChar(char in)
{
	setAll(40, 0, 0, 0);
	asm("int $110");
	void (*func)(char) = (void *)((int *)0x0)[1];
	func(in);
}
char readChar()
{
	mem[81] = 0;
	while (mem[81] == 0)
	{
	}
	return mem[81];
}
void changeColor(char color)
{
	setAll(0, color, 0, 0);
	asm("int $110");
}
void changeCursorPosition(char x, char y)
{
	setAll(2, x, y, 0);
	asm("int $110");
}
int getX()
{
	setAll(4, 0, 0, 0);
	asm("int $110");
	return mem[83];
}
void setAll(char type, char arg1, char arg2, char arg3)
{
	mem[82] = type;
	mem[83] = arg1;
	mem[84] = arg2;
	mem[85] = arg3;
}
void printS(char str[])
{
	for (int i = 0; i < length(str); i++)
	{
		setAll(40, 0, 0, 0);
		asm("int $110");
		void (*func)(char) = (void *)((int *)0x0)[1];
		func(str[i]);
	}
}
void scanS(char out[])
{
	char tp = 0;
	int index = 0;
	while ((tp = readChar()) != '\n')
	{
		out[index] = tp;
		out[index + 1] = 0;
		if (out[index] == '\b')
		{
			if (index > 0)
			{
				out[index] = 0;
				out[index - 1] = 0;
				printChar('\b');
				index -= 1;
			}
		}
		else
		{
			printChar(tp);
			index++;
		}
	}
}
void write_io(char *in)
{
	char *memr = (char *)io_adrress;
	for (int i = 0; in[i] != 0; i++)
	{
		memr[i] = in[i];
		memr[i + 1] = 0;
	}
}
