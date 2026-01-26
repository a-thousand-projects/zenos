#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/keyboard_driver.h>

extern uint32_t isr0;
extern void gdt_install();

void hang_message(){
	printf("Oh dear - I've hung and cannot continue");
}

void kernel_main(void) {
	gdt_install();
	terminal_initialize();
	
	keyboard_init();
	printf("isr0 address: %X\n", isr0);
	printf("Hello, kernel World!\n");
	printf("Num %X\n", 0xDEADBEEF);

	//printf("Testing divide by zero exception...\n");
	//asm volatile("xor %%eax, %%eax; div %%eax" : : : "eax");
	//printf("After divide by zero\n");
	while(1)
	{
		for (int a=0;a<0xffff;a++);
	};

}
