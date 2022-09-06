#ifndef SRC_COUNT_H_
#define SRC_COUNT_H_

#include <math.h>

#include "db_stack.h"

#define TRUE 1
#define FALSE 0

void string_to_number(int* i, char* str, double* number);
int calculate_expression(char* str, double* result, double x);
void count_numbers(int* i, char* str, stack_db** head);
void count_function(char* str, stack_db** head);
int check_x_string(char* x);

#endif  // SRC_COUNT_H_
