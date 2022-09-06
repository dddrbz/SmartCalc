#include "check_func.h"

void format_some_operators(char* str) {
  for (int i = 0; str[i]; ++i) {
    while (str[i] == ' ') shift_line(i, str);
    while (str[i] == '+') {
      if ((i == 0) || (is_operator(str[i - 1]))) {
        shift_line(i, str);
      } else {
        ++i;
      }
    }
    while (str[i] == '-') {
      if ((i == 0) || (is_operator(str[i - 1])) || str[i - 1] == '(') {
        if ((i >= 1) && (str[i - 1] == '~')) {
          --i;
          shift_line(i, str);
          shift_line(i, str);
        } else {
          str[i] = '~';
        }
      } else {
        ++i;
      }
    }
    if (&str[i] == strstr(&str[i], "mod")) {
      shift_line(i, str);
      shift_line(i, str);
      str[i] = '%';
    }
  }
}

int check_string(char* str) {
  int check_br = 0, flag = 1;

  if (!str) {
    flag = 0;
  } else if (strlen(str) > 1) {
    format_some_operators(str);
    for (int i = 0; str[i]; ++i) {
      if (str[i] == '(') {
        ++check_br;
        flag = check_left_br(i, str);
      } else if ((check_br) && (str[i] == ')')) {
        --check_br;
        flag = check_right_br(i, str);
      } else if (str[i] == ')') {
        flag = 0;
      } else if (is_operator(str[i])) {
        flag = check_operator(i, str);
      } else if (is_function((&str[i]))) {
        flag = check_function(&i, str);
      } else if (str[i] == 'x') {
        flag = check_x(i, str);
      } else if (is_digit(str[i])) {
        flag = check_digit(&i, str);
      } else {
        flag = 0;
      }
      if (!flag) break;
    }
    if (check_br != 0) flag = 0;
  } else if (!is_digit(str[0])) {
    flag = 0;
  }
  return (flag) ? TRUE : FALSE;
}

int check_left_br(int i, char* str) {
  int res = TRUE;

  if (is_operator(str[i + 1]) && (str[i + 1] != '~') && (str[i + 1] != '(')) {
    res = FALSE;
  } else if ((i >= 1) && (is_digit(str[i - 1]))) {
    res = FALSE;
  }
  return res;
}

int check_right_br(int i, char* str) {
  int res = TRUE;

  if ((!is_digit(str[i - 1]) && (str[i - 1] != ')'))) {
    res = FALSE;
  } else if ((!is_operator(str[i + 1]) && (str[i + 1] != '\0'))) {
    if (str[i + 1] != ')') res = FALSE;
  }
  return res;
}

int check_operator(int i, char* str) {
  int res = TRUE;

  if (str[i] == '~') {
    if (i >= 1) {
      if ((!is_operator(str[i - 1])) && (str[i - 1] != '(')) {
        res = FALSE;
      } else if ((!is_digit(str[i + 1])) && (str[i + 1] != '(')) {
        if (str[i + 1] != '~' && !is_function(&str[i + 1])) res = FALSE;
      }
    }
  } else {
    if (i < 1) {
      res = FALSE;
    } else {
      if ((!is_digit(str[i - 1])) && (str[i - 1] != ')')) {
        res = FALSE;
      } else if ((!is_digit(str[i + 1])) && (str[i + 1] != '(')) {
        if (str[i + 1] != '~' && !is_function(&str[i + 1])) res = FALSE;
      }
    }
  }
  return res;
}

int check_function(int* i, char* str) {
  char array[9][5] = {"cos",  "sin",  "tan", "acos", "asin",
                      "atan", "sqrt", "ln",  "log"};

  *i += strlen(array[is_function(&str[*i]) - 1]) - 1;
  return (str[*i] != '(') ? TRUE : FALSE;
}

int check_x(int i, char* str) {
  int res = FALSE;

  if ((i == 0) || is_operator(str[i - 1]) || (str[i - 1] == '(')) {
    if (is_operator(str[i + 1]) || (str[i + 1] == ')') ||
        (str[i + 1] == '\0')) {
      res = TRUE;
    }
  }
  return res;
}

int check_digit(int* i, char* str) {
  int res = TRUE;
  int dot_flag = TRUE;

  if (is_digit(str[*i])) {
    if ((*i == 0) || (is_operator(str[*i - 1])) || (str[*i - 1] == '(')) {
      while (is_digit(str[*i]) && str[*i] != 'x') {
        if (str[*i] == '.') {
          if (dot_flag == TRUE) {
            dot_flag = FALSE;
          } else {
            res = FALSE;
          }
        }
        if (res == FALSE) break;
        ++(*i);
      }
      if ((!is_operator(str[*i])) && (str[*i] != ')') && (str[*i] != '\0')) {
        res = FALSE;
      }
      --(*i);
    } else {
      res = FALSE;
    }
  } else {
    res = FALSE;
  }
  return res;
}

int is_digit(char value) {
  int res = FALSE;

  if ((value >= '0') && (value <= '9')) {
    res = TRUE;
  } else if (value == 'x' || value == '.') {
    res = TRUE;
  }
  return res;
}

int is_operator(char value) {
  char operators[] = "+-*/%^~";

  return (strchr(operators, value) != NULL) ? TRUE : FALSE;
}

int is_function(char* str) {
  char array[9][5] = {"cos",  "sin",  "tan", "acos", "asin",
                      "atan", "sqrt", "ln",  "log"};
  int res = 0;

  for (int i = 0; i < 9; ++i) {
    if (str == strstr(str, array[i])) {
      res = i + 1;
      break;
    }
  }
  return res;
}

void shift_line(int i, char* str) {
  int length = strlen(str);

  while (i < length) {
    str[i] = str[i + 1];
    ++i;
  }
}