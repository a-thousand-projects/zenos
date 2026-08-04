#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

 typedef enum {
    CURSOR_DEFAULT = 0,
    CURSOR_SHIFT = 1
} e_cursor_type;


void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_nl();
void terminal_setcolor(uint8_t color);
void terminal_cursor_put(int x, int y);
void terminal_cursor_enable();
void terminal_cursor_disable();
void terminal_cursor_type(e_cursor_type cursor);
#endif
