char * process(char * in);
#include<Drivers/Screen.h>
#include<System/SystemTime.h>
#include<Util/string.h>
#include<Drivers/Keyboard.h>
#include<System/MemoryManager.h>
#include<FS/fs.h>
void compile(char * text){
 char * command = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 char * total = new_str(216);
 int temp = 0;
 for(int i = 0;i<length(text);i++){
   if(text[i]=='\n'){
     total = join(total,process(command));
     temp = 0;
     command[0]=0;
   }
   else{
    command[temp]=text[i];
    command[temp+1]=0;
    temp++;
   }
 }
 total = join(total,"\r\0");
 if(!doesFileExists("out.mex"))
 createFile("out.mex");
 writeFile("out.mex",total);
}
char * process(char * in){
 char * out = "\0\0\0\e\0";
 if(equalS(in,"movn",4))out[0]=30;
 if(equalS(in,"movr",4))out[0]=31;
 if(equalS(in,"push",4))out[0]=32;
 if(equalS(in,"popr",4))out[0]=33;
 if(equalS(in,"cmdn",4))out[0]=34;
 if(equalS(in,"addn",4))out[0]=35;
 if(equalS(in,"addr",4))out[0]=36;
 if(equalS(in,"subn",4))out[0]=37;
 if(equalS(in,"subr",4))out[0]=38;
 if(equalS(in,"jump",4))out[0]=39;
 if(equalS(in,"jnzn",4))out[0]=40;
 if(equalS(in,"smal",4))out[0]=41;
 if(equalS(in,"bign",4))out[0]=42;
 if(equalS(in,"equn",4))out[0]=43;
 if(equalS(in,"inbn",4))out[0]=44;
 if(equalS(in,"outb",4))out[0]=45;
 int sp = 0;
 for(int i = 5;i<length(in);i++)if(in[i]==' ')sp = i;
 char * arg1 = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 set((int *)arg1,(int *)substring(in,5,sp));
 char * arg2 = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
 set((int *)arg2,(int *)substring(in,sp+1,length(in))); 
 if(arg1[0]<='9'&&arg1[0]>='0')out[1]=(char)parseInt(arg1);
 else if(arg1[0]=="'"[0])out[1]=arg1[1];
 else{
    if(equalS(arg1,"aa",2))out[1]=1;
    else if(equalS(arg1,"ab",2))out[1]=2;
    else if(equalS(arg1,"ac",2))out[1]=3;
    else if(equalS(arg1,"ad",2))out[1]=4;
    else if(equalS(arg1,"ae",2))out[1]=5;
    else if(equalS(arg1,"af",2))out[1]=6;
    else if(equalS(arg1,"ag",2))out[1]=7;
    else if(equalS(arg1,"ah",2))out[1]=8;
    else if(equalS(arg1,"ai",2))out[1]=9;
    else if(equalS(arg1,"aj",2))out[1]=10;
    else if(equalS(arg1,"ak",2))out[1]=11;
    else if(equalS(arg1,"al",2))out[1]=12;
 }
 if(arg2[0]<='9'&&arg2[0]>='0')out[2]=(char)parseInt(arg2);
 else if(arg2[0]=="'"[0])out[2]=arg2[1];
 else{
    if(equalS(arg2,"aa",2))out[2]=1;
    else if(equalS(arg2,"ab",2))out[2]=2;
    else if(equalS(arg2,"ac",2))out[2]=3;
    else if(equalS(arg2,"ad",2))out[2]=4;
    else if(equalS(arg2,"ae",2))out[2]=5;
    else if(equalS(arg2,"af",2))out[2]=6;
    else if(equalS(arg2,"ag",2))out[2]=7;
    else if(equalS(arg2,"ah",2))out[2]=8;
    else if(equalS(arg2,"ai",2))out[2]=9;
    else if(equalS(arg2,"aj",2))out[2]=10;
    else if(equalS(arg2,"ak",2))out[2]=11;
    else if(equalS(arg2,"al",2))out[2]=12;
 }
 out[3]='\e';
 return out;
}