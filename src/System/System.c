#include "System.h"
#include <Drivers/Screen.h>
#include <System/IO.h>
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
void system_handle(int type, int arg1, int arg2, int arg3)
{
     if (type == 1)
          if (arg2 == 0)
               printC(arg1);
          else
               printChar(arg1, arg2);
}