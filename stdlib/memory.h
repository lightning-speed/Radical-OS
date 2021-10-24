#include "stdio.h"
#pragma once
char *malloc(int len)
{
 int *mem = (int *)0x0;
 mem[0] = len;
 setAll(45, 0, 0, 0);
 asm("int $110");
 return (char *)mem[0];
}