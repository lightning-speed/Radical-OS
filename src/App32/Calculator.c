#include<Util/string.h>
#include<Drivers/Screen.h>
#include<Drivers/Keyboard.h>
void calc_init(){
  printW("\nEnter First Number: ");
  int fn = parseInt(input());
  printW("\nEnter Second Number: ");
  int sn = parseInt(input());
  printW("\nEnter the valid operator: ");
  char ae;
  int runningC = 1;
  while(runningC){
  ae =  readChar();
  if(ae=='+'){
    printC(ae);
    printW("\nOutput: ");
    printW(toString(fn+sn));
    runningC = 0;
  }
  else  if(ae=='-'){
    printC(ae);
    printW("\nOutput: ");
    printW(toString(fn-sn));
    runningC = 0;
  }
  else  if(ae=='/'){
    printC(ae);

    printW("\nOutput: ");
    printW(toString(fn/sn));
    runningC = 0;
  }
  else  if(ae=='*'){
    printC(ae);

    printW("\nOutput: ");
    printW(toString((fn*sn)));
    runningC = 0;
  }
  else if(ae=='%'){
    printC(ae);

    printW("\nOutput: ");
    printW(toString((fn%sn)));
    runningC = 0;

  }
  else{
   printC(ae);
   printW("\nEnter the valid operator: ");
  }
  
  }
}