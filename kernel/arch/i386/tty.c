#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/port_driver.h>

#define CURSOR_MAX_NUMBER 5

typedef struct {
    uint8_t start;
    uint8_t end;
} cursor_t;



static cursor_t cursor_type[CURSOR_MAX_NUMBER] = {
	{14,15},
	{7,15}
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

static e_cursor_type current_cursor = CURSOR_DEFAULT;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_colour(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_char(' ', terminal_color);
		}
	}
	terminal_cursor_enable();

}


void terminal_cursor_type(e_cursor_type cursor)
{
	current_cursor = cursor;
}
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_char(c, color);
}

void terminal_putchar(uint16_t c) {
	unsigned char uc = c;
	if (c== '\n\r' || c== '\r\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row = 0; // Todo: screen must scroll if allowed 
		}
			terminal_cursor_put(terminal_column,terminal_row);
		return;
	}
	if (c=='\n')
	{
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row = 0; // Todo: screen must scroll if allowed
		}
		terminal_cursor_put(terminal_column,terminal_row);
		return;
	}
	if (c == '\r') {
		terminal_column = 0;
		return;
	}
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	// Move Cursor
	terminal_cursor_put(terminal_column,terminal_row);

}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
	{
		terminal_putchar(data[i]);
		terminal_cursor_put(terminal_column,terminal_row);
	}

}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void terminal_nl() {
	terminal_write("\n\r", 2);
}


void terminal_cursor_enable()
{
	port_byte_out(0x3D4, 0x0A);
	port_byte_out(0x3D5, (port_byte_in(0x3D5) & 0xC0) | cursor_type[current_cursor].start );

	port_byte_out(0x3D4, 0x0B);
	port_byte_out(0x3D5, (port_byte_in(0x3D5) & 0xE0) | cursor_type[current_cursor].end);
}


void terminal_cursor_disable()
{
	port_byte_out(0x3D4, 0x0A);
	port_byte_out(0x3D5, 0x20);
}

void terminal_cursor_put(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	port_byte_out(0x3D4, 0x0F);
	port_byte_out(0x3D5, (uint8_t) (pos & 0xFF));
	port_byte_out(0x3D4, 0x0E);
	port_byte_out(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t terminal_cursor_get(void)
{
    uint16_t pos = 0;
    port_byte_out(0x3D4, 0x0F);
    pos |= port_byte_in(0x3D5);
    port_byte_out(0x3D4, 0x0E);
    pos |= ((uint16_t)port_byte_in(0x3D5)) << 8;
    return pos;
}