#include<Drivers/Screen.h>
#include<Graphics/Graphics.h>
#include<Util/string.h>
#include<System/IO.h>
char * screen = (char *)0xFFFFFFF;
void makeWindow(char * window_name){
  for(int i = 0;i<160*25;i++){
    screen[i]=Screen->vga[i];
  }
 clearScreen();
 for(int i = 0;i<80;i++){printChar(' ',0x1f);setCharAt(i,24,' ',0x1f);}
 for(int i = 0;i<25;i++){
   setCharAt(0,i,' ',0x1f);
   setCharAt(79,i,' ',0x1f);
 }
 printCenter(0,window_name,0x1f);
 Screen->cursorX=2;
 Screen->cursorY=1;
 printAt(0,24," Press ESC to exit",0x1f);
}
void printStringInWindow(char * text){
 for(int i = 0;i<length(text);i++){
  if(Screen->cursorX%160==0){
   Screen->cursorX+=2;
  }
  if(Screen->cursorX%158==0){
   Screen->cursorX+=4;                            
  }
  printC(text[i]);
 }
}
void start_window_system(){
  int running = 1;
  while(running)
  if(inportb(0x60)==0x01)running=0;
  for(int i = 0;i<160*25;i+=2){Screen->vga[i]=0;}
  clearScreen();
}
void clearWindow(){
 for(int i = 160;i<1840;i+=2){
   Screen->vga[i]=0;
 }
 Screen->cursorX=2;
 Screen->cursorY=1;
}