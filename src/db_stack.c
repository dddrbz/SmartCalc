#include "db_stack.h"

void add_value_to_stack_db(double value, stack_db** head) {
  stack_db* stack = (stack_db*)calloc(1, sizeof(stack_db));

  stack->value = value;
  stack->previus = (*head);
  (*head) = stack;
}

char get_value_from_stack_db(stack_db** head) {
  char value = 0;

  if ((*head) != NULL) {
    stack_db* tmp = (*head);
    value = (*head)->value;
    (*head) = (*head)->previus;
    free(tmp);
  }
  return value;
}

void free_stack_db(stack_db** head) {
  while ((*head) != NULL) {
    stack_db* tmp = (*head);
    (*head) = (*head)->previus;
    free(tmp);
  }
}
