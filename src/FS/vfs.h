#pragma once
void init_fs();
void createFile(char *name, char *content, int content_length);
char *read_file_at(int index);
char *read_file(char *name);
void write_file_at(int at, char *content, int content_length);
void delete_file_at(int at);
int get_file_size_at(int at);
int get_file_szie(char *name);
void rename_file(char *from, char *to);
char *get_file_name_at(int at);