asm(".org 0x100");
asm("jmp kmain");
typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;
uint8 inportb(uint16 _port);
void outportb(uint16 _port, uint8 _data);

void cli();
uint8 inportb(uint16 _port)
{
   uint8 rv;
   __asm__ __volatile__("inb %1, %0"
                        : "=a"(rv)
                        : "dN"(_port));
   return rv;
}

void outportb(uint16 _port, uint8 _data)
{
   __asm__ __volatile__("outb %1, %0"
                        :
                        : "dN"(_port), "a"(_data));
}
void cli()
{
   __asm__("cli");
}
struct sc
{
  int cursorX;
  int cursorY;
  int defaultColor;
  char *vga;
};
static struct sc *Screen = (struct sc *)0xAA;;
void screen_init();
void clearScreen();
void printChar(char ch, int color);
void print(const char *str, int color);
void printW(const char *str);
void setScreenColor(int color);
void setDefaultColor(int color);
void setCursorPosition(int xe, int ye);
void backspace();
void printC(char a);
void clearFullScreen();
void printChar(char ch,int color){
  if(ch=='\b'){backspace();return;}
  if(Screen->cursorY>=24){scroll();}
  if(ch=='\n'||Screen->cursorX==160){
   Screen->cursorY++;
   Screen->cursorX = 0;
  }
  if(ch!='\n'){
   Screen->vga[(Screen->cursorY*160)+Screen->cursorX]=ch;
   Screen->vga[(Screen->cursorY*160)+Screen->cursorX+1]=color;
   Screen->cursorX+=2;
  }
  setCursorPosition(Screen->cursorX,Screen->cursorY);
}
void setCursorPosition(int xe,int ye){
    unsigned temp;
    temp = ye * 80 + (xe/2);                                                      
    outportb(0x3D4, 14);                                                                
    outportb(0x3D5, temp >> 8);                                                         
    outportb(0x3D4, 15);                                                                
    outportb(0x3D5, temp);        
}
void printC(char a){
  printChar(a,Screen->defaultColor);
}
void print(const char * str,int color){
  for(int i = 0;str[i]!=0;i++){
   printChar(str[i],color);
  }
  setCursorPosition(Screen->cursorX,Screen->cursorY);
}
void printW(const char * str){
    print(str,Screen->defaultColor);
    setCursorPosition(Screen->cursorX,Screen->cursorY);
}
void clearScreen(){
 Screen->cursorX = 0;
 Screen->cursorY = 0;
 for(int i = 0;i<160*25;i+=2){
  Screen->vga[i]=0;
 }                     
}

void screen_init(){
  Screen->vga = (char *) 0xB8000;
  Screen->cursorX = 0;
  Screen->cursorY = 0;
  Screen->defaultColor = 0x07;
}
void setDefaultColor(int color){
 Screen->defaultColor = color;
}
void clearLine(int line){
    for(int i = 0;i<160;i++){
        Screen->vga[(160*line)+i]=0;
    }
}
void setScreenColor(int color){
  setDefaultColor(color);
  char * vga = (char *) 0xB8000;
  for(int i = 1;i<160*26;i+=2){
      vga[i] = (color-(color%16))+(vga[i]%16);
  }
}
void scroll(){
    char * * lines;
    for(int i = 1;i<Screen->cursorY+1;i++){
        for(int j = 0;j<160;j++){
            Screen->vga[(160*(i-1))+j] = Screen->vga[(160*i)+j];
        }
    }
    clearLine(Screen->cursorY);
    Screen->cursorY--;
}
void backspace(){
  if(Screen->cursorX!=0)Screen->cursorX-=2;
  else{Screen->cursorX=160;Screen->cursorY--;}
  Screen->vga[(Screen->cursorY*160)+Screen->cursorX]=0;
  setCursorPosition(Screen->cursorX,Screen->cursorY);
}
void clearFullScreen(){
   Screen->cursorX = 0;
 Screen->cursorY = 0;
  for (int i = 0; i < 25*160; i+=2){
    Screen->vga[i]   = 0;
    Screen->vga[i+1] = Screen->defaultColor;
  }
}
void kmain(){
 screen_init();
 clearScreen();
 printW("Hello\nBruh");
 return;
}