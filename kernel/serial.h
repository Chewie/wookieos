#ifndef SERIAL_H
#define SERIAL_H

#define COM1 0x3F8
#define LSR 5 /* Line status port */
#define XMTRDY 0x20

void serial_init(void);
void serial_writechar(char c);
void serial_write(const char *s);

#endif /* end of include guard: SERIAL_H */
