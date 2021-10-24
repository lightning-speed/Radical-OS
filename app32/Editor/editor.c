#include <stdio.h>
#include <exec.h>
#include <util_string.h>
#include <file.h>
#include <graphics.h>
#include <memory.h>
int of;
char *text;
int text_index = 0;
void drawTB()
{
	for (int i = 0; i < 80; i++)
	{
		set_char_at(i, 0, ' ', 0x1f);
		set_char_at(i, 24, ' ', 0x1f);
	}
	printAt(34, 0, "Text Editor " - of, 0x1f);
	printAt(32, 24, "Press TAB to exit " - of, 0x1f);
}
void drawText()
{
	clearScreen();
	drawTB();
	Screen->cursorY = 1;
	Screen->cursorX = 0;
	print_t(text, 0x0f, text_index + 1);
}
void start_program(char **args, int offset)
{
	save_screen_state();
	of = offset;
	g_init();
	clearScreen();
	drawTB();
	text = malloc(1024 * 500);
	read_f(text, args[1], get_file_size_of(args[1]));
	text_index = get_file_size_of(args[1]) - 1;
	drawText();
	char in;
	while ((in = readChar()) != '\t')
	{
		if (in != '\b')
		{
			text_index++;
			text[text_index] = in;
		}
		else
		{
			text[text_index] = 0;
			text_index--;
		}
		drawText();
	}
	write_file(args[1], text, text_index + 1);
	clearScreen();
	load_screen_state();
}
