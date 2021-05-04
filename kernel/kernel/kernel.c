#include <stdio.h>

#include <kernel/tty.h>
#include "../drivers/kbd.h"
#include "../arch/i386/vga.h"



void kernel_main(void) {
	terminal_initialize();
	terminal_start();
	
	int cmd = 0;
	hello_user("root");
	while(1){       //-------------Command loop
    	prompt();
    	cmd = get_command();
    	execute_command(cmd);
    	if(cmd == 2){
      		break;
    	}
    	cmd = 0;
  	}
}
