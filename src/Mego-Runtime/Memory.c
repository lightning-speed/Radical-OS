#include<Mego-Runtime/Runtime.h>
int AA = 0;
int AB = 0;
int AC = 0;
int AD = 0;
int AE = 0;
int AF = 0;
int AG = 0;
int AH = 0;
int AI = 0;
int AJ = 0;
int AK = 0;
int AL = 0;
int * virtual_memory  = (int *)0xFF;
int stack_pointer = 0;

void mem_init(){
 AA = 0;
 AB = 0;
 AC = 0;
 AD = 0;
 AE = 0;
 AF = 0;
 AH = 0;
 AI = 0;
 AJ = 0;
 AK = 0;
 AL = 0;
}
void setRegValueOf(int in,int value){
 if(in==1)AA = value;
 if(in==2)AB = value;
 if(in==3)AC = value;
 if(in==4)AD = value;
 if(in==5)AE = value;
 if(in==6)AF = value;
 if(in==7)AG = value;
 if(in==8)AH = value;
 if(in==9)AI = value;
 if(in==10)AJ = value;
 if(in==11)AK = value;
 if(in==12)AL = value;
}
int getRegValueOf(int in){
 if(in==1)return AA;
 if(in==2)return AB;
 if(in==3)return AC;
 if(in==4)return AD;
 if(in==5)return AE;
 if(in==6)return AF;
 if(in==7)return AG;
 if(in==8)return AH;
 if(in==9)return AI;
 if(in==10)return AJ;
 if(in==11)return AK;
 if(in==12)return AL;
 else return 0;
}
void push(int in){
  virtual_memory[stack_pointer] = in;
  stack_pointer++;
}
int pop(){
 int out = virtual_memory[0];
 for(int i = 0;i<stack_pointer;i++){
   virtual_memory[i]=virtual_memory[i+1];
 }
 stack_pointer--;
 return out;
}
void setMemoryAt(int in,int mem){
  virtual_memory[in] = mem;
}
int getMemoryAt(int in){
 return virtual_memory[in];
}