#include "shell.h"
#include<Drivers/Screen.h>
#include<System/SystemTime.h>
#include<Util/string.h>
#include<Drivers/Keyboard.h>
#include<Terminal-Runtime/Terminal-Runtime.h>
#include<FS/fs.h>
#include<Drivers/isr.h>
#include<Drivers/idt.h>
void ImageViewr_pre();
void memory_init();

void shell_main(){
  for(int i = 0;i<2000;i++)
  Screen->vga[i]=0;
  setScreenColor(0x1f);
  printW("Radical OS [Version 2.0.0]\n");
  printW("Copyright (c) 2021 Radical Foundation.  All rights reserved.\n\n");
  printW("Welcome to Radical OS. Hope you have fun :)\n\n");
  printW("Setting up Memory Manager...    ");
  memory_init();
  print("[ done ]\n\n",0x1a);
  printW("Setting up VFS...               ");
  fs_init();
  print("[ done ]\n\n",0x1a);
  printW("Time from boot: ");
  printW(toString(getTimeFromBoot()));
  printC('\n');
  start_shell();
}
void start_shell(){
  ImageViewr_pre();
  isr_install();
  char * temp = 0x0;
  for(int i =0;i<1000000;i++){
    if(temp[i]=='w'&&temp[i+1]=='e'&&temp[i+2]=='0'){
      printC(temp[i+3]);
      break;
    }
  }
  while(1){
    print("\nRADICAL>> ",0x1c);
    system(input());
  }
}