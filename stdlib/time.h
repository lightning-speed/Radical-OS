#include "stdio.h"
#pragma once
void sleepD()
{
  int *mem = (int *)0x0;
  char *slp = (char *)mem[0];
  asm volatile("call *%0"
               :
               : "r"((slp)));
}
void sleep(int ms)
{
  setAll(20, 0, 0, 0);
  asm("int $110");
  for (int i = 0; i < ms; i++)
  {
    sleepD();
  }
}
