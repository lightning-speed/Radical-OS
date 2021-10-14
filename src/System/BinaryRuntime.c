#include "BinaryRuntime.h"
#include <FS/vfs.h>
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
void set_binary_location(int to)
{
  binary_mem = (char *)to;
}
void run_binary_file(char *fileName)
{
  clear_binary_mem(get_file_size(fileName));
  load_binary(read_file(fileName), get_file_size(fileName));
  run_binary();
}