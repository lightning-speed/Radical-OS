#include "Terminal-Runtime.h"
#include <Util/string.h>
#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <FS/fs.h>
#include <Mego-Runtime/Runtime.h>
#include <System/System.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <System/MemoryManager.h>
void calc_init();
void edit_file();
void ImageViewr_init(char *fn);
int runSh(char *fn)
{
  if (fn[length(fn) - 1] == 'h' && fn[length(fn) - 2] == 's')
  {
    char *ft = (char *)malloc(length(readFile(fn)) + 5);
    //for (int i = 0; i < length(readFile(fn)); i++)
    // ft[i] = readFile(fn)[i];
    set((int *)ft, (int *)readFile(fn));
    char *command = malloc(50);
    if (ft[length(ft) - 1] != '\n')
      addChar(ft, '\n');
    int tempy = 0;
    for (int i = 0; ft[i] != 0; i++)
    {
      if (ft[i] == '\n')
      {
        system(command);
        for (int j = 0; j < 50; j++)
          command[j] = 0;
        tempy = 0;
      }
      else
      {
        command[tempy] = ft[i];
        command[tempy + 1] = 0;
        tempy++;
      }
    }
    roll_back(50 + length(readFile(fn)) + 5);
    return 1;
  }
  return 0;
}
int runFile(char *in)
{
  if (readFile(in)[0] != 0)
  {
    printC('\n');
    int *pro = (int *)malloc(length(readFile(in)));
    for (int i = 0; i < length(readFile(in)); i++)
    {
      pro[i] = readFile(in)[i];
    }
    execute_program((int *)pro);
    roll_back(length(readFile(in)));
    return 1;
  }
  return 0;
}
void compile();
void system(char *command)
{
  setDefaultColor(0x0b);
  if (0)
  {
  }
  else if (equalS(command, "rename", 6))
  {
    int dif = 0;
    for (int i = 7; i < 40; i++)
    {
      if (command[i] == ' ')
      {
        dif = i - 1;
        break;
      }
    }
    char *to_name = malloc(32);
    char *fn = malloc(32);
    set((int *)fn, (int *)substring(command, 7, dif + 1));
    set((int *)to_name, (int *)substring(command, dif + 2, length(command)));
    if (doesFileExists(to_name))
    {
      printW("\nFile Already Exists");
      return;
    }
    rename(fn, to_name);
  }
  else if (equalS(command, "cls", 3) || equalS(command, "clear", 4))
  {
    clearScreen();
    setScreenColor(0x0f);
  }
  else if (equalS(command, "mex", 3))
  {
    if (doesFileExists(substring(command, 4, length(command))))
    {
      char *in = malloc(4096);
      set((int *)in, (int *)readFile(substring(command, 4, length(command))));
      compile(in);
      roll_back(4096);
    }
    else
      printW("\nInput File doesn't exists");
  }
  else if (equalS("edit", command, 4))
  {
    edit_file(substring(command, 5, length(command)));
  }
  else if (equalS(command, "echo", 4))
  {
    printC('\n');
    for (int i = 5; command[i] != 0; i++)
    {
      printC(command[i]);
    }
  }
  else if (equalS(command, "mk", 2))
  {
    if (command[3] == 0)
    {
      printW("\ncannot make a file with empty file name");
    }
    else if (!doesFileExists(substring(command, 3, 38)))
    {
      createFile(substring(command, 3, 38));
      writeFile(substring(command, 3, 38), "\0\0\0\0\0");
    }
    else
    {
      printW("\nFile already exists");
    }
  }
  else if (equalS(command, "readf", 5))
  {
    if (doesFileExists(substring(command, 6, 38)))
    {
      makeWindow(substring(command, 6, 38));
      printStringInWindow(readFile(substring(command, 6, 38)));
      start_window_system();
    }
    else
    {
      printW("\nFile does not exists");
    }
  }
  else if (equalS(command, "mem", 3))
  {
    printC('\n');
    printW(toString(getMemPointer() - 0xFFFFAA));
  }
  else if (equalS(command, "del", 3))
  {
    if (doesFileExists(substring(command, 4, 36)))
    {
      deleteFile(substring(command, 4, 36));
    }
    else
    {
      printW("\nFile does not exists");
    }
  }
  else if ((doesFileExists(command) && runSh(command)))
  {
  }
  else if (command[0] != 0 && doesFileExists(command) && command[length(command) - 1] == 'x' && command[length(command) - 2] == 'e')
  {
    runFile(command);
  }
  else if (equal(command, "ls"))
  {
    for (int i = 0; i < total_files(); i++)
    {
      printC('\n');
      printW(getFileNameAt(i));
      for (int j = 0; j < 20 - length(getFileNameAt(i)); j++)
      {
        printC(' ');
      }
      printW(toString(length(getFileContentAt(i))));
      printW(" Bytes");
    }
  }
  else if (equalS(command, "ascii", 5))
  {
    printC('\n');
    for (int i = 0; i < 255; i++)
    {
      printW(toString(i));
      printW(" ");
      printC(i);
      printW(" ");
    }
  }
  else if (equalS(command, "colors", 6))
  {
    printC('\n');
    for (int i = 0; i < 16; i++)
    {
      printChar(219, i);
    }
  }
  else if (equalS(command, "copy", 4))
  {
    char *in = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    char *des = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    int f = 5;
    int sec = 0;
    for (int i = 5; command[i] != ' ' && command[i] != 0; i++)
      f++;
    set((int *)in, (int *)substring(command, 5, f));
    sec = f + 1;
    set((int *)des, (int *)substring(command, sec, length(command)));
    if (!doesFileExists(in))
    {
      printW("\nInput file doesn't exists");
      return;
    }
    if (doesFileExists(des))
    {
      printW("\nOutput file already exists");
      return;
    }
    copyFile(in, des);
  }
  else if (equalS(command, "restart", 7))
  {
    restart();
  }
  else if (equalS(command, "shutdown", 8))
  {
    shutdown();
  }
  else if (equalS(command, "read", 4))
  {
    printW("\nPress Any key to continue...");
    readChar();
  }
  else if (equalS(command, "help", 4))
  {
    printW("\nRadical Kernel Version 3.2.0");
    printW("\nKernel Build: 1721");
    printW("\nCommands are:-\n");
    printW("cls\n");
    printW("echo\n");
    printW("mk\n");
    printW("del\n");
    printW("copy\n");
    printW("ls\n");
    printW("rename\n");
    printW("readf\n");
    printW("restart\n");
    printW("shutdown\n");
    printW("colors\n");
    printW("ascii\n");
    printW("time\n");
    printW("calc\n");
    printW("view\n");
    printW("mex\n");
  }
  else if (equalS(command, "calc", 4))
  {
    calc_init();
  }
  else if (equalS(command, "view", 4))
  {
    if (doesFileExists(substring(command, 5, length(command))))
      ImageViewr_init(substring(command, 5, length(command)));
    else
      printW("\nFile dosen't exists");
  }
  else if (equalS("time", command, 4))
  {
    printW("\nCurrent BIOS time is: ");
    printW(toString(getHours()));
    printC(':');
    printW(toString(getMinutes()));
    printC(':');
    printW(toString(getSeconds()));
  }

  else if (command[0] != 0)
  {
    printW("\n'");
    printW(command);
    printW("'");
    printW(" is not recognized as an internal or external command,\noperable program or batch file.");
  }
  for (int i = 0; i < 100; i++)
    command[i] = 0;
  setDefaultColor(0x0f);
}