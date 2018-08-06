#include "vga.h"
#include "io.h"

static struct vga_info
{
  uint8_t current_color;
  size_t x;
  size_t y;
  uint16_t *fb;
} vi;

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
  outb(0x3D4, 0x0A);
  outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

  outb(0x3D4, 0x0B);
  outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void vga_update_cursor(int x, int y)
{
  uint16_t pos = y * VGA_WIDTH + x;

  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t) (pos & 0xFF));
}

void vga_init(void)
{
  vi.current_color = vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  vi.x = 0;
  vi.y = 0;
  vi.fb = (uint16_t*) 0xB8000;

  for (size_t j = 0; j < VGA_HEIGHT; ++j)
    for (size_t i = 0; i < VGA_WIDTH; ++i)
      vi.fb[j * VGA_WIDTH + i] = vga_entry(' ', vi.current_color);
}

void vga_writechar(unsigned char c)
{
  if (c == '\r')
  {
    vi.x = 0;
    vga_update_cursor(vi.x, vi.y);
    return;
  }
  else if (c == '\n')
  {
    vi.y++;
    if (vi.y == VGA_HEIGHT)
      vi.y = 0;
    vga_update_cursor(vi.x, vi.y);
    return;
  }
  vi.fb[vi.y * VGA_WIDTH + vi.x] = vga_entry(c, vi.current_color);
  ++vi.x;
  if (vi.x == VGA_WIDTH)
  {
    vi.x = 0;
    ++vi.y;
    if (vi.y == VGA_HEIGHT)
      vi.y = 0;
  }
  vga_update_cursor(vi.x, vi.y);
}

void vga_write(char *s)
{
  char *current = s;

  for (; *current; ++current)
    vga_writechar(*current);
}
