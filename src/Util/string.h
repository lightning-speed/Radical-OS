#pragma once
typedef char *string;
int length(string abc);
string toString(int val);
string reverse(string in);
int parseInt(string a);
int equal(string a, string b);
int equalS(string a, string b, int till);
string join(string a, string b);
string addChar(string ab, char ae);
void concat(char *s1, char *s2);
char *substring(char *str, int a, int b);
void mk_equal(char *out, char *in);
void set(int *out, int *to);
string array_to_string(char array[], int length);
void split_to_args(char *args[], char *line, char regex, int array_length);
