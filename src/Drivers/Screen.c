#include "Screen.h"
#include <System/IO.h>

void scroll();
void printChar(char ch, int color)
{
  if (ch == '\b')
  {
    backspace();
    return;
  }
  if (Screen->cursorY >= 24)
  {
    scroll();
  }
  if (ch == '\n' || Screen->cursorX == 160)
  {
    Screen->cursorY++;
    Screen->cursorX = 0;
  }
  if (ch != '\n')
  {
    Screen->vga[(Screen->cursorY * 160) + Screen->cursorX] = ch;
    Screen->vga[(Screen->cursorY * 160) + Screen->cursorX + 1] = color;
    Screen->cursorX += 2;
  }
  setCursorPosition(Screen->cursorX, Screen->cursorY);
}
void setCursorPosition(int xe, int ye)
{
  unsigned temp;
  temp = ye * 80 + (xe / 2);
  outportb(0x3D4, 14);
  outportb(0x3D5, temp >> 8);
  outportb(0x3D4, 15);
  outportb(0x3D5, temp);
}
void printC(char a)
{
  printChar(a, Screen->defaultColor);
}
void print(const char *str, int color)
{
  for (int i = 0; str[i] != 0; i++)
  {
    printChar(str[i], color);
  }
  setCursorPosition(Screen->cursorX, Screen->cursorY);
}
void printW(const char *str)
{
  print(str, Screen->defaultColor);
  setCursorPosition(Screen->cursorX, Screen->cursorY);
}
void clearScreen()
{
  Screen->cursorX = 0;
  Screen->cursorY = 0;
  for (int i = 0; i < 160 * 25; i += 2)
  {
    Screen->vga[i] = 0;
  }
}

void screen_init()
{
  Screen->vga = (char *)0xB8000;
  Screen->cursorX = 0;
  Screen->cursorY = 0;
  Screen->defaultColor = 0x07;
}
void setDefaultColor(int color)
{
  Screen->defaultColor = color;
}
void clearLine(int line)
{
  for (int i = 0; i < 160; i++)
  {
    Screen->vga[(160 * line) + i] = 0;
  }
}
void setScreenColor(int color)
{
  setDefaultColor(color);
  char *vga = (char *)0xB8000;
  for (int i = 1; i < 160 * 26; i += 2)
  {
    vga[i] = (color - (color % 16)) + (vga[i] % 16);
  }
}
void scroll()
{
  char **lines;
  for (int i = 1; i < Screen->cursorY + 1; i++)
  {
    for (int j = 0; j < 160; j++)
    {
      Screen->vga[(160 * (i - 1)) + j] = Screen->vga[(160 * i) + j];
    }
  }
  clearLine(Screen->cursorY);
  Screen->cursorY--;
}
void backspace()
{
  if (Screen->cursorX != 0)
    Screen->cursorX -= 2;
  else
  {
    Screen->cursorX = 160;
    Screen->cursorY--;
  }
  Screen->vga[(Screen->cursorY * 160) + Screen->cursorX] = 0;
  setCursorPosition(Screen->cursorX, Screen->cursorY);
}
void clearFullScreen()
{
  Screen->cursorX = 0;
  Screen->cursorY = 0;
  for (int i = 0; i < 25 * 160; i += 2)
  {
    Screen->vga[i] = 0;
    Screen->vga[i + 1] = Screen->defaultColor;
  }
}