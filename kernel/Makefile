CC = i686-elf-gcc
AS = i686-elf-as

CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS = -ffreestanding -nostdlib

ARCH = x86
ARCHDIR = arch/$(ARCH)

include $(ARCHDIR)/make.config

OBJS = $(ARCH_OBJS) main.o

.PHONY: all clean

all: wookieos.iso

wookieos.iso: wookieos.bin
	cp $^ iso/boot/
	grub-mkrescue -o $@ iso

wookieos.bin: $(OBJS)
	$(CC) -T $(ARCHDIR)/linker.ld $(LDFLAGS) -o $@ $^ -lgcc

%.o: %.S
	$(CC) -c $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS) wookieos.iso wookieos.bin
