#include "stdio.h"
#pragma once
typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;
char *malloc(int len)
{
	int *mem = (int *)0x0;
	mem[0] = len;
	setAll(45, 0, 0, 0);
	asm("int $110");
	return (char *)mem[0];
}
uint8 inportb(uint16 _port)
{
	uint8 rv;
	__asm__ __volatile__("inb %1, %0"
											 : "=a"(rv)
											 : "dN"(_port));
	return rv;
}

void outportb(uint16 _port, uint8 _data)
{
	__asm__ __volatile__("outb %1, %0"
											 :
											 : "dN"(_port), "a"(_data));
}