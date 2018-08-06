#include "vga.h"

static struct vga_info vi;

struct vga_info *vga_init(void)
{
  vi.current_color = vga_color(VGA_COLOR_WHITE, VGA_COLOR_BROWN);
  vi.x = 0;
  vi.y = 0;
  vi.fb = (uint16_t*) 0xB8000;

  for (size_t j = 0; j < VGA_HEIGHT; ++j)
    for (size_t i = 0; i < VGA_WIDTH; ++i)
      vi.fb[j * VGA_WIDTH + i] = vga_entry(' ', vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));

  return &vi;
}

void vga_writechar(struct vga_info *vi, unsigned char c)
{
  vi->fb[vi->y * VGA_WIDTH + vi->x] = vga_entry(c, vi->current_color);
  ++vi->x;
  if (vi->x == VGA_WIDTH)
  {
    vi->x = 0;
    ++vi->y;
    if (vi->y == VGA_HEIGHT)
      vi->y = 0;
  }
}

void vga_write(struct vga_info *vi, char *s)
{
  char *current = s;

  for (; *current; ++current)
    vga_writechar(vi, *current);
}
