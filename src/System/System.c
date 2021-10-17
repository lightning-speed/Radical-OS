#include "System.h"
#include <Drivers/Screen.h>
#include <System/IO.h>
#include <Graphics/Graphics.h>
#include <Drivers/Keyboard.h>
#include <util/string.h>
#include <FS/vfs.h>
#include <System/SystemTime.h>
#include <System/BinaryRuntime.h>
#include <System/MemoryManager.h>
const int io_adrress = 0xA00000;
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
int run_file_c(char *line)
{
     char *args[10];
     split_to_args(args, line, ' ', 10);
     if (does_file_exists(args[0]))
     {
          set_args(args, 10);
          roll_back(10 * 100);
          run_binary_file(args[0]);
          return 1;
     }
     return 0;
}
void system(char *line)
{
     if (line[0] == 0 || line[0] == '\b')
     {
          return;
     }
     if (equalS(line, "cls", 3))
     {
          clearScreen();
     }
     else if (equalS(line, "echo", 4))
     {
          printC('\n');
          printW(substring(line, 5, length(line)));
     }
     else if (equalS("time", line, 4))
     {
          printW("\nCurrent BIOS time is: ");
          printW(toString(getHours()));
          printC(':');
          printW(toString(getMinutes()));
          printC(':');
          printW(toString(getSeconds()));
     }
     else if (equalS("ls", line, 2))
     {
          for (int i = 0; i < f_index; i++)
          {
               printC('\n');
               printW(get_file_name_at(i));
               printW("    ");
               printW(toString(get_file_size_at(i)));
               printW(" Bytes");
          }
     }
     else if (run_file_c(line) == 1)
     {
     }
     else
     {
          print("\nerror: ", 0x04);
          printW("invalid command ");
     }
     for (int i = 0; i < 1000; i++)
     {
          line[i] = 0;
     }
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
     if (type == 5)
     {
          system((char *)io_adrress);
     }
}