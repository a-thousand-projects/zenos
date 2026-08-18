.global gdt_flush
gdt_flush:
    lgdt (%rdi)                 # rdi = pointer to gdt_ptr, first arg as per SysV convestion

    movw $0x10, %ax             # kernel data selector
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    pushq $0x80                 # target: kernel code selector
    movq $.flush, %rax
    pushq %rax                  # target: return address
    lretq                       # far return - reloads CS and RIP together

 .flush:
    ret