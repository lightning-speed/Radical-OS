#include"fs.h"
#include<Util/string.h>
#include<System/MemoryManager.h>
char * fs;
int fs_index = 0;
int file_index  = 0;
void createNativeFiles();
void fs_init(){
  fs = (char *)new_str(10000);
 createNativeFiles();
}
void createFile(char * fn){
 for(int i = fs_index;i<=fs_index+2048;i++){
  fs[i] = 0;
 }
 for(int i = 0;i<length(fn);i++){
   fs[fs_index+i] = fn[i];  
 }
 fs_index+=2048;
 file_index++;
}
void writeFileAt(int indexF,char * content){
  int loc = indexF*2048;
  for(int i = loc+32;i<loc+32+length(content);i++){
     fs[i]=content[i-(loc+32)];
  }
}
char * getFileNameAt(int indexF){
  char * out = new_str(34); //32-bit name
  int loc = indexF*2048;
  for(int i = 0;i<32;i++){
    out[i]=fs[loc+i];
  }
  return out;
}
char * getFileContentAt(int indexF){
  char * out = new_str(2050);
  int loc = indexF*2048;
  for(int i = 0;i<2000;i++){
    out[i]=fs[loc+i+32];

  }
  return out;
}
char * readFile(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      return getFileContentAt(i);
    }
  }
}
void writeFile(char * name,char * text){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      writeFileAt(i,text);
    }
  }
}
int doesFileExists(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      return 1;
    }
  }
  return 0;
}
int file_size_of(char * name){
  return length(readFile(name));
}
char * getFS(){
  return fs;
}
int total_files(){
  return file_index;
}

void createNativeFiles(){
createFile("hello");
writeFile("hello","movn ac 'H\ncmdn 1 1\nmovn ac 'e\ncmdn 1 1\nmovn ac 'l\ncmdn 1 1\nmovn ac 'l\ncmdn 1 1\nmovn ac 'o\ncmdn 1 1\nmovn ac ',\ncmdn 1 1\nmovn ac 'M\ncmdn 1 1\nmovn ac 'e\ncmdn 1 1\nmovn ac 'x\ncmdn 1 1\n");
createFile("build.sh");
writeFile("build.sh","echo building...\nmex hello\ncopy out.mex hello.mex\ndel out.mex\necho done\n");
}
void copyFile(char * in,char * des){
  createFile(des);
  writeFile(des,readFile(in));
}
void clearFile(char * name){
  for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
     for(int j = 0;j<2000;j++){
         fs[(i*2048)+j+32]=0;
     }
    }
  }
}
void deleteFileAt(int ie){
int loc = ie*2048;
int inr = 0;
for(int i = loc+2048;i<=fs_index;i++){
 fs[loc+inr]=fs[i];
 inr++;
}
fs_index-=2048;
file_index--;
}
void deleteFile(char * name){
for(int i = 0;i<file_index;i++){
    if(equal(name,getFileNameAt(i))){
      deleteFileAt(i);
      return;
    }
    }
}