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
void copy(char to[], char from[], int till)

{
	for (int i = 0; i < till; i++)
	{
		to[i] = from[i];
	}
}
char *toString(int val)
{
	if (val == 0)
		return (char *)"0";
	char *out;
	int base = 10;
	char *buf;
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
int parseInt(char *a)
{
	int n = length(a);
	int out = 0;
	int ae = 1;
	for (int i = n - 1; i > -1; i--)
	{
		out += (a[i] - '0') * ae;
		ae *= 10;
	}
	return out;
}