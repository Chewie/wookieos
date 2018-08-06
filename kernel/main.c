#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "vga.h"
#include "serial.h"
#include "printf.h"



void kernel_main(uint32_t magic, multiboot_info_t * mbi)
{
  (void) magic;
  (void) mbi;

  serial_init();

  vga_init();
  puts("Bonjour !\n");
  printf("mon chiffre prefere est %d\n", 42);
  printf("magic vaut %X\n", magic);

  for (;;)
    asm("hlt");
}
