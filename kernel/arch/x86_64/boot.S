# Declare constants for the multiboot header.
.set FLAG_ALIGN,    1<<0                                # align loaded modules on page boundaries
.set FLAG_MEMINFO,  1<<1                                # provide memory map
.set FLAG_NONE,     0                                   # No Flags
.set FLAGS,         FLAG_NONE                                     # this is the Multiboot 'flag' field
.set MAGIC_NUMBER,    0xE85250D6                        # 'magic number' lets bootloader2 find the header
.set CHECKSUM, -(MAGIC_NUMBER + FLAGS + (multiboot2_header_end - multiboot2_header_start))    # checksum of above, to prove we are multiboot

## NOTE
## FLAGS =  architecture: 0 = i386/protected mode

#############################
# Declare Multiboot 2 header
#############################
.section .multiboot
.align 8
multiboot2_header_start:
    .long MAGIC_NUMBER
    .long FLAGS
    .long multiboot2_header_end - multiboot2_header_start     # Header Length
    .long CHECKSUM

    # End tag
    .align  8
    .word   0
    .word   0
    .long   8
multiboot2_header_end:

##################
# GLOBAL VARIABLES
##################
    .section .data
    .global linked_label_addr
    linked_label_addr: .long 1f
    .global actual_eip
    actual_eip: .long 0

    #Grub info pointers
    .global multiboot_magic
    multiboot_magic: .long 0
    .global multiboot_info_ptr
    multiboot_info_ptr: .long 0
#Global Variables END

# UNINITIALIZED VARIABLES
    .section .bss
            .align 4096
        pml4_table:
            .skip 4096
        pdpt_table:
            .skip 4096
        pd_table:
            .skip 4096
# UNINITIALIZED VARIABLES END

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
.code32

# Save the GRUB Information Pointer and place in Global Variables
movl %eax, multiboot_magic
movl %ebx, multiboot_info_ptr
movl $stack_top, %esp

#####################################
####### Call the global constructors.
#####################################

#call _init
call 1f
1: pop %ebx
movl %ebx, actual_eip

###############################
####### BUILD 64  bit GDT Table
###############################

.section .data
.align 8
gdt64:
    .quad 0x0000000000000000                # NULL descriptor
    .quad 0x00209A0000000000                # 64 bit Code segment
    .quad 0x0000920000000000                # 64-bit Data Segment
gdt64_end:

gdt64_ptr:
    .word gdt64_end - gdt64 - 1
    .long gdt64

.section .text

#########################
####### Set up PAGE table
#########################
movl $pdpt_table, %eax                      # Move address of pdpt_table into eax
orl $0x3, %eax                              # OR with 0x3 (Present and Writable)
movl %eax, pml4_table                       # Store result in top Level Table pml4_table

movl $pd_table, %eax                        # Move address of pd_table inot eax
orl  $0x3, %eax                             # OR with 0x1 | 0x2 | 0x80 = 0x83
movl %eax, pdpt_table                       # store result in 2nd level table (pdpt_table)

#Set up pd_table[0]
movl $0x0, %eax                             # Move address of bottom of memory into eax
orl  $0x83, %eax                            # OR with 0x1 | 0x2 | 0x80 = 0x83
movl %eax, pd_table                         # store result in 3rd level PD table

# Set up pd_table[1]
movl $0x00200000, %eax                      # Move address 0x00200000 into eax
orl  $0x83, %eax                            # OR with 0x1 | 0x2 | 0x80 = 0x83
movl %eax, pd_table + 8                     # store result in 3rd level PD table


###########################
####### ENABLE PAE & PAGING
###########################
# set PAE
movl %cr4, %eax                             # Move the current value of CR4 into eax
orl $0x20, %eax                             # Set bit 5 = PAE
movl %eax, %cr4

# Set CR3 to addr of pml4_table
movl $pml4_table, %eax                       # Move pml4_table into %eax
movl %eax, %cr3

#Set EFER.LME - Enable Long Mode
movl $0xC0000080, %ecx                      # Move 0xC0000080 into ecx
rdmsr                                       # Reads EFER into edx:eax - EDX (high 32) and EAX (low 32)
orl $0x100, %eax                            # Set bit 8 = LME - Long Mode Enable
wrmsr                                       # Writes eds:eax back

# Set CR0.PG - Enable Paging
movl %cr0, %eax                             # Move CR0 into eax
orl $0x80000000, %eax                       # Set bit 31 = PG
movl %eax,%cr0

#########################
####### Initiate FAR Jump
#########################
lgdt gdt64_ptr
ljmp $0x08, $long_mode_start

.code64                                     # Compile for 64bit code
long_mode_start:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw %ax, %fs
    movw %ax, %gs

    movq $0xb8000, %rdi                      # Put VGA Base Address into di
    movq $0x2f36, (%rdi)                     # write '6' White on green
    movq $0x2f34, 2(%rdi)                    # write '4' White on green to next address

    cli                                      # Disable interrupts
 1: hlt                                      # Halt the process
    jmp 1b
 .code32                                     # Back to 32bit code

# Transfer control to the main kernel.
# call kernel_main

	# Hang if kernel_main unexpectedly returns.
#	cli
#1:	call hang_message
#	hlt
#	jmp 1b
#.size _start, . - _start
