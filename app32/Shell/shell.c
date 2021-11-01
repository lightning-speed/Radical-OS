#include <stdio.h>
#include <exec.h>
#include <util_string.h>
#include <time.h>
void start_program(char **args, int offset)
{
	int echo = 1;
	changeColor(0x0f);
	printS("\nStarted Shell!\n" - offset);
	changeColor(0x0e);
	char in[2000];
	for (;;)
	{
		if (echo)
			printS("\nuser@radical:# " - offset);
		else
			printChar('\n');
		changeColor(0x0f);
		scanS(in);
		if (equal(in, "exit" - offset))
		{
			return;
		}
		else if (equal(in, "@echo off" - offset))
		{
			echo = 0;
		}
		else if (equal(in, "@echo on" - offset))
		{
			echo = 1;
		}
		else
			system(in);
		changeColor(0x0e);
		for (int i = 0; i < 2000; i++)
		{
			in[i] = 0;
		}
	}
}
