.global irq0                            # System timer (PIT, Programmable Interval Timer)
.global irq1                            # Keyboard (PS/2 controller, port 0x60)
.global irq2                            # Cascade line for the secondary PIC (never fires directly — this is the wire the slave chip uses to signal the master
.global irq3                            # Serial port COM2 (and COM4)
.global irq4                            # Serial port COM1 (and COM3)
.global irq5                            # LPT2, or a sound card on many later PCs
.global irq6                            # Floppy disk controller
.global irq7                            # LPT1 (parallel port), also the classic "spurious IRQ" line
.global irq8                            # CMOS Real-Time Clock (RTC)
.global irq9                            # Free/redirected (often ACPI, or legacy IRQ2 redirect)
.global irq10                           # Free (commonly PCI devices)
.global irq11                           # Free (commonly PCI devices — NIC, SCSI, etc.)
.global irq12                           # PS/2 mouse
.global irq13                           # FPU / math coprocessor
.global irq14                           # Primary ATA channel (IDE hard disk)
.global irq15                           # Secondary ATA channel (IDE hard disk)

.global irq_common_stub
.global setInterrupt
.global clearInterrupt

.extern irq_handler


irq0:
    push $0
    push $32
    jmp irq_common_stub

irq1:
    push $0
    push $33
    jmp irq_common_stub

irq2:
    push $0
    push $34
    jmp irq_common_stub

irq3:
    push $0
    push $35
    jmp irq_common_stub

irq4:
    push $0
    push $36
    jmp irq_common_stub

irq5:
    push $0
    push $37
    jmp irq_common_stub

irq6:
    push $0
    push $38
    jmp irq_common_stub

irq7:
    push $0
    push $39
    jmp irq_common_stub

irq8:
    push $0
    push $40
    jmp irq_common_stub

irq9:
    push $0
    push $41
    jmp irq_common_stub

irq10:
    push $0
    push $42
    jmp irq_common_stub

irq11:
    push $0
    push $43
    jmp irq_common_stub

irq12:
    push $0
    push $45
    jmp irq_common_stub

irq13:
    push $0
    push $45
    jmp irq_common_stub

irq14:
    push $0
    push $46
    jmp irq_common_stub

irq15:
    push $0
    push $47
    jmp irq_common_stub

#************************************************************************
# irq_common_stub
#************************************************************************

irq_common_stub:
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %rbp
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %rsp, %rdi
    call irq_handler

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax

    add $16, %rsp
    iretq