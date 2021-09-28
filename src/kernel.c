#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <FS/fs.h>
#include <Shell/shell.h>
void printLogo();
extern int kmain()
{
  screen_init();
  clearScreen();
  time_init();
  printCenter(2, "Welcome to", 0x0b);
  Screen->cursorY = 5;
  printLogo();
  setCursorPosition(-1, -1);
  printCenter(15, "Operating System", 0x0c);
  printCenter(17, "Press Any Key to start", 0x09);
  printCenter(24, "(C) Krish", 0x0f);
  readChar();
  clearScreen();
  shell_main();
  for (;;)
  {
  }
  return 0;
}