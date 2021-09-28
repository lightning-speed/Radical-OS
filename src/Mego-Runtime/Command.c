#include "Runtime.h"
#include <Drivers/Screen.h>
#include <Mego-Runtime/Runtime.h>
#include <Drivers/Keyboard.h>
#include <Timer/Timer.h>
void execute_command(int command)
{
  if (command == 1)
  {
    printC(getRegValueOf(3));
  }
  else if (command == 2)
  {
    setRegValueOf(4, readChar());
  }
  else if (command == 3)
  {
    clearScreen();
  }
  else if (command == 4)
  {
    if (getRegValueOf(6) != 1)
      setDefaultColor(0x00 + getRegValueOf(6));
  }
  else if (command == 5)
  {
    Sleep(getRegValueOf(3));
  }
}