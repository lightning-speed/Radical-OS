#include "stdio.h"
char *read_file(char name[])
{
 pass_address((int)name);
 setAll(10, 0, 0, 0);
 asm("int $110");
 return (char *)get_address();
}