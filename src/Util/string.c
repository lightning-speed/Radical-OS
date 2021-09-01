#include "string.h"
#include<string.h>
int length(string abc){
  for(int i = 0;;i++)
  if(abc[i]=='\0')return i;
}
string reverse(string in){
    string out = (string)"";
    int temp = 0;
    for(int i = length(in)-1;i>-1;i--){
        out[temp] = in[i];
        temp++;
    }
    return out;
}
string toString(int val){
    if(val==0)return (string)"0";
    string out = (string)"";
    int base = 10;
    char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    out = &buf[i+1];
    return out;
}
int parseInt(string a){
   int n = length(a);
   int out = 0;
   int ae = 1;
   for(int i = n-1;i>-1;i--){
        out+=(a[i]-'0')*ae;
        ae*=10;
   }
   return out;
}
int max(int a,int b){
    if(a>b)return a;
    else return b;
}
int equal(string a,string b){
   for(int i = 0;i<max(length(a),length(b));i++)
    if(a[i]!=b[i])return 0;
   return 1;
}
int equalS(string a, string b,int till){
 for(int i = 0;i<till;i++)
  if(a[i]!=b[i])return 0;
  return 1;
}
string join(char * a,char * b){
    string out = a;
    concat(out,b);
    return out;
}
void concat(char * s1, char * s2) {
	int i, j;
	i = length(s1);
	for (j = 0; s2[j] != '\0'; i++, j++) {
		s1[i] = s2[j];
	}
	s1[i] = '\0';
}
string addChar(string ab,char ae){
    string outf = ab;
    outf[length(ab)]=ae;
    return outf;
}
char * substring(char * str,int a,int b){
   char * out="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
   int stri = 0;
   for(int i = a;i<b;i++){
       out[stri]=str[i];
       out[stri+1]=0;
       stri++;
   }
   return out;
}
void set(int * a,int * b){
  for(int i = 0;b[i]!=0;i++){
    a[i]=b[i];
  }
}