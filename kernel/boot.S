#include "multiboot.h"

# Multiboot header
#define MULTIBOOT_FLAGS MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO

# Multiboot section
.section .multiboot
.align 4
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_FLAGS
.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_FLAGS)

# Stack for the initial thread (so we can use C)
.section .bss
.align 16
stack_bottom:
.skip 16 * 1024
stack_top:

.section .text
.global _start
.type _start,	@function
_start:
	lea stack_top, %esp

	# Push multiboot info struct
	pushl %ebx
	# Push magic number
	pushl %eax
	# Switch to C. We should never return from this call
	call kernel_main

	# If we return for whatever reason, hang forever
	cli
1:	hlt
	jmp 1b

.size _start,	. - _start
