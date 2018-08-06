CFLAGS = -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS = -ffreestanding -nostdlib

TARGET_ARCH = -m32
TARGET_MACH = -m32

OBJS = boot.o vga.o serial.o main.o

.PHONY: all clean

all: wookieos.iso

wookieos.iso: wookieos.bin
	cp $^ iso/boot/
	grub-mkrescue -o $@ iso

wookieos.bin: $(OBJS)
	$(CC) -T linker.ld $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ -lgcc

clean:
	rm -f $(OBJS) wookieos.iso wookieos.bin
