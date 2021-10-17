#pragma once
int length(char str[])
{
   for (int i = 0;; i++)
      if (str[i] == 0)
         return i;
}
void strcopy(char to[], char from[])

{
   for (int i = 0; i < length(from); i++)
   {
      to[i] = from[i];
   }
}
