#include "stdio.h"
#include "util_string.h"
void system(char *command)
{
                                               write_io(command);
                                               setAll(6, 0, 0, 0);
                                               asm("int $110");
}
