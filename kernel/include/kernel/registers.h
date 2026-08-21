#pragma once
#include <stdint.h>


/*
** General Registers
RAX	EAX	AX	AH	AL	Accumulator
RBX	EBX	BX	BH	BL	Base
RCX	ECX	CX	CH	CL	Counter
RDX	EDX	DX	DH	DL	Data (commonly extends the A register)
RSI	ESI	SI	N/A	SIL	Source index for string operations
RDI	EDI	DI	N/A	DIL	Destination index for string operations
RSP	ESP	SP	N/A	SPL	Stack Pointer
RBP	EBP	BP	N/A	BPL	Base Pointer (meant for stack frames)

** Pointer Registers
RIP	EIP	IP	Instruction Pointer

** Segment Registers - Protected mode
CS	Code Segment
DS	Data Segment
SS	Stack Segment
ES	Extra Segment (used for string operations)
FS	General-purpose Segment
GS	General-purpose Segment

** Flags
0	CF	Carry Flag
1	1	Reserved
2	PF	Parity Flag
3	0	Reserved
4	AF	Auxiliary Carry Flag
5	0	Reserved
6	ZF	Zero Flag
7	SF	Sign Flag
8	TF	Trap Flag
9	IF	Interrupt Enable Flag
10	DF	Direction Flag
11	OF	Overflow Flag
12-13	IOPL	I/O Privilege Level
14	NT	Nested Task
15	0	Reserved
16	RF	Resume Flag
17	VM	Virtual-8086 Mode
18	AC	Alignment Check / Access Control
19	VIF	Virtual Interrupt Flag
20	VIP	Virtual Interrupt Pending
21	ID	ID Flag
22-63	0	Reserved
 */

typedef struct {
   uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
   uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
   uint64_t int_no, err_code;
   uint64_t rip, cs, rflags, rsp, ss;
} registers_t;