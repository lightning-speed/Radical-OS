#include "shell.h"
#include <Drivers/Screen.h>
#include <System/SystemTime.h>
#include <Util/string.h>
#include <Drivers/Keyboard.h>
#include <Terminal-Runtime/Terminal-Runtime.h>
#include <FS/vfs.h>
#include <System/MemoryManager.h>
#include <Drivers/ramdisk.h>
#include <System/BinaryRuntime.h>

void ImageViewr_pre();
void memory_init();

void shell_main()
{
  for (int i = 0; i < 2000; i++)
    Screen->vga[i] = 0;
  for (int i = 1; i < 2000; i += 2)
  {
    Screen->vga[i] = 0x1f;
  }
  setScreenColor(0x0f);
  memory_init();
  init_fs();
  start_shell();
}
void start_shell()
{
  ImageViewr_pre();
  printW("\nBuilding Some MEX Files");
  printC('\n');
  while (1)
  {
    print("\nRADICAL>> ", 0x0c);
    setDefaultColor(0x02);
    system(input());
    setDefaultColor(0x0f);
    removeCache();
  }
}