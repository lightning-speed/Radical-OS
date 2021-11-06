#include "Random.h"
#include <System/SystemTime.h>
static unsigned long int next = 1;

int random()
{
	next = next * 1103515245 + 12345 * getSeconds();
	return (unsigned int)((next / 65536) % 32768) * 12451;
}