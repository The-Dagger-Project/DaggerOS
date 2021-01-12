#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\nMade by aa2006 & Ayman0x03");
}
