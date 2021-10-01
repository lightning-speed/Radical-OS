#include <Util/string.h>
#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <FS/fs.h>
#include <Mego-Runtime/Runtime.h>
#include <System/System.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <System/MemoryManager.h>
char *fileText;
int *vars;
void run();
void execute(char *command);
int run_gemo_file(char *fileName)
{
 vars = (int *)malloc(30);
 fileText = malloc(4096);
 set((int *)fileText, (int *)readFile(fileName));
 run();
}
void run()
{
 int temp = 0;
 char *command = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 for (int i = 0; i < 60; i++)
 {
  if (fileText[i] == '\n')
  {
   execute(command);
   temp = 0;
   command[0] = 0;
  }
  else
  {
   command[temp] = fileText[i];
   command[temp + 1] = 0;
   temp++;
  }
 }
}
void execute(char *commandIN)
{
}
