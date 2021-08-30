#include"Timer.h"
#include<System/SystemTime.h>
void Sleep(int seconds){
  for(int i = 0;i<seconds;i++){
    int temp = getTimeFromBoot();
    while(temp==getTimeFromBoot()){}
  }
}