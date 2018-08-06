#ifndef PRINTF_H
#define PRINTF_H

#include <stdarg.h>
#include "io.h"

int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int printf(const char *fmt, ...);

#endif /* end of include guard: PRINTF_H */
