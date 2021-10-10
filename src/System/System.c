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
