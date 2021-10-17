#pragma once
void init_fs();
void create_file(char *name, char *content, int content_length);
char *read_file_at(int index);
char *read_file(char *name);
void write_file_at(int at, char *content, int content_length);
void delete_file_at(int at);
int get_file_size_at(int at);
int get_file_size(char *name);
void rename_file(char *from, char *to);
char *get_file_name_at(int at);
void *write_file(char *name, char *content, int content_length);
int does_file_exists(char *name);
int f_index;