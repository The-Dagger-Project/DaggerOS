#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("    ___                                ___  __ \n");
	printf("   /   \\__ _  __ _  __ _  ___ _ __    /___\\/ _\\ \n");
	printf("  / /\\ / _` |/ _` |/ _` |/ _ \\ '__|  //  //\\ \\ \n");
	printf(" / /_// (_| | (_| | (_| |  __/ |    / \\_// _\\ \\ \n");
	printf("/___,' \\__,_|\\__, |\\__, |\\___|_|    \\___/  \\__/\n");
	printf("             |___/ |___/            \n");
	printf("\n\n\nMade by  Ayman0x03 & aa2006\n");
}
