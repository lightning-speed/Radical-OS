#include"Terminal-Runtime.h"
#include<Util/string.h>
#include<Drivers/Screen.h>
#include<FS/fs.h>
#include<Mego-Runtime/Runtime.h>
#include<System/System.h>
int runFile(char * in){
   if(readFile(in)[0]!=0){
    printC('\n');
    int * pro = (int *)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    for(int i = 0;i<length(readFile(in));i++){
      pro[i]=readFile(in)[i];
    }
    execute_program((int *)pro);
    return 1;
   }
   return 0;
}

void system(char * command){
  if(equalS(command,"cls",3)||equalS(command,"clear",4)){
   clearScreen();
  }
  else if(equalS(command,"echo",4)){
   printC('\n');
   for(int i = 5;command[i]!=0;i++){
      printC(command[i]);
   }
  }
  else if(equalS(command,"mk",2)){
    if(!doesFileExists(substring(command,3,38))){
    createFile(substring(command,3,38));
    writeFile(substring(command,3,38),"\0\0\0\0\0");
    }
    else{
      printW("\nFile already exists");
    }
  }
  else if(command[0]!=0&&doesFileExists(command)){
    runFile(command);
  }
  else if(equalS(command,"ls",2)){
   for(int i = 0;i<total_files();i++){
     printC('\n');
     printW(getFileNameAt(i));
     printW("     ");
     printW(toString(length(getFileContentAt(i))));
     printW(" Bytes");
   }
  }
  else if(equalS(command,"readf",5)){
   if(doesFileExists(substring(command,6,38))){
    printC('\n');
    printW(readFile(substring(command,6,38)));
   }else{
     printW("\nFile does not exists");
   }
  }
  else if(equalS(command,"ascii",5)){
    printC('\n');
    for(int i = 0;i<255;i++){
      printW(toString(i));
      printW(" ");
      printC(i);
      printW(" ");
    }
  }
  else if(equalS(command,"colors",6)){
    printC('\n');
    for(int i = 0;i<16;i++){
      printChar(219,i);
    }
  }
  else if(equalS(command,"copy",4)){
   char * in="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   char * des="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   int f = 5;
   int sec = 0;
   for(int i = 5;command[i]!=' '&&command[i]!=0;i++)f++;
   set((int *)in,(int *)substring(command,5,f));
   sec=f+1;
   set((int *)des,(int *)substring(command,sec,length(command)));
   copyFile(in,des);
  }
  else if(equalS(command,"restart",7)){
    restart();
  }
  else if(equalS(command,"shutdown",8)){
    shutdown();
  }
  else if(command[0]!=0){
     printW("\n'");
     printW(command);
     printW("'");
     printW(" is not recognized as an internal or external command,\noperable program or batch file.");
  }
  for(int i = 0;i<100;i++)command[i]=0;
}