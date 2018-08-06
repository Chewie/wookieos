#include <stdint.h>

#include "io.h"
#include "serial.h"

void serial_init(void)
{
  outb(COM1 + 3, 0x3); /* 8 bits, no parity */
  outb(COM1 + 2, 0xc7);
  outb(COM1 + 1, 0x2);
}

void serial_writechar(char c)
{
  while ((inb(COM1 + LSR) & XMTRDY) == 0)
    asm("pause");
  outb(COM1, c);
}


void serial_write(const char *s)
{
  while (*s)
    serial_writechar(*s++);
}

