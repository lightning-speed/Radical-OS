#include<Drivers/Screen.h>

int length(char * in);
void setDefaultScreenColor(int color);
void setCharAt(int xex,int ye,char ae,int color){
    int xe = xex*2;
    char * vga = (char *) 0xB8000;
    vga[(ye*160)+xe]=ae;
    vga[(ye*160)+xe+1]=color;
}
void printAt(int xe,int ye,char * tex,int color){
 for(int i = 0;i<length(tex);i++){
    setCharAt(xe+i,ye,tex[i],color);
 }
}
void printCenter(int ye,char * text,int color){
  printAt(40-(length(text)/2),ye,text,color);
}
void setBlockAt(int x,int y,int color){
  Screen->vga[(y*160)+(x*4)]=219;
  Screen->vga[(y*160)+(x*4)+1]=color;
  Screen->vga[(y*160)+(x*4)+2]=219;
  Screen->vga[(y*160)+(x*4)+3]=color;

}