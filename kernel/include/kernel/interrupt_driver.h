#ifndef _IDF_H_
#define _IDF_H_

#include <stdint.h>
#include "registers.h"

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define IDT_ENTRIES 256

void load_idt();
void install_interrupts();

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;





typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef void (*isr_t)(registers_t *);





/* Function to register interrupt handler with custom call back function */
void register_interrupt_handler(uint8_t n, isr_t handler);
void install_interrupts();

#endif