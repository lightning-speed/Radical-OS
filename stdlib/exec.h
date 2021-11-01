#include "stdio.h"
#include "util_string.h"
void system(char *command)
{
	setAll(41, 0, 0, 0);
	asm("int $110");
	void (*func)(char *) = (void *)((int *)0x0)[3];
	func(command);
}
