#include <stdio.h>
#include <exec.h>
#include <util_string.h>
#include <file.h>
char *file_content;
void start_program(char **args, int offset)
{
 file_content = read_file(args[1]);
 char temp[300] = {0};
 int ti = 0;
 for (int i = 0; i < length(file_content); i++)
 {
		if (file_content[i] == '\n')
		{
			system(temp);
			ti = 0;
		}
		else
		{
			temp[ti] = file_content[i];
			temp[ti + 1] = 0;
			ti++;
		}
 }
}