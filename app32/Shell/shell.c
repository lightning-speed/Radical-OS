asm("jmp _pmain");
void pmain(){
 char * temp = (char *)0x0;
 temp[82]= 1;
 temp[83]='H';
 temp[84]=0x1f;
 asm("int $110");
 for(;;){}
}