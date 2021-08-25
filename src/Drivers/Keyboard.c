#include"Screen.h"
char * keycode = "\e 1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";
char * keycode2 = "\e !@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:'~\0|ZXCVBNM<>?\0\0\0 ";
int isShift= 0;
#include<System/IO.h>
char readChar(){
   int run = 1;
   char out = 0;
   while(run){
     if(inportb(0x64) & 0x1){
            if(inportb(0x60)==0x2A&&!isShift)isShift=1;
            else if(inportb(0x60)==0xAA&&isShift)isShift=0;
            if(!isShift)
            out = keycode[inportb(0x60)];
            else if(isShift)
            out = keycode2[inportb(0x60)];
            if(out!=0&&inportb(0x60)<60)run=0;
     }
   }
   return out;
}
 char * input(){
  char tp=0;
  char * out="";
  int index = 0;
  while((tp=readChar())!='\n'){
     out[index]=tp;
     out[index+1]=0;
     if(out[index]=='\b'){
       if(index>0){
       out[index]=0;
       out[index-1]=0;
       backspace();
       index-=1;
       }
     }
     else{
     printChar(tp,Screen->defaultColor);
     index++;
     }
  }
  return out;
}
char getChar(){
   if(inportb(0x60)<60&&inportb(0x60)>0&&keycode[inportb(0x60)]>0&&keycode[inportb(0x60)]<254)return keycode[inportb(0x60)];
}