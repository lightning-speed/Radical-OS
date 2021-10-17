asm("jmp _start");
void start_program(char **args, int offset);
int start()
{
  char *arguments = (char *)0xAAAA;
  char *args[10];
  for (int i = 0; i < 10; i++)
  {
    args[i] = (char *)(arguments + (i * 100));
  }
  int *temp = (int *)0x0;
  int offset = 0xAAAAAF;
  offset -= temp[5];
  start_program(args, offset);
}