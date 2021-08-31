#include<Drivers/Screen.h>
typedef int * Image;
int he,we;
void drawImage(int xe,int ye,int * img){
      we = img[0];
      he = img[1];
      int temp = 2;
      xe*=2;
      for(int i = 0;i<he;i++){
          for(int j = 0;j<we*4;j+=4){
            Screen->vga[(160*(i+ye))+j+xe]=219;
            Screen->vga[(160*(i+ye))+j+1+xe]=img[temp]/16;
            Screen->vga[(160*(i+ye))+j+2+xe]=219;
            Screen->vga[(160*(i+ye))+j+3+xe]=img[temp]/16;
            temp++;
          }
      }
}