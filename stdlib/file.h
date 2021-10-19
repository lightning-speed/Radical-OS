#pragma once
#include "stdio.h"
char *read_file(char name[])
{
 setAll(10, 0, 0, 0);
 char *memu = (char *)io_adrress;
 for (int i = 0; i < name[i] != 0; i++)
 {
		memu[i] = name[i];
		memu[i + 1] = 0;
 }
 asm("int $110");
 return (char *)io_adrress;
}
int does_file_exists(char name[])
{
 setAll(11, 0, 0, 0);
 char *memu = (char *)io_adrress;
 for (int i = 0; i < name[i] != 0; i++)
 {
		memu[i] = name[i];
		memu[i + 1] = 0;
 }
 asm("int $110");
 return memu[0];
}