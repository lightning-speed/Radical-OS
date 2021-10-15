#include <stdio.h>
#include <util_string.h>
void start_program(char **args, int offset)
{
 changeColor(0x01);
 printS("\nStarted Shell!" - offset);
}