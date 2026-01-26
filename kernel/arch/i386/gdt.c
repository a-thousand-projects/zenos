#include <stdint.h>


#define GDT_ENTRIES 3

// GDT entry structure
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));


// GDT pointer structure
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


// GDT with  entries: null, kernel code, kernel data, user code, user data
struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

// External assembly function to load GDT
extern void gdt_flush(uint32_t);

// Set up a GDT entry
static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;
    
    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}

// Initialize GDT - Protected Flat Mode
void gdt_install() {
    gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1; 
    gp.base = (uint32_t)&gdt;
    // NULL descriptor
    gdt_set_gate(0, 0, 0, 0, 0);
    
    // ** base is Zero because its a flat memory model **

    // Kernel code segment: base=0, limit=0xFFFFFFFF, access=0x9A, granularity=0xCF
    gdt_set_gate(1, 0x00, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // Kernel data segment: base=0, limit=0xFFFFFFFF, access=0x92, granularity=0xCF
    gdt_set_gate(2, 0x0, 0xFFFFFFFF, 0x92, 0xCF);
    
    // User code segment: base=0, limit=0xFFFFFFFF, access=0xFA, granularity=0xCF
    //gdt_set_gate(3, 0x10, 0xFFFFFFFF, 0xFA, 0xCF);
    
    // User data segment: base=0, limit=0xFFFFFFFF, access=0xF2, granularity=0xCF
   // gdt_set_gate(4, 0x0B, 0xFFFFFFFF, 0xF2, 0xCF);
    
    // Load the GDT
    gdt_flush((uint32_t)&gp);
}