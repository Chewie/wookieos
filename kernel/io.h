#ifndef IO_H
#define IO_H

#include <stdint.h>

#include "serial.h"
#include "vga.h"

static inline void outb(uint16_t port, uint8_t value)
{
  __asm__ __volatile__ ("outb %0, %1\n\t"
                        : /* No output */
                        : "a" (value), "dN" (port));
}

static inline uint8_t inb(uint16_t port)
{
  uint8_t value;

  __asm__ __volatile__ ("inb %1, %0\n\t"
                        : "=a" (value)
                        : "dN" (port));
  return value;
}

void writechar(char ch);
void puts(const char *str);


#endif /* end of include guard: IO_H */
