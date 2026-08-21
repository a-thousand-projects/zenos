
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31
.global isr_common_stub

.extern isr_handler

# 0: Divide By Zero Exception
isr0:
    push $ 0
    push $ 0
    jmp isr_common_stub

# 1: Debug Exception
isr1:
    push $ 0
    push $ 1
    jmp isr_common_stub

# 2: Non Maskable Interrupt
isr2:
    push $ 0
    push $ 2
    jmp isr_common_stub

# 3: Breakpoint Exception
isr3:
    push $ 0
    push $ 3
    jmp isr_common_stub

# 4: Into Detected Overflow Exception
isr4:
    push $ 0
    push $ 4
    jmp isr_common_stub

# 5: Out of Bounds Exception
isr5:
    push $ 0
    push $ 5
    jmp isr_common_stub

# 6: Invalid Opcode Exception
isr6:
    push $ 0
    push $ 6
    jmp isr_common_stub

# 7: No Coprocessor Exception
isr7:
    push $ 0
    push $ 7
    jmp isr_common_stub

# 8: Double Fault Exception
isr8:
    push $ 8
    jmp isr_common_stub

# 9: Coprocessor Segment Overrun Exception
isr9:
    push $ 0
    push $ 9
    jmp isr_common_stub

# 10: Bad TSS Exception
isr10:
    push $ 10
    jmp isr_common_stub

# 11: Segment Not Present Exception
isr11:
    push $ 11
    jmp isr_common_stub

# 12: Stack Fault Exception
isr12:
    push $ 12
    jmp isr_common_stub

# 13: General Protection Fault Exception
isr13:
    push $ 13
    jmp isr_common_stub

# 14: Page Fault Exception
isr14:
    push $ 14
    jmp isr_common_stub

# 15: Unknown Interrupt Exception
isr15:
    push $ 0
    push $ 15
    jmp isr_common_stub

# 16: Coprocessor Fault Exception
isr16:
    push $ 0
    push $ 16
    jmp isr_common_stub

# 17: Alignment Check Exception
isr17:
    push $ 17
    jmp isr_common_stub

# 18: Machine Check Exception
isr18:
    push $ 0
    push $ 18
    jmp isr_common_stub

# 19: Reserved
isr19:
    push $ 0
    push $ 19
    jmp isr_common_stub

# 20: Reserved
isr20:
    push $ 0
    push $ 20
    jmp isr_common_stub

# 21: Reserved
isr21:
    push $ 0
    push $ 21
    jmp isr_common_stub

# 22: Reserved
isr22:
    push $ 0
    push $ 22
    jmp isr_common_stub

# 23: Reserved
isr23:
    push $ 0
    push $ 23
    jmp isr_common_stub

# 24: Reserved
isr24:
    push $ 0
    push $ 24
    jmp isr_common_stub

# 25: Reserved
isr25:
    push $ 0
    push $ 25
    jmp isr_common_stub

# 26: Reserved
isr26:
    push $ 0
    push $ 26
    jmp isr_common_stub

# 27: Reserved
isr27:
    push $ 0
    push $ 27
    jmp isr_common_stub

# 28: Reserved
isr28:
    push $ 0
    push $ 28
    jmp isr_common_stub

# 29: Reserved
isr29:
    push $ 0
    push $ 29
    jmp isr_common_stub

# 30: Reserved
isr30:
    push $ 0
    push $ 30
    jmp isr_common_stub

# 31: Reserved
isr31:
    push $ 0
    push $ 31
    jmp isr_common_stub


isr_common_stub:
    # push general purpose registers
    pusha

    # push data segment selector
    movw %ds, %ax
    push %eax

    # use kernel data segment
    movw $0x10,%ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
   # Call handler with pointer to registers_t on stack
    mov %esp, %eax
    push %eax

    call isr_handler

    #clean up
    pop %eax

    # restore original segment pointers segment
    pop %eax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs

    # restore registers
    popa

    # remove int_no and err_code from stack
    add $8,%esp

    # pops cs, eip, eflags, ss, and esp
    # https://www.felixcloutier.com/x86/iret:iretd
    iret
