#ifndef SRC_CH_STACK_H_
#define SRC_CH_STACK_H_

#include <stdlib.h>

typedef struct stack_ch {
  char value;
  struct stack_ch* previus;
} stack_ch;

int translate_notation(char* str, char* result);
void add_value_to_stack_ch(char value, stack_ch** head);
char get_value_from_stack_ch(stack_ch** head);
void free_stack_ch(stack_ch** head);

#endif  // SRC_CH_STACK_H_
