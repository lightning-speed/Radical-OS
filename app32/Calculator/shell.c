#include <stdio.h>
#include <exec.h>
#include <util_string.h>
void start_program(char **args, int offset)
{
 changeColor(0x0f);
 printS("\nStarted Shell!\n" - offset);
 changeColor(0x0e);
 char in[1000];
 for (;;)
 {
		printS("\nuser@radical:~$ " - offset);
		changeColor(0x0f);
		scanS(in);
		system(in);
		changeColor(0x0e);
		for (int i = 0; i < 1000; i++)
		{
			in[i] = 0;
		}
 }
}