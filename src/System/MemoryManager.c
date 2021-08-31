#include"Memory.h"
int last_index = 0xFFFFF;
char * new_str(int len){
 last_index+=len;
 return (char *)last_index;
}
void move_mem(int from,int to,int till){
 char * from_c = (char *)0x0+from;
 char * to_c  = (char *)0x0+to;
 for(int i = 0;i<till;i++){
  from_c[i]=to_c[i];
 }
}