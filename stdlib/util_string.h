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
void toString(int val, char out[])
{
	if (val == 0)
	{
		out[0] = '0';
		return;
	}
	char temp[32] = {0};
	int p = 0;
	for (int i = 0; val != 0; i++)
	{
		temp[i] = '0' + val % 10;
		val /= 10;
		p = i;
	}
	for (int i = p; i > -1; i--)
	{
		out[p - i] = temp[i];
	}
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