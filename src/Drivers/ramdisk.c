#include <System/MemoryManager.h>
#include <Drivers/ramdisk.h>
void init_ramdisk()

{
	ramdisk_start = (int)&ramdisk_start;
	ramdisk_end = (int)&ramdisk_end;
}
