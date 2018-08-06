#include "vga.h"

static struct vga_info
{
  uint8_t current_color;
  size_t x;
  size_t y;
  uint16_t *fb;
} vi;

void vga_init(void)
{
  vi.current_color = vga_color(VGA_COLOR_WHITE, VGA_COLOR_BROWN);
  vi.x = 0;
  vi.y = 0;
  vi.fb = (uint16_t*) 0xB8000;

  for (size_t j = 0; j < VGA_HEIGHT; ++j)
    for (size_t i = 0; i < VGA_WIDTH; ++i)
      vi.fb[j * VGA_WIDTH + i] = 0;
}

void vga_writechar(unsigned char c)
{
  vi.fb[vi.y * VGA_WIDTH + vi.x] = vga_entry(c, vi.current_color);
  ++vi.x;
  if (vi.x == VGA_WIDTH)
  {
    vi.x = 0;
    ++vi.y;
    if (vi.y == VGA_HEIGHT)
      vi.y = 0;
  }
}

void vga_write(char *s)
{
  char *current = s;

  for (; *current; ++current)
    vga_writechar(*current);
}
