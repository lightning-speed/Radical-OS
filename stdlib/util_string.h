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

char *toString(int val)
{
   if (val == 0)
      return (char *)"0";
   char *out = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   int base = 10;
   char *buf = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   int i = 30;
   for (; val && i; --i, val /= base)
      buf[i] = "0123456789abcdef"[val % base];
   out = &buf[i + 1];
   return out;
}
int max(int a, int b)
{
   if (a > b)
      return a;
   else
      return b;
}
int equal(char *a, char *b)
{
   for (int i = 0; i < max(length(a), length(b)); i++)
      if (a[i] != b[i])
         return 0;
   return 1;
}