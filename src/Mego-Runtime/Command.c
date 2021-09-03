#include"Runtime.h"
#include<Drivers/Screen.h>
#include<Mego-Runtime/Runtime.h>
#include<Drivers/Keyboard.h>
void execute_command(int command){
  if(command==0x1){
    printC(getRegValueOf(3));
  }
  if(command==0x2){
     setRegValueOf(4,readChar());
  }
}