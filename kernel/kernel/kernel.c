#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/interrupt_driver.h>
#include <kernel/keyboard_driver.h>
#include <kernel/shell.h>
#include <kernel/eventqueue.h>
#include <kernel/pmm.h>

// For TESTING
#include <kernel/pmm_tests.h>

extern void gdt_install();

// https://littleosbook.github.io/#interrupts-and-input

void hang_message(){
	printf("Oh dear - I've hung and cannot continue");
}

void kernel_main(void) {
	asm volatile("cli");
	terminal_initialize();

	printf("Initializing GDT");
	gdt_install();
	printf(" [OK]\n\r");

	printf("Installing Inetrrupts\n\r");
	install_interrupts();
	printf(" [OK]\n\r");

	printf("Initializing Event Queue\n\r");
	event_queue_init();
	printf(" [OK]\n\r");

	printf("Initalising User Terminal\n\r");
	shell_init();
	
	printf(" [OK]\n\r");

	asm volatile("sti");

	terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
	printf("**************************\n\r");
	printf("* Zenos - Experimental OS*\n\r");
	printf("**************************\n\r");

	pmm_init();
	// test ONLY
	pmm_run_tests();
	// END TEST

	shell_run();
	
	while(1)
	{
		for (int a=0;a<0xffff;a++);
		// check the last key entered into the buffer

	};

}
