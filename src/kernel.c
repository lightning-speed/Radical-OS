#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <FS/fs.h>
#include <Shell/shell.h>
#include <System/BinaryRuntime.h>
#include <Util/string.h>
#include <Drivers/gdt.h>
#include <Drivers/idt.h>
void printLogo();
void Sleep(int in);
// constants

void init_pic(void)
{ /* Initialization of ICW1 */
  outportb(0x20, 0x11);
  outportb(0xA0, 0x11);                         /* Initialization of ICW2 */
  outportb(0x21, 0x20);                         /* start vector = 32 */
  outportb(0xA1, 0x70); /* start vector = 96 */ /* Initialization of ICW3 */
  outportb(0x21, 0x04);
  outportb(0xA1, 0x02); /* Initialization of ICW4 */
  outportb(0x21, 0x01);
  outportb(0xA1, 0x01); /* mask interrupts */
  outportb(0x21, 0x0);
  outportb(0xA1, 0x0);
}
int kmain()
{
  time_init();
  screen_init();
  clearFullScreen();
  gdt_install();
  idt_install();
  init_pic();
  idt_set_gate(33, keyboard_handler, 0x8E);
  outportb(0x21, 0xfd);
  outportb(0xa1, 0xff);
  asm("sti");
  Screen->cursorY = 5;
  printCenter(5, "OOOOOO ", 0x0e);
  printCenter(6, "O     O", 0x0d);
  printCenter(7, "O     O", 0x0c);
  printCenter(8, "OOOOOO ", 0x0b);
  printCenter(9, "O   O  ", 0x0a);
  printCenter(10, "O    O ", 0x09);
  printCenter(11, "O     O", 0x08);
  printCenter(5, "OOOOOO ", 0x0e);
  printCenter(6, "O     O", 0x0d);
  printCenter(7, "O     O", 0x0c);
  printCenter(8, "OOOOOO ", 0x0b);
  printCenter(9, "O   O  ", 0x0a);
  printCenter(10, "O    O ", 0x09);
  printCenter(11, "O     O", 0x08);
  for (int i = 0; i < 12 * 160; i += 2)
  {
    if (Screen->vga[i] == 'O')
      Screen->vga[i] = 2;
  }
  printCenter(16, " Radical OS", 0x0f);
  setCursorPosition(-1, -1);
  printCenter(14, " .         ", 0x0f);
  Sleep(1);
  printCenter(14, " .  .      ", 0x0f);
  Sleep(1);
  printCenter(14, " .  .  .   ", 0x0f);
  Sleep(1);
  printCenter(14, " .  .  .  .", 0x0f);
  Sleep(1);
  clearScreen();
  shell_main();
  for (;;)
  {
  }
  return 0;
}