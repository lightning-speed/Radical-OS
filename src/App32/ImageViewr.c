#include<Util/string.h>
#include<Drivers/Screen.h>
#include<Drivers/Keyboard.h>
#include<Graphics/Image.h>
#include<System/MemoryManager.h>
#include<Graphics/Graphics.h>
#include<FS/fs.h>
char * ftv;
void ImageViewr_pre(){
 ftv = new_str(109);
}
void ImageViewr_init(char * fn){
 for(int i = 0;i<108;i++){
  ftv[i]=0;
 }
 makeWindow("Image Viewr");
 set((int *)ftv,(int *)readFile(fn));
 drawImage(40-ftv[0],12-ftv[1],ftv);     
 start_window_system(); 
}