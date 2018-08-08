#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "multiboot.h"

// Size of our page frame. For the low level memory allocator, this is the
// smallest unit of memory that can be allocated.
#define PAGE_SIZE 4096


uintptr_t find_first_addr(multiboot_info_t *mbi);

#endif /* end of include guard: MEMORY_H */
