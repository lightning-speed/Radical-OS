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
 char type = (char)temp[82];
 char arg1 = (char)temp[83];
 char arg2 = (char)temp[84];
 char arg3 = (char)temp[85];
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