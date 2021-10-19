#include "Runtime.h"
int tempR = 0;
void run_instruction(int *instruction)
{
  int command = instruction[0];
  int arg1 = instruction[1];
  int agr2 = instruction[2];
  exec_instruction(command, arg1, agr2);
}
int condition = 0;
void exec_instruction(int command, int arg1, int arg2)
{
  if (command == 30)
  {
    //MOV
    setRegValueOf(arg1, arg2);
  }
  if (command == 31)
  {
    //MOVR
    setRegValueOf(arg1, getRegValueOf(arg2));
  }
  if (command == 32)
  {
    //PUSH
    push(arg1);
  }
  if (command == 33)
  {
    //POP
    setRegValueOf(arg1, pop());
  }
  if (command == 34)
  {
    //CMD
    execute_command(arg1);
  }
  if (command == 35)
  {
    //ADD
    setRegValueOf(arg1, getRegValueOf(arg1) + arg2);
  }
  if (command == 36)
  {
    //ADDR
    setRegValueOf(arg1, getRegValueOf(arg1) + getRegValueOf(arg2));
  }
  if (command == 37)
  {
    //SUB
    setRegValueOf(arg1, getRegValueOf(arg1) - arg2);
  }
  if (command == 38)
  {
    //SUBR
    setRegValueOf(arg1, getRegValueOf(arg1) - getRegValueOf(arg2));
  }
  if (command == 39)
  {
    //JUMP
    setCpuPointer(arg1);
  }
  if (command == 40)
  {
    //JNZ
    if (condition)
      setCpuPointer(arg1);
  }
  if (command == 41)
  {
    //SMALL
    if (getRegValueOf(arg1) < arg2)
    {
      condition = 1;
    }
    else
      condition = 0;
  }
  if (command == 42)
  {
    //BIG
    if (getRegValueOf(arg1) > arg2)
    {
      condition = 1;
    }
    else
      condition = 0;
  }
  if (command == 43)
  {
    //EQU
    if (getRegValueOf(arg1) == arg2)
      condition = 1;
    else
      condition = 0;
  }
  if (command == 44)
  {
    //OUTB
    setMemoryAt(getRegValueOf(arg1), getRegValueOf(arg2));
  }
  if (command == 45)
  {
    //INB
    setRegValueOf(arg1, getMemoryAt(getRegValueOf(arg2)));
  }
}