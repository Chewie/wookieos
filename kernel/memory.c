#include <stdint.h>

#include "multiboot.h"
#include "printf.h"
#include "memory.h"

// Align to the upper page size alignment.
#define page_align(mem) (((uintptr_t)(mem) + PAGE_SIZE) & ~(PAGE_SIZE - 1))

// End of the kernel code+data. The symbol is defined by the linker script
// The symbol has the address that we want, but no value.
// The array trick is to get its address instead of its value
extern void *_end[];

// Find the first usable address for our allocator.
// Since modules could potentially be loaded, we can't rely blindly on _end
uintptr_t find_first_addr(multiboot_info_t *mbi)
{
  if (!(mbi->flags & MULTIBOOT_INFO_MODS) || !mbi->mods_count)
    return page_align(_end);

  // Get the end address of the last module
  multiboot_module_t *mods = (multiboot_module_t*)mbi->mods_addr;
  uintptr_t mods_end = mods[mbi->mods_count - 1].mod_end;

  // Either modules are loaded before the kernel and we choose _end,
  // or modules are loaded after the kernel and we choose mods_end
  if (mods_end < (uintptr_t)_end)
    return page_align(_end);
  else
    return page_align(mods_end);
}
