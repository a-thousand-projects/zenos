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
#include <kernel/cpuid.h>

// For TESTING
#include <kernel/pmm_tests.h>


extern uint32_t multiboot_magic;
extern uint32_t multiboot_ptr;

#define   MAGIC_NUMBER 0x36D76289

// https://littleosbook.github.io/#interrupts-and-input

void hang_message(){
	printf("Oh dear - I've hung and cannot continue");
}

void kernel_main(void) {
	asm volatile("cli");
	terminal_initialize();


	printf("Multiboot magic: 0x%x\n\r",multiboot_magic);
	if (multiboot_magic != MAGIC_NUMBER) {
		printf("WARNING: not loaded by a Multiboot-compliant bootloader\n\r");
	}
	else {
		printf("Magic Number : [OK]\n\r");
	}

	check_long_mode_support();

	asm volatile("cli");     // Disable Interrupts for now

	printf(" [OK]\n\r");

	printf("Initializing Event Queue\n\r");
	event_queue_init();
	printf(" [OK]\n\r");

	printf("Initalising User Terminal\n\r");
	// shell_init();
	printf(" [OK]\n\r");



	terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
	printf("**************************\n\r");
	printf("* Zenos - Experimental OS*\n\r");
	printf("**************************\n\r");

	// shell_run();

	while(1)
	{
		for (int a=0;a<0xffff;a++);
		// check the last key entered into the buffer

	};


}
