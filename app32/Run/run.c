#include <stdio.h>
#include <exec.h>
#include <util_string.h>
#include <file.h>
void start_program(char **args, int offset)
{
 if (!does_file_exists(args[1]))
 {
  printS("\nScript file doesn't exists" - offset);
 }
 char *file_content;
 file_content = read_file(args[1]);
 char temp[300];
 int ti = 0;
 for (int i = 0; file_content[i] != 0; i++)
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