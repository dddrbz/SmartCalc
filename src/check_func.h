#ifndef SRC_CHECK_FUNC_H_
#define SRC_CHECK_FUNC_H_

#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void format_some_operators(char* str);
int check_string(char* str);
int check_left_br(int i, char* str);
int check_right_br(int i, char* str);
int check_operator(int i, char* str);
int check_dot(int i, char* str);
int check_function(int* i, char* str);
int check_x(int i, char* str);
int check_digit(int* i, char* str);
int is_digit(char value);
int is_operator(char value);
int is_function(char* str);
void shift_line(int i, char* str);

#endif  // SRC_CHECK_FUNC_H_