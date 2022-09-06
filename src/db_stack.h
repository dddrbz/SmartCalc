#ifndef SRC_DB_STACK_H_
#define SRC_DB_STACK_H_

#include <stdlib.h>

typedef struct stack_db {
  double value;
  struct stack_db* previus;
} stack_db;

void add_value_to_stack_db(double value, stack_db** head);
char get_value_from_stack_db(stack_db** head);
void free_stack_db(stack_db** head);

#endif  // SRC_DB_STACK_H_
