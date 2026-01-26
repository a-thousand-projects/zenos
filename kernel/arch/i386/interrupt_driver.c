#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/tty.h>
#include "isr.h"
#include "irq.h"
#include "port_driver.h"
#include "registers.h"
#include "interrupt_driver.h"



// https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh

// PIC
// https://www.geeksforgeeks.org/computer-organization-architecture/command-words-of-8259-pic/
// https://wiki.osdev.org/8259_PIC
// https://www.thesatya.com/8259.html

#define PIC_1_CMD   0x20
#define PIC_1_DATA  0x21

#define PIC_2_CMD   0xA0
#define PIC_2_DATA  0xA1


static uint32_t offset;


idt_gate_t idt[256];
isr_t interrupt_handlers[256] = {0};
idt_register_t idt_reg;

char *exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void irq_handler(registers_t *r) {
    if (r->int_no != 32) {
    printf("IRQ %d received (int_no=%d)\n", r->int_no - 32, r->int_no);
    }
    
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    // Send EOI
    if (r->int_no >= 40) {
        port_byte_out(PIC_2_CMD, 0x20); // secondary EOI
    }
    port_byte_out(PIC_1_CMD, 0x20); // primary EOI
}

void isr_handler(registers_t *r) {
    printf("Exception %d triggered\n", r->int_no);
while(1);

}

void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].selector = 0x08; // see GDT
    //----------------------------------//
    idt[n].always0 = 0;
    // 0x8E = 1  00 0 1  110
    //        P DPL 0 D Type
    idt[n].flags = 0x8E; // Sets as Gate Type
    idt[n].high_offset = high_16(handler);
}
    



void isr_install() {
    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);


    // ICW1
    port_byte_out(PIC_1_CMD, 0x11);
    port_byte_out(PIC_2_CMD, 0x11);

    // ICW2 - IDT Offset
    port_byte_out(PIC_1_DATA, 0x20); 
    port_byte_out(PIC_2_DATA, 0x28);

    // ICW3 - Set PIC 1 to accept data from PIC 2
    port_byte_out(PIC_1_DATA, 0x04);
    port_byte_out(PIC_2_DATA, 0x02);

    // ICW4 - Mode - 8086 mode
    port_byte_out(PIC_1_DATA, 0x01);
    port_byte_out(PIC_2_DATA, 0x01);

     // OCW1 - Unmask all interrupts
    port_byte_out(PIC_1_DATA, 0x0);
    port_byte_out(PIC_2_DATA, 0x0);
    
    printf("PIC initialized. Checking masks...\n");
    uint8_t mask1 = port_byte_in(PIC_1_DATA);
    uint8_t mask2 = port_byte_in(PIC_2_DATA);
    printf("PIC1 mask: %X, PIC2 mask: %X\n", mask1, mask2);


    // IRQ ISRs (primary PIC)
    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);
    set_idt_gate(34, (uint32_t)irq2);
    set_idt_gate(35, (uint32_t)irq3);
    set_idt_gate(36, (uint32_t)irq4);
    set_idt_gate(37, (uint32_t)irq5);
    set_idt_gate(38, (uint32_t)irq6);
    set_idt_gate(39, (uint32_t)irq7);

    // IRQ ISRs (secondary PIC)
    set_idt_gate(40, (uint32_t)irq8);
    set_idt_gate(41, (uint32_t)irq9);
    set_idt_gate(42, (uint32_t)irq10);
    set_idt_gate(43, (uint32_t)irq11);
    set_idt_gate(44, (uint32_t)irq12);
    set_idt_gate(45, (uint32_t)irq13);
    set_idt_gate(46, (uint32_t)irq14);
    set_idt_gate(47, (uint32_t)irq15);

    load_idt();
   }



/* Function to register interrupt handler with custom call back function */
void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void load_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
    asm volatile ("sti"); // set the interrupt flag
}

