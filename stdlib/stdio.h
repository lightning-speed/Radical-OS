#pragma once
#include <util_string.h>
char *mem = (char *)0x0;
void setAll(char type, char arg1, char arg2, char arg3);
void printChar(char in)
{
 setAll(1, in, 0, 0);
 asm("int $110");
}
char readChar()
{
 mem[82] = 3;
 asm("int $110");
 return mem[83];
}
void changeColor(char color)
{
 setAll(0, color, 0, 0);
 asm("int $110");
}
void changeCursorPosition(char x, char y)
{
 setAll(2, x, y, 0);
 asm("int $110");
}
int getX()
{
 setAll(4, 0, 0, 0);
 asm("int $110");
 return mem[83];
}
void setAll(char type, char arg1, char arg2, char arg3)
{
 mem[82] = type;
 mem[83] = arg1;
 mem[84] = arg2;
 mem[85] = arg3;
}
void printS(char str[])
{
 for (int i = 0; i < length(str); i++)
 {
  setAll(1, str[i], 0, 0);
  asm("int $110");
 }
}
char *input()
{
 char tp = 0;
 char *out = "";
 int index = 0;
 while ((tp = readChar()) != '\n')
 {
  out[index] = tp;
  out[index + 1] = 0;
  if (out[index] == '\b')
  {
   if (index > 0)
   {
    out[index] = 0;
    out[index - 1] = 0;
    printChar('\b');
    index -= 1;
   }
  }
  else
  {
   printChar(tp);
   index++;
  }
 }
 return out;
}
