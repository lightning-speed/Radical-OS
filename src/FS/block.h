#include "FS2.h"
#include <Util/string.h>
#include <System/MemoryManager.h>
int block_size = 256;

void write_block(int block, char *content)
{
    int block_location = block_size * block;
    for (int i = 0; i < block_size; i++)
    {
        fs[block_location + i] = content[i];
    }
}
void clear_block(int block)
{
    int block_location = block_size * block;
    for (int i = 0; i < block_size; i++)
    {
        fs[block_location + i] = 0;
    }
}
char * read_block(int block){
    char * out = malloc(block_size);
    int block_location = block_size * block;
    for (int i = 0; i < block_size; i++)
    {
        out[i] = fs[block_location + i];
    }
    return out;
}
void move_block(int from,int to){
    char * temp = malloc(block_size);
    clear_block(to);
    set(temp,read_block(from));
    write_block(to,temp);
    clear_block(from);
}