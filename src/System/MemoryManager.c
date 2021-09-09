#include"Memory.h"
int last_index = 0xFFAA;
char * new_str(int len){
 int out = last_index;
  last_index+=len;
 return (char *)out;
}
void move_mem(int from,int to,int till){
 char * from_c = (char *)0x0+from;
 char * to_c  = (char *)0x0+to;
 for(int i = 0;i<till;i++){
  to_c[i]=from_c[i];
 }
}
void memory_init(){
  last_index = 0xFFFFAA;
  char * tempr = (char *)last_index;
  for(int i = 0;i<1000000;i++){
     tempr[i]=0;
  }
}
void role_back(int to){
  last_index-=to;
}