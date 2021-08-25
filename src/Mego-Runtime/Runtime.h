#pragma once
void push(int in);
int getRegValueOf(int in);
void setRegValueOf(int in,int value);
int pop();
void exec_instruction(int command,int arg1,int arg2);
void run_instruction(int * instruction);
void mem_init();
void execute_command(int command);
void setCpuPointer(int in);
void run_block(int * block);
void setMemoryAt(int in,int  mem);
int getMemoryAt(int in);
void execute_program(int * program);