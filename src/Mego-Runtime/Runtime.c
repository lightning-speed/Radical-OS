#include "Runtime.h"
int cpu_pointer = 0;
void run_block(int *block)
{
  int *instruction = (int *)"\0\0\0\0";
  int temp = 0;
  for (cpu_pointer = 0; block[cpu_pointer] != 0; cpu_pointer++)
  {
    if (block[cpu_pointer] != '\e' && temp < 3)
    {
      instruction[temp] = block[cpu_pointer];
      temp++;
    }
    else
    {
      run_instruction(instruction);
      temp = 0;
      instruction = (int *)"\0\0\0\0";
    }
  }
}
void setMemory(int *mem)
{
  for (int i = 0; mem[i] != 0; i++)
    setMemoryAt(i + 50, mem[i]);
}
void setCpuPointer(int in)
{
  cpu_pointer = (in * 2) - 3;
}
void execute_program(int *program)
{
  mem_init();
  int *program_block = (int *)0xFFFF;
  int *mem = (int *)0xAAAA;
  for (int i = 0; i < 1000; i++)
  {
    mem[i] = 0;
    program_block[i] = 0;
  }
  int tempy = 0;
  for (int i = 0; program[i] != '\r' && program[i] != 0; i++)
  {
    program_block[i] = program[i];
    tempy = i + 2;
  }
  for (int i = tempy; program[i] != 0; i++)
  {
    mem[i - tempy] = program[i];
  }
  setMemory(mem);
  run_block(program_block);
}