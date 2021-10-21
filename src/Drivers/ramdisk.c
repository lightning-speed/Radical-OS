#include <System/MemoryManager.h>
#include <Drivers/ramdisk.h>
void load_ramdisk()

{
 char *mem = (char *)0x0;
 for (long long i = 0;; i++)
 {
  if (mem[i] == '{' && mem[i + 1] == '-' && mem[i + 2] == '3' && mem[i + 3] == ']')
  {
   ramdisk_start = i + 4;
   for (long long j = 0;; j++)
   {
    if (mem[ramdisk_start + j] == '{' && mem[ramdisk_start + 1 + j] == '+' && mem[ramdisk_start + 2 + j] == '3' && mem[ramdisk_start + 3 + j] == ']')
    {
     ramdisk_end = ramdisk_start + (j - 1);
     break;
    }
   }
   break;
  }
 }
}
