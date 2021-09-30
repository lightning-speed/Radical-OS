#include <Util/string.h>
#include <Drivers/Screen.h>
#include <Drivers/Keyboard.h>
#include <FS/fs.h>
#include <Mego-Runtime/Runtime.h>
#include <System/System.h>
#include <System/SystemTime.h>
#include <Graphics/Graphics.h>
#include <System/MemoryManager.h>
char *fileText;
int run_file(char *fileName)
{
 fileText = malloc(4096);
 set((int *)fileText, (int *)readFile(fileName));
}
