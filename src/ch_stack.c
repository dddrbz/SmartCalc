#include "ch_stack.h"

void add_value_to_stack_ch(char value, stack_ch** head) {
  stack_ch* stack = (stack_ch*)calloc(1, sizeof(stack_ch));

  stack->value = value;
  stack->previus = (*head);
  (*head) = stack;
}

char get_value_from_stack_ch(stack_ch** head) {
  char value = 0;

  if ((*head) != NULL) {
    stack_ch* tmp = (*head);
    value = (*head)->value;
    (*head) = (*head)->previus;
    free(tmp);
  }
  return value;
}

void free_stack_ch(stack_ch** head) {
  while ((*head) != NULL) {
    stack_ch* tmp = (*head);
    (*head) = (*head)->previus;
    free(tmp);
  }
}
