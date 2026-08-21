.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15
.global irq16
.global irq17
.global irq18
.global irq19
.global irq20
.global irq21
.global irq22
.global irq23
.global irq24
.global irq25
.global irq26
.global irq27
.global irq28
.global irq29
.global irq30
.global irq31
.global irq_common_stub
.global setInterrupt
.global clearInterrupt

.extern irq_handler

# 0: Divide By Zero Exception

irq0:
    push $ 0   // Error Code
    push $ 32  // Int number
    jmp irq_common_stub

# 1: Debug Exception
irq1:
    push $ 0
    push $ 33
    jmp irq_common_stub

# 2: Non Maskable Interrupt
irq2:
    push $ 0
    push $ 34
    jmp irq_common_stub

# 3: Breakpoint Exception
irq3:
    push $ 0
    push $ 35
    jmp irq_common_stub

# 4: Into Detected Overflow Exception
irq4:
    push $ 0
    push $ 36
    jmp irq_common_stub

# 5: Out of Bounds Exception
irq5:
    push $ 0
    push $ 37
    jmp irq_common_stub

# 6: Invalid Opcode Exception
irq6:
    push $ 0
    push $ 38
    jmp irq_common_stub

# 7: No Coprocessor Exception
irq7:
    push $ 0
    push $ 39
    jmp irq_common_stub

# 8: Double Fault Exception
irq8:
    push $ 0
    push $ 40
    jmp irq_common_stub

# 9: Coprocessor Segment Overrun Exception
irq9:
    push $ 0
    push $ 41
    jmp irq_common_stub

# 10: Bad TSS Exception
irq10:
    push $ 0
    push $ 42
    jmp irq_common_stub

# 11: Segment Not Present Exception
irq11:
    push $ 0
    push $ 43
    jmp irq_common_stub

# 12: Stack Fault Exception
irq12:
    push $ 0
    push $ 44
    jmp irq_common_stub

# 13: General Protection Fault Exception
irq13:
    push $ 0
    push $ 45
    jmp irq_common_stub

# 14: Page Fault Exception
irq14:
    push $ 0
    push $ 46
    jmp irq_common_stub

# 15: Unknown Interrupt Exception
irq15:
    push $ 0
    push $ 47
    jmp irq_common_stub

# 16: Coprocessor Fault Exception
irq16:
    push $ 0
    push $ 48
    jmp irq_common_stub

# 17: Alignment Check Exception
irq17:
    push $ 0
    push $ 49
    jmp irq_common_stub

# 18: Machine Check Exception
irq18:
    push $ 0
    push $ 50
    jmp irq_common_stub

# 19: Reserved
irq19:
    push $ 0
    push $ 51
    jmp irq_common_stub

# 20: Reserved
irq20:
    push $ 0
    push $ 52
    jmp irq_common_stub

# 21: Reserved
irq21:
    push $ 0
    push $ 53
    jmp irq_common_stub

# 22: Reserved
irq22:
    push $ 0
    push $ 54
    jmp irq_common_stub

# 23: Reserved
irq23:
    push $ 0
    push $ 55
    jmp irq_common_stub

# 24: Reserved
irq24:
    push $ 0
    push $ 56
    jmp irq_common_stub

# 25: Reserved
irq25:
    push $ 0
    push $ 57
    jmp irq_common_stub

# 26: Reserved
irq26:
    push $ 0
    push $ 58
    jmp irq_common_stub

# 27: Reserved
irq27:
    push $ 0
    push $ 59
    jmp irq_common_stub

# 28: Reserved
irq28:
    push $ 0
    push $ 60
    jmp irq_common_stub

# 29: Reserved
irq29:
    push $ 0
    push $ 61
    jmp irq_common_stub

# 30: Reserved
irq30:
    push $ 0
    push $ 62
    jmp irq_common_stub

# 31: Reserved
irq31:
    push $ 0
    push $ 63
    jmp irq_common_stub


    

irq_common_stub:
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
    call irq_handler
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

