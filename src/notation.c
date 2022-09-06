#include "notation.h"

int translate_notation(char* str, char* result) {
  int res;
  stack_ch* head = NULL;

  if ((res = check_string(str)) == TRUE) {
    for (int i = 0; str[i]; ++i) {
      if (is_digit(str[i]) || (str[i] == 'x')) {
        add_number(str, i, result);
      } else if ((str[i] == '(') || (is_function(&str[i]))) {
        add_func_to_stack(str, &i, &head);
      } else if (is_operator(str[i]) == TRUE) {
        while ((head != NULL) &&
               (get_priority(str[i]) <= get_priority(head->value))) {
          result[strlen(result)] = get_value_from_stack_ch(&head);
        }
        add_value_to_stack_ch(str[i], &head);
      } else if (str[i] == ')') {
        while (head->value != '(') {
          result[strlen(result)] = get_value_from_stack_ch(&head);
        }
        get_value_from_stack_ch(&head);
        while ((head != NULL) && (!is_operator(head->value)) &&
               (head->value != '(')) {
          result[strlen(result)] = get_value_from_stack_ch(&head);
        }
      }
    }
    while (head != NULL) {
      result[strlen(result)] = get_value_from_stack_ch(&head);
    }
  }
  return res;
}

void add_number(char* str, int i, char* result) {
  result[strlen(result)] = str[i];
  if (!is_digit(str[i + 1])) {
    result[strlen(result)] = '|';
  }
}

void add_func_to_stack(char* str, int* i, stack_ch** head) {
  int k = 0, bracket = 0;

  while (str[*i + k] != '(') ++k;
  bracket = k;
  --k;
  while (k >= 0) {
    add_value_to_stack_ch(str[*i + k], head);
    --k;
  }
  *i += bracket;
  add_value_to_stack_ch(str[*i], head);
}

int get_priority(char value) {
  int priority = 0;

  switch (value) {
    case '(':
      priority = 0;
      break;
    case '+':
      priority = 1;
      break;
    case '-':
      priority = 1;
      break;
    case '*':
      priority = 2;
      break;
    case '/':
      priority = 2;
      break;
    case '%':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case '~':
      priority = 4;
      break;
  }
  return priority;
}
