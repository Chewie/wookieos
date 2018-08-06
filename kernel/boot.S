# Multiboot header
.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

# Multiboot section
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Stack for the initial thread (so we can use C)
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start,	@function
_start:
	mov $stack_top, %esp

	# Switch to C. We should never return from this call
	call kernel_main

	# If we return for whatever reason, hang forever
	cli
1:	hlt
	jmp 1b

.size _start,	. - _start
