#include <stddef.h>
#include <stdint.h>

void kernel_main(void)
{
  char *fb = (char *)0xB8000;
  char stars[] = "/-\\|";
  size_t i;

  for (i = 0;; ++i)
    *fb = stars[i % 4];
}
