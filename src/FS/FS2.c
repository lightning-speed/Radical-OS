#include "FS2.h"
#include <Util/string.h>
#include <System/MemoryManager.h>
#include"block.h"

void init_fs()
{
    fs = malloc(56000);
}