#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
void terminal_scroll(void);
void terminal_clear_line(size_t y);
void terminal_clearscreen(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
int strcmp(const char *str1, const char *str2);
bool isascii(int c);
char getchar();
void getline(char* string, int len);
void prompt();
void hello_user(char* user);
void help();
void echo();
void shutdown();
int get_command();
void execute_command(int cmd);
#endif
