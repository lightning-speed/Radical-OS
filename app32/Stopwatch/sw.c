#include <stdio.h>
#include <util_string.h>
#include <graphics.h>
#include <time.h>
int ofs;
int ms = 0, sec = 0, min = 0, hour = 0, running = 0;
void write_time(int hour, int minutes, int seconds, int milliseconds)
{
	char hour_b[3] = {0, 0, 0}, minutes_b[3] = {0, 0, 0}, seconds_b[3] = {0, 0, 0}, milliseconds_b[3] = {0, 0, 0};
	toString(hour, hour_b);
	toString(minutes, minutes_b);
	toString(seconds, seconds_b);
	toString(milliseconds, milliseconds_b);
	printAt(33, 7, hour_b, 0x0f);
	printAt(37, 7, minutes_b, 0x0f);
	printAt(41, 7, seconds_b, 0x0f);
	printAt(45, 7, milliseconds_b, 0x0f);
	set_char_at(35, 7, ':', 0x0f);
	set_char_at(39, 7, ':', 0x0f);
	set_char_at(43, 7, ':', 0x0f);
}
void update()
{
	if (running)
	{
		ms++;
		if (ms == 100)
		{
			sec++;
			ms = 0;
		}
		if (sec == 60)
		{
			min++;
			sec = 0;
		}
		write_time(hour, min, sec, ms);
	}
}
void start_program(char **args, int offset)
{
	save_screen_state();
	ofs = offset;
	clearScreen();
	for (int i = 0; i < 80; i++)
		set_char_at(i, 0, ' ', 0x1f);
	printAt(35, 0, "Stop-Watch" - offset, 0x1f);
	printAt(25, 3, "Press Space to Start and Stop " - offset, 0x0f);
	printAt(31, 24, "Press Tab to exit " - offset, 0x0f);

	printAt(37, 15, " Start " - offset, 0xcf);
	struct TASK t = create_task((int)update - offset, 100);
	write_time(hour, min, sec, ms);
	char in = 0;
	while (in != '\t')
	{
		in = readChar();
		if (in == ' ')
		{
			if (running == 1)
			{
				running = 0;
				printAt(37, 15, " Start " - offset, 0xcf);
			}

			else
			{
				running = 1;
				printAt(37, 15, "  Stop " - offset, 0xaf);
			}
		}
	}
	dispose_task(t);
	clearScreen();
	load_screen_state();
}