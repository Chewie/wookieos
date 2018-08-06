#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "vga.h"
#include "serial.h"



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
