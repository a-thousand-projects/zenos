//
// Created by graeme on 13/08/2026.
//

.global cpuid

cpuid:
    push %ebp
    movl %esp, %ebp
    push %ebx               # callee-saved; cpuid overwrites it, must restore before returning
    push %edi               # callee-saved; used below as a scratch pointer register

    movl 8(%ebp), %eax       # leaf argument
    cpuid
    movl  12(%ebp), %edi    # &eax_out
    movl  %eax, (%edi)
    movl  16(%ebp), %edi    # &ebx_out
    movl  %ebx, (%edi)
    movl  20(%ebp), %edi    # &ecx_out
    movl  %ecx, (%edi)
    movl  24(%ebp), %edi    # &edx_out
    movl  %edx, (%edi)

    pop   %edi
    pop   %ebx
    pop   %ebp
    ret


