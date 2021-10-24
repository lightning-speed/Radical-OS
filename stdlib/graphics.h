#include "memory.h"
#pragma once
struct sc
{
	int cursorX;
	int cursorY;
	int defaultColor;
	char *vga;
};
static struct sc *Screen = (struct sc *)0xAA;
void g_init()
{
	Screen->cursorX = 0;
	Screen->cursorY = 0;
}
void clearScreen()
{
	for (int i = 0; i < 25 * 160; i++)
	{
		((char *)0xB8000)[i] = 0;
	}
	g_init();
}
void set_char_at(int x, int y, char ch, int color)
{
	((char *)0xB8000)[(y * 160) + (x * 2)] = ch;
	((char *)0xB8000)[(y * 160) + (x * 2) + 1] = color;
}
void printAt(int x, int y, char *str, int color)
{
	for (int i = 0; str[i] != 0; i++)
	{
		set_char_at(x + i, y, str[i], color);
	}
}
void print(char *str, int color)
{
	for (int i = 0; str[i] != 0; i++)
	{
		if (Screen->cursorX == 160 || str[i] == '\n')
		{
			Screen->cursorX = 0;
			Screen->cursorY++;
		}
		if (str[i] != '\n')
		{
			set_char_at(Screen->cursorX / 2, Screen->cursorY, str[i], color);
			Screen->cursorX += 2;
		}
	}
}
void print_t(char *str, int color, int till)
{
	for (int i = 0; i < till; i++)
	{
		if (Screen->cursorX == 160 || str[i] == '\n')
		{
			Screen->cursorX = 0;
			Screen->cursorY++;
		}
		if (str[i] != '\n')
		{
			set_char_at(Screen->cursorX / 2, Screen->cursorY, str[i], color);
			Screen->cursorX += 2;
		}
	}
}
char *sc;

void save_screen_state()
{
	sc = malloc(25 * 160);
	for (int i = 0; i < 25 * 160; i++)
	{
		sc[i] = ((char *)0xB8000)[i];
	}
}
void load_screen_state()
{
	for (int i = 0; i < 25 * 160; i++)
	{
		((char *)0xB8000)[i] = sc[i];
	}
}