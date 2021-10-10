asm("jmp _kmain");
void kmain(){
 char * vga = (char *)0XB8000;
 vga[0]='A';
 return;
}