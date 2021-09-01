#include"Memory.h"
int last_index = 0xFFFFF8;
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