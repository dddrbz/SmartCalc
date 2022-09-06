#include "count.h"

#include "check_func.h"

void string_to_number(int* i, char* str, double* number) {
  *number = atof(&str[*i]);
  while (is_digit(str[*i])) ++(*i);
}

int calculate_expression(char* str, double* result, double x) {
  int res = TRUE;

  if (str[0]) {
    double number;
    stack_db* stack_head = NULL;
    for (int i = 0; str[i]; ++i) {
      if (is_digit(str[i])) {
        if (str[i] == 'x') {
          number = x;
        } else {
          string_to_number(&i, str, &number);
        }
        add_value_to_stack_db(number, &stack_head);
      } else if (is_operator(str[i]) || is_function(&str[i])) {
        count_numbers(&i, str, &stack_head);
      }
    }
    if (stack_head != NULL) *result = stack_head->value;
    free_stack_db(&stack_head);
  }
  return res;
}

void count_numbers(int* i, char* str, stack_db** head) {
  if (str[*i] == '-') {
    (*head)->previus->value = (*head)->previus->value - (*head)->value;
  } else if (str[*i] == '+') {
    (*head)->previus->value = (*head)->previus->value + (*head)->value;
  } else if (str[*i] == '*') {
    (*head)->previus->value = (*head)->previus->value * (*head)->value;
  } else if (str[*i] == '/') {
    (*head)->previus->value = (*head)->previus->value / (*head)->value;
  } else if (str[*i] == '%') {
    (*head)->previus->value = fmod((*head)->previus->value, (*head)->value);
  } else if (str[*i] == '^') {
    (*head)->previus->value = pow((*head)->previus->value, (*head)->value);
  } else if (str[*i] == '~') {
    (*head)->value *= -1.0;
  } else if (is_function(&str[*i])) {
    count_function(&str[*i], head);
  }
  if ((str[*i] != '~') && (!is_function(&str[*i])))
    get_value_from_stack_db(head);
  if (is_function(&str[*i])) *i += 2;
}

void count_function(char* str, stack_db** head) {
  char array[9][10] = {"cos",  "sin",  "tan", "acos", "asin",
                       "atan", "sqrt", "ln",  "log"};

  if (str == strstr(str, array[0])) {
    (*head)->value = cos((*head)->value);
  } else if (str == strstr(str, array[1])) {
    (*head)->value = sin((*head)->value);
  } else if (str == strstr(str, array[2])) {
    (*head)->value = tan((*head)->value);
  } else if (str == strstr(str, array[3])) {
    (*head)->value = acos((*head)->value);
  } else if (str == strstr(str, array[4])) {
    (*head)->value = asin((*head)->value);
  } else if (str == strstr(str, array[5])) {
    (*head)->value = atan((*head)->value);
  } else if (str == strstr(str, array[6])) {
    (*head)->value = sqrt((*head)->value);
  } else if (str == strstr(str, array[7])) {
    (*head)->value = log((*head)->value);
  } else if (str == strstr(str, array[8])) {
    (*head)->value = log10((*head)->value);
  }
}

int check_x_string(char* x) {
  int flag = 0, res = TRUE;

  for (int i = 0; x[i]; ++i) {
    if (x[i] == '.') {
      if (flag || (i == 0)) res = FALSE;
      flag = 1;
    } else if (x[i] < '0' || x[i] > '9') {
      if (i == 0 && (x[i] == '+' || x[i] == '-')) {
        res = TRUE;
      } else {
        res = FALSE;
      }
    }
    if (res == FALSE) break;
  }
  return res;
}
