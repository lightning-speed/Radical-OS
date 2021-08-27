#pragma once
void createFile(char * fn);
void fs_init();
char * getFS();
void writeFileAt(int indexF,char * content);
char * getFileNameAt(int indexF);
char * getFileContentAt(int indexF);
int total_files();
int file_size_of(char * name);
char * readFile(char * name);
int doesFileExists(char * name);
void writeFile(char * name,char * text);
void copyFile(char * in,char * des);
void clearFile(char * name);
void deleteFile(char * name);