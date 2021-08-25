#include"Runtime.h"
#include<Drivers/Screen.h>
void execute_command(int command){
  if(command==0x1){
    printC(getRegValueOf(3));
  }
}