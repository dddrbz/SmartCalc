#ifndef SRC_NOTATION_H_
#define SRC_NOTATION_H_

#include "ch_stack.h"
#include "check_func.h"

#define TRUE 1
#define FALSE 0

int translate_notation(char* str, char* result);
void add_number(char* str, int i, char* result);
void add_func_to_stack(char* str, int* i, stack_ch** head);
int get_priority(char value);
void shift_line(int i, char* str);

#endif  // SRC_NOTATION_H_
