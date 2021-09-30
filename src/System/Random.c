#include"Random.h"
#include<System/SystemTime.h>
int random(){
  return (getSeconds()*getTimeFromBoot()*getSeconds()*getMinutes())*getSeconds();
}