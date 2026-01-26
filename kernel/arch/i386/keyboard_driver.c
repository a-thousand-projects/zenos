#include "kernel/keyboard_driver.h"
#include "stdio.h"
#include "registers.h"
#include "irq.h"
#include "interrupt_driver.h"
#include "port_driver.h"
#include "kernel/tty.h"

#define IRQ1 33

static void keyboard_callback(registers_t *regs) {
     uint8_t scancode = port_byte_in(0x60);
    printf("Keyboard interrupt received! [%x]\n", scancode); 
}

void keyboard_init()
{
    printf("Initalising Keyboard Controller\n\r");
    isr_install();
    register_interrupt_handler(IRQ1, keyboard_callback);
}

