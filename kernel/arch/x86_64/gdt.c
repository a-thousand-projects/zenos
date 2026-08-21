//
// Created by graeme on 18/08/2026.
//
#include <stdint.h>
#include <kernel/gdt.h>


#define GDT_ENTRIES     3

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

extern void gdt_flush(uint64_t);

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base>>16) &0xff;
    gdt[num].base_high      = (base >> 24) & 0xff;
    gdt[num].limit_low      = (limit & 0xffff);
    gdt[num].granularity    = (limit >> 16) & 0xff;
    gdt[num].granularity    |= granularity & 0xf0;
    gdt[num].access         = access;
}

void gdt_install(void) {
    gp.limit    = (sizeof(struct gdt_entry)* GDT_ENTRIES) -1;
    gp.base     = (uint64_t)&gdt;

    gdt_set_gate(0,0,0,0,0);            // Null Descriptor
    gdt_set_gate(1,0,0,0x9a,0x20);      // Kernel code : L=1, D=0, G=0 - Matches boot.S's gdt64
    gdt_set_gate(2,0,0,0x92,0x0);       // Kernel data

    gdt_flush((uint64_t)&gp);
}