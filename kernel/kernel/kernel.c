#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/keyboard_driver.h>

extern void gdt_install();

void hang_message(){
	printf("Oh dear - I've hung and cannot continue");
}

void kernel_main(void) {
	gdt_install();
	terminal_initialize();
	
	keyboard_init();
	printf("Hello, kernel World!\n");
	printf("Num %X\n", 0xDEADBEEF);

	while(1)
	{
		for (int a=0;a<0xffff;a++);
	};

}
