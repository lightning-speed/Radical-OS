#pragma once
struct sc
{
  int cursorX;
  int cursorY;
  int defaultColor;
  char *vga;
};
static struct sc *Screen;
void screen_init();
void clearScreen();
void printChar(char ch, int color);
void print(const char *str, int color);
void printW(const char *str);
void setScreenColor(int color);
void setDefaultColor(int color);
void setCursorPosition(int xe, int ye);
void backspace();
void printC(char a);
void clearFullScreen();