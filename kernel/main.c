#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "vga.h"

#define COM1 0x3F8

static inline void outb(uint16_t port, uint8_t value)
{
  __asm__ __volatile__ ("outb %0, %1\n\t"
                        : /* No output */
                        : "a" (value), "d" (port));
}

static void serial_init(void)
{
  outb(COM1 + 3, 0x3); /* 8 bits, no parity */
  outb(COM1 + 2, 0xc7);
  outb(COM1 + 1, 0x2);
}


static inline void serial_write(char *s)
{
  char *current;

  for (current = s; *current; ++current)
    outb(COM1, *current);
}


void kernel_main(uint32_t magic, multiboot_info_t * mbi)
{
  (void) magic;
  (void) mbi;

  serial_init();
  serial_write("bonjour\r\n");

  vga_init();

  vga_write("BONJOUR MDR COMMENT CA VA ?");

  for (;;)
    asm("hlt");
}
