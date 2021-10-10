#include "ramdisk.h"
long long ramdisk_location = 0;
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
 return out;
}