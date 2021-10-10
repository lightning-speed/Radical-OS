#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <FS/fs.h>
#include <Shell/shell.h>
#include <System/BinaryRuntime.h>
#include <Util/string.h>
#include <Drivers/gdt.h>
void printLogo();
void Sleep(int in);
int kmain()
{
  time_init();
  screen_init();
  clearFullScreen();
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