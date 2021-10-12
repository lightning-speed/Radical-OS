#pragma once
void init_fs();
void write_block(int block, char *content);
void clear_block(int block);
char * read_block(int block);
void move_block(int from,int to);
char *fs;