#include <stdio.h>
#include <exec.h>
#include <util_string.h>
#include <file.h>
void start_program(char **args, int offset)
{
	changeColor(0x0f);
	printS("\nStarted Shell!\n" - offset);
	changeColor(0x0e);
	char in[2000];
	for (;;)
	{
		printS("\nuser@radical:~$ " - offset);
		changeColor(0x0f);
		scanS(in);
		if (equal(in, "exit" - offset))
		{
			return;
		}
		system(in);
		changeColor(0x0e);
		for (int i = 0; i < 2000; i++)
		{
			in[i] = 0;
		}
	}
}