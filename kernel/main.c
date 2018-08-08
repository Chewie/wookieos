#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "vga.h"
#include "serial.h"
#include "printf.h"


static void print_mmap(multiboot_info_t *mbi)
{
  multiboot_memory_map_t *mmap;
  printf("mmap_addr = 0x%x, mmap_length = 0x%x\n",
        (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
  for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
      (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
      mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                + mmap->size + sizeof (mmap->size)))
    printf(" size = 0x%x, base_addr = 0x%x%08x,"
           " length = 0x%x%08x, type = 0x%x\n",
           (unsigned) mmap->size,
           (unsigned) (mmap->addr >> 32),
           (unsigned) (mmap->addr & 0xffffffff),
           (unsigned) (mmap->len >> 32),
           (unsigned) (mmap->len & 0xffffffff),
           (unsigned) mmap->type);
}

static void print_modules(multiboot_info_t *mbi)
{
  printf("mods_count = %d, mods_addr = 0x%x\n", mbi->mods_count, mbi->mods_addr);
  multiboot_module_t *curr_mod = (multiboot_module_t*)mbi->mods_addr;
  for (size_t i = 0;
       i < mbi->mods_count;
       i++, curr_mod++)
  {
    printf(" start = 0x%x end = 0x%x cmdline = %s\n",
           curr_mod->mod_start,
           curr_mod->mod_end,
           (char*)curr_mod->cmdline);
  }
}

extern void *_end[];

void kernel_main(uint32_t magic, multiboot_info_t *mbi)
{
  (void) magic;

  serial_init();
  vga_init();

  if (!(mbi->flags & MULTIBOOT_INFO_MEM_MAP))
  {
    printf("[ERR] Multiboot memory map info unavailable!\n");
    return;
  }
  else
    print_mmap(mbi);

  if (!(mbi->flags & MULTIBOOT_INFO_MODS))
    printf("[INFO] No multiboot module info available\n");
  else
    print_modules(mbi);

  printf("_end = 0x%x\n", _end);


  for (;;)
    asm("hlt");
}
