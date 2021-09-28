#include <Util/string.h>
#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <FS/fs.h>
#include <Mego-Runtime/Runtime.h>
#include <System/System.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <System/MemoryManager.h>
char *title;
void draw()
{
  for (int i = 1; i < 160; i += 2)
    Screen->vga[i] = 0x1f;
  printCenter(0, title, 0x1f);
}
void drawBottom()
{
  for (int i = 1; i < 160; i += 2)
    Screen->vga[i + 3840] = 0x1f;
  printCenter(24, "Press Tab To Save and Exit", 0x1f);
}
void startEditing(char *fn)
{
  setCursorPosition(0, 1);

  int pointer = 0;
  char *text = malloc(4096);
  if (doesFileExists(fn))
  {
    set((int *)text, (int *)readFile(fn));
    printC('\n');
    printW(text);
    pointer += length(text);
  }
  drawBottom();
  char in = 0;
  Screen->cursorY = 1;
  while ((in = readChar()) != '\t')
  {
    if (in == '\b')
    {
      if (pointer > 0)
      {
        text[pointer - 1] = 0;
        pointer -= 1;
        clearFullScreen();
        draw();
        printC('\n');
        printW(text);
        drawBottom();
      }
    }
    else
    {
      text[pointer] = in;
      pointer++;
      printC(in);
    }

    drawBottom();
    setCursorPosition(Screen->cursorX, Screen->cursorY);
  }
  if (!doesFileExists(fn))
    createFile(fn);
  clearFile(fn);
  writeFile(fn, text);
  clearFullScreen();
}
void edit_file(char *fn)
{
  title = malloc(32);
  set((int *)title, (int *)join("Text Editor - ", fn));
  clearScreen();
  for (int i = 1; i < 160; i += 2)
    Screen->vga[i] = 0x1f;
  printCenter(0, title, 0x1f);
  setDefaultColor(0x0f);
  startEditing(fn);
}