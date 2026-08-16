//
// Created by graeme on 13/08/2026.
//

.global cpuid

cpuid:
    push %rbx
    movq %rdx, %r10         # save ebx_out ptr - cpuid is about to clobber rdx
    movq %rcx, %r11         # save ecx_out ptr - cpuid is about to clobber rcx

    movl %edi, %eax        # leaf argument, passed in rdi per SysV convention
    cpuid

    movl %eax, (%rsi)        # eax_out (rsi untouched by cpuid, safe to use directly)
    movl %ebx, (%r10)
    movl %ecx, (%r11)
    movl %edx, (%r8)        # edx_out (r8 untouched by cpuid, safe to use directly)

    pop %rbx
    ret


