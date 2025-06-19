#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Utility function declarations
void clear_input_buffer();
void remove_newline(char* str);
void get_current_date(char* date_str);
char* get_current_timestamp();
void initialize_system();
int create_directory(const char* path);
void display_loading_animation();
void print_header(const char* title);
void print_separator();

#endif