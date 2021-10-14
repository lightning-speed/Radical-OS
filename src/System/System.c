#include "System.h"
#include <Drivers/Screen.h>
#include <System/IO.h>
#include <Graphics/Graphics.h>
#include <Drivers/Keyboard.h>
void restart()
{
     uint8 good = 0x02;
     while (good & 0x02)
          good = inportb(0x64);
     outportb(0x64, 0xFE);
}
void shutdown()
{
}
void system_handle(char type, char arg1, char arg2, char arg3)
{
     char *mem = (char *)0x0;
     //IO
     //Set Color
     if (type == 0)
          Screen->defaultColor = arg1;
     //Print Char
     if (type == 1)
          printC(arg1);
     //Set Cursor Position
     if (type == 2)
     {
          Screen->cursorX = arg1;
          Screen->cursorY = arg2;
     }
     if (type == 3)
          mem[83] = readChar();
     if (type == 4)
          mem[83] = Screen->cursorX;
}