#include "multiboot.h"

# GDT Segment entries
# Those entries will be shifted by 3 to represent a segment selector
# (Shifting by 3 clears the TI and RPL low order bits)
#define GDT_KCODE 1
#define GDT_KDATA 2

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
	lgdt gdt_desc
	# The code segment can only be reloaded by far jumping
	ljmp $(GDT_KCODE << 3), $protected_start

protected_start:
	# Reload all other segments
	movw $(GDT_KDATA << 3), %ax # Data segment selector
	movw %ax, %ds
	movw %ax, %ss
	movw $0, %ax # Null segment selector
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

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


#define SEG_CODE 0x8 // Set if segment is code, cleared if segment is data
#define SEG_DATA 0 // Clear the same byte as SEG_CODE
#define SEG_E 0x4 // Expand down flag (data segments only)
#define SEG_C 0x4 // Conforming flag (code segments only)
#define SEG_W 0x2 // Writable flag (data segments only)
#define SEG_R 0x2 // Readable flag (code segments only)
#define SEG_A 0x1 // Accessed flag

#define GDT_NULL_ENTRY	\
	.zero 8

# GDT Entry for code and data segments. Not suitable for system segments!
# 0x90: 1001xxxx (P = 1, DPL = 0, S = 1)
# 0xc0: 1100xxxx (G = 1, D/B = 1, L = 0, AVL = 0)
#define GDT_ENTRY(type, base, limit)		\
	.word (((limit) >> 12) & 0xffff),	\
	      ((base) & 0xffff);		\
	.byte (((base) >> 16) & 0xff),		\
	      (0x90 | ((type) & 0xf)),		\
	      (0xc0 | (((limit) >> 28) & 0xf)),	\
	      (((base) >> 24) & 0xff);


.section .data
gdt:
	GDT_NULL_ENTRY
	GDT_ENTRY(SEG_CODE | SEG_R, 0, 0xffffffff) # Kernel code segment
	GDT_ENTRY(SEG_DATA | SEG_W, 0, 0xffffffff) # Kernel data segment

gdt_desc:
	.word (gdt_desc - gdt - 1) # sizeof(gdt) - 1
	.long gdt
