#include <System/sys_call.h>
#include <Drivers/idt.h>
#include <System/System.h>
#include <System/IO.h>
void sys_call_init()
{
 setup_call_handler();
}
void setup_call_handler()
{
 idt_set_gate(110, call_handler, 0x8E);
}
void sys_call()
{
 char *temp = (char *)0x0;
 int type = (int)temp[82];
 int arg1 = (int)temp[83];
 int arg2 = (int)temp[84];
 int arg3 = (int)temp[85];
 system_handle(type, arg1, arg2, arg3);
}
void call_handler(void)
{
 __asm__("pusha"); // save registers
 sys_call();
 outportb(MASTER_PIC_CMD_PORT, END_OF_INTERRUPT);
 outportb(SLAVE_PIC_CMD_PORT, END_OF_INTERRUPT);
 __asm__("popa");  // restore registers
 __asm__("leave"); // restore stack
 __asm__("iret");  // interrupt return - important
}