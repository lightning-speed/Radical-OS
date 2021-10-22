#include "BinaryRuntime.h"
#include <FS/vfs.h>
#include <System/MemoryManager.h>
const int bm = 0xAAAAAF;
char *binary_mem = (char *)0xAAAAAA;
void binary_runtime_init()
{
}
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
void run_binary(int len)
{
  binary_mem += len;
  asm volatile("call *%0"
               :
               : "r"((binary_mem - len)));
  binary_mem -= len;
}
void set_binary_location(int to)
{
  binary_mem = (char *)to;
}
void run_binary_file(char *fileName)
{
  int *temp = (int *)0x0;
  temp[5] = (int)binary_mem;
  clear_binary_mem(get_file_size(fileName));
  load_binary(read_file(fileName), get_file_size(fileName));
  run_binary(get_file_size(fileName));
}
void set_args(char *args[], int length)
{
  char *temp = (char *)0xFFFFF;
  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      temp[(i * 100) + j] = args[i][j];
    }
  }
}
