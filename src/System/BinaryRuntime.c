#include "BinaryRuntime.h"
char *binary_mem = (char *)0xAAAAAF;
void load_binary(char *binary, int till)
{
  for (int i = 0; i < till; i++)
  {
    binary_mem[i] = binary[i];
  }
}
void clear_binary_mem(int till)
{
  for (int i = 0; i < till; i++)
    binary_mem[i] = 0;
}
void run_binary()
{
  asm volatile("call *%0"
               :
               : "r"(binary_mem));
}