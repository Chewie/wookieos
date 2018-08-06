#include "io.h"

void writechar(char ch)
{
  if (ch == '\n')
    writechar('\r');

  serial_writechar(ch);
  vga_writechar(ch);
}

void puts(const char *str)
{
  while (*str)
    writechar(*str++);
}

