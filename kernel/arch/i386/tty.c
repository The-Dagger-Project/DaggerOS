#include <kernel/tty.h>

#include "vga.h"
#include "../../drivers/kbd.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_start() {
	terminal_setcolor(VGA_COLOR_BLUE);
	printf("                   ___                                ___  __ \n");
	printf("                  /   \\__ _  __ _  __ _  ___ _ __    /___\\/ _\\ \n");
	printf("                 / /\\ / _` |/ _` |/ _` |/ _ \\ '__|  //  //\\ \\ \n");
	printf("                / /_// (_| | (_| | (_| |  __/ |    / \\_// _\\ \\ \n");
	printf("               /___,' \\__,_|\\__, |\\__, |\\___|_|    \\___/  \\__/\n");
	printf("                            |___/ |___/            \n");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);
	printf("\n\n\n                           Made by Ayman0x03 & aa2006\n\n\n");
}
void init() {
	terminal_setcolor(VGA_COLOR_BLUE);
	printf("                   ___                                ___  __ \n");
	printf("                  /   \\__ _  __ _  __ _  ___ _ __    /___\\/ _\\ \n");
	printf("                 / /\\ / _` |/ _` |/ _` |/ _ \\ '__|  //  //\\ \\ \n");
	printf("                / /_// (_| | (_| | (_| |  __/ |    / \\_// _\\ \\ \n");
	printf("               /___,' \\__,_|\\__, |\\__, |\\___|_|    \\___/  \\__/\n");
	printf("                            |___/ |___/            \n");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n                           Made by Ayman0x03 & aa2006\n\n\n");
}


void terminal_scroll(){
    for(int i = 0; (long unsigned int)i < VGA_HEIGHT; i++){
        for (int m = 0; (long unsigned int)m < VGA_WIDTH; m++){
            terminal_buffer[i * VGA_WIDTH + m] = terminal_buffer[(i + 1) * VGA_WIDTH + m];
        }
    }
}

void terminal_clear_line(size_t y) {
	size_t x = 0;
	while (x < VGA_WIDTH) {
		terminal_putentryat(' ', terminal_color, x, y);
		x ++;
	}
}

void terminal_clearscreen(void) {
	size_t y = 0;
	while (y < VGA_HEIGHT) {
		terminal_clear_line(y);
		y ++;
	}
	terminal_row = 0;
	terminal_column = 0;
}

void terminal_putchar(char c) {
	if (terminal_row + 1 == VGA_HEIGHT) {
		terminal_scroll();
		terminal_row --;
		terminal_column = 0;
	} 

	
	if (c == '\n') {
		terminal_row ++;
		terminal_column = 0;
	} else {
		unsigned char uc = c;
		terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			terminal_row ++;
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

int strcmp(const char *str1, const char *str2){
  int res = 1;
  int i = 0;
  if(strlen(str1) == strlen(str2)){
    while(str1[i] != 0x0A && str2[i] != 0x0A){
      if(str1[i] != str2[i]){
        res = 0;
      }
      i++;
    }
  }else{res = 0;}
  return res;
}

bool isascii(int c) {
	return c >= 0 && c < 128;
}

uint8_t kybrd_enc_read_buf () {
  return inb(KYBRD_ENC_INPUT_BUF);
}

uint8_t kybrd_ctrl_read_status(){
  return inb(KYBRD_CTRL_STATS_REG);
}

char getchar() {
	uint8_t code = 0;
	uint8_t key = 0;
	while(1) {
		if (kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF) {
			code = kybrd_enc_read_buf();
			if(code <= 0x58) {
				key = _kkybrd_scancode_std[code];
				break;
			}
		}
	}
	return key;
}

void getline(char* string, int len) {
	uint8_t i = 0;
	char temp = 0;
	memset(string, 0, len);
	
	while(i < len && temp != 0x0D) {
		temp = getchar();
		if(isascii(temp) && temp != 0x0D) {
			if(temp == 0x08) {
				terminal_column --;
				terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
				i --;
			} else if (temp >= 22 && temp <= 127) {
				terminal_putchar(temp);
				string[i] = temp;
				i ++;
			}
		}
	}
	string[i] = 0x0A;
}

void prompt() {
	terminal_writestring("root@DaggerOS> ");
}

void hello_user(char* user) {
	terminal_setcolor(VGA_COLOR_BLUE);
	terminal_writestring("                          --- Welcome to DaggerOS ---\n");
	printf(              "                                   Hello, ");
	terminal_writestring(user);
	printf("\n");
	terminal_setcolor(VGA_COLOR_LIGHT_GREY);
}

// ---------------------------------- Basic Commands ------------------------------------
void help() {
	terminal_writestring("---- HELP MENU ----\n");
  	terminal_writestring("Commands:\n");
  	terminal_writestring("  help -------> this menu\n");
  	terminal_writestring("  shutdown ---> power off machine\n");
  	terminal_writestring("  echo -------> type and receive a response\n");
  	terminal_writestring("  clear ------> clear screen\n");
	terminal_writestring("  init -------> display start screen\n");
	terminal_writestring("  color ------> change text color\n");
	terminal_writestring("  about ------> display about information\n");
	terminal_writestring("Warning: special keys (esc, ctrl, ...) will not work.\n");
}

void color() {
	char string[50];
	terminal_writestring("Enter color: ");
	getline(string, 50);
	printf("\n");
	if (strcmp(string, "black\x0D") == 1) {
		terminal_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
	} else if (strcmp(string, "white\x0D") == 1) {
		terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	} else if (strcmp(string, "blue\x0D") == 1) {
		terminal_setcolor(VGA_COLOR_BLUE);
	} else if (strcmp(string, "green\x0D") == 1) {
		terminal_setcolor(VGA_COLOR_GREEN);
	} else if (strcmp(string, "red\x0D") == 1) {
		terminal_setcolor(VGA_COLOR_RED);
	}  else if (strcmp(string, "yellow\x0D") == 1) {
		terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
	} else {
		terminal_writestring("Color not found\n");
	}
}

void echo() {
	char string[50];
	terminal_writestring("Enter string: ");
	getline(string, 50);
	printf("\n");
	terminal_writestring(string);
}
void about(){
	char string[50];
	terminal_writestring("DaggerOS is a hobbyist, Unix-like OS built from scratch. It is still in \n production, and has limited features.\n" );
	terminal_writestring("Made By Ayman0x03 & aa2006 in behalf of The Dagger Project. \n");

}
void dsh(){
	char string[50];
	terminal_writestring("DaggerSH is still in development.\n");
}

void shutdown() {
	terminal_clearscreen();
	terminal_writestring("It is now safe to shutdown your machine");
	__asm__ __volatile__("outw %1, %0" : : "dN" ((uint16_t)0xD004), "a" ((uint16_t)0x2000));
}

int get_command() {
	int cmd = 1;
	char string[50];
	getline(string, 50);
	if(strcmp(string,"help\x0D") == 1){
		cmd = 1;
	} else if(strcmp(string,"shutdown\x0D") == 1) {
		cmd = 2;
	} else if(strcmp(string,"echo\x0D") == 1){
		cmd = 3;
	} else  if(strcmp(string,"clear\x0D") == 1) {
		cmd = 4;
	} else if(strcmp(string, "init\x0D") == 1) {
		cmd = 5;
	} else if(strcmp(string, "color\x0D") == 1) {
		cmd = 6;
	} else if(strcmp(string, "about\x0D") == 1) {
		cmd = 7;
	}  else if(strcmp(string, "dsh\x0D") == 1) {
		cmd = 8;
	}  else {
		cmd = 9;
	}

	memset(string,0,50);
	terminal_writestring("\n");
	return cmd;
}

void execute_command(int cmd){
  switch(cmd){
    case 1:
      help();
      break;
    case 2:
      shutdown();
      break;
    case 3:
      echo();
      break;
    case 4:
      terminal_clearscreen();
      break;
	case 5:
	  init();
	  break;
	case 6:
	  color();
	  break;
	case 7:
	 about();
	 break;
	case 8:
	 dsh();
	 break;
    default: 
      terminal_writestring("[!]dsh: Command not found\n");
  }
}