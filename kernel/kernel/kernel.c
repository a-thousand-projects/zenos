#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/interrupt_driver.h>
#include <kernel/keyboard_driver.h>
#include <kernel/terminal.h>

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
	printf(" [OK]\n");

	printf("Installing Inetrrupts");
	install_interrupts();
	printf(" [OK]\n");

	printf("Initalising User Terminal");
	terminal_init();
	
	printf(" [OK]\n");

	asm volatile("sti");

	terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
	printf("**************************\n\r");
	printf("* Zenos - Experimental OS*\n");
	printf("**************************\n\r");


	
	while(1)
	{
		for (int a=0;a<0xffff;a++);
		// check the last key entered into the buffer

	};

}
