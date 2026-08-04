#include "kernel/terminal.h"
#include "kernel/terminal_commands.h"
#include "kernel/cbuffer.h"
#include "kernel/keyboard_driver.h"


circular_buffer_t terminal_buffer={.init_status= 0};


void terminal_init()
{
    cbuffer_initialize(&terminal_buffer);
    // Assign buffer to keyboard input
    keyboard_init(&terminal_buffer);
};

