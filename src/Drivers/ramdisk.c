#include "ramdisk.h"
#include <FS/vfs.h>
#include <System/MemoryManager.h>
#include <Util/string.h>
long long ramdisk_location = 0;
int r_length = 0;
char *ramdisk = (char *)0X0;
long long detectRamdiskLocation()
{
 char *temp = (char *)0x0;
 long long out = 0;
 for (long long i = 0;; i++)
 {
  if (temp[i] == '{' && temp[i + 1] == '-' && temp[i + 2] == '!' && temp[i + 3] == ']')
  {
   out = i + 4;
   break;
  }
 }
 ramdisk_location = out;
 return out;
}
long long detectRamdiskLength()
{
 char *temp = (char *)0x0;
 long long out;
 for (long long i = ramdisk_location;; i++)
 {
  if (temp[i] == '{' && temp[i + 1] == '+' && temp[i + 2] == '!' && temp[i + 3] == ']')
  {
   out = i - ramdisk_location;
   break;
  }
 }
 r_length = out;
 return out;
}
void load_ramdisk()
{
 ramdisk = (char *)0x0 + detectRamdiskLocation();
}
char *get_ramdisk()
{
 return ramdisk;
}
char *fileNames[1] = {"shell.bin"};
void rn()
{
 for (int i = 0; i < fileNames[i][0] != 0; i++)
 {
  rename_file(toString(i + 1), fileNames[i]);
 }
}
void create_files_from_ramdisk()
{
 char *temp_c = (char *)malloc(20480);
 int temp_l = 0;
 int ap = 0;
 for (long long i = 0; i < r_length; i++)
 {
  if (ramdisk[i] == '@' && ramdisk[i + 1] == '>' && ramdisk[i + 2] == '<')
  {
   ap++;
   create_file(toString(ap), temp_c, temp_l);
   temp_l = 0;
   i += 2;
  }
  else
  {
   temp_c[temp_l] = ramdisk[i];
   temp_l++;
  }
 }
 roll_back(20480);
 rn();
}
