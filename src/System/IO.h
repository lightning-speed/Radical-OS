#pragma once
typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;
uint8 inportb (uint16 _port);
void outportb (uint16 _port, uint8 _data);
void cli();