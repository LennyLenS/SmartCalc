#include "polish.h"

Node *init_node() {
  Node *new_node = calloc(sizeof(Node), 1);
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->num = NAN;
  return new_node;
}

void destruct_from_last(Node *last) {
  Node *cur = last;
  while (cur) {
    Node *a = cur->prev;
    free(cur);
    cur = a;
  }
}

void destruct_from_first(Node *first) {
  Node *cur = first;
  while (cur) {
    Node *a = cur->next;
    free(cur);
    cur = a;
  }
}

void copy_value(Node *from, Node *to) {
  to->num = from->num;
  to->operation = from->operation;
  to->priority = from->priority;
  to->x = from->x;
}

Node *push(Node *last, Node *value) {
  Node *a = init_node();
  copy_value(value, a);
  if (last != NULL) {
    last->next = a;
    a->prev = last;
    a->next = NULL;
  }
  return a;
}

Node *pop(Node *last, Node *to) {
  if (to != NULL) {
    copy_value(last, to);
  }
  Node *a = last->prev;
  if (a) {
    a->next = NULL;
    free(last);
  }
  return a;
}

int is_number(char c) {
  int res = 0;
  if (strchr("0123456789", c)) {
    res = 1;
  }
  return res;
}

int is_operation(char c) {
  int res = 0;
  if (strchr("-+/*^", c)) {
    res = 1;
  }
  return res;
}

int get_priority(char c) {
  int res = 0;
  if (c == '+' || c == '-') {
    res = 1;
  } else if (c == '*' || c == '/' || c == 'm') {
    res = 2;
  } else if (strchr("cstlgqioa^~&", c)) {
    res = 3;
  } else if (c == ')' || c == '(') {
    res = 4;
  }
  return res;
}

int make_string_simple(char *str, char *temp) {
  int string_len = (int)strlen(str);
  int point_temp = 0;
  int res = 0;
  for (int i = 0; i < string_len; i++) {
    if (str[i] == 'c') {
      if (i + 2 < string_len && str[i + 1] == 'o' && str[i + 2] == 's') {
        temp[point_temp++] = 'c';
        i += 2;
      } else {
        res = 1;
      }
    } else if (str[i] == 's') {
      if (i + 2 < string_len && str[i + 1] == 'i' && str[i + 2] == 'n') {
        temp[point_temp++] = 's';
        i += 2;
      } else if (i + 3 < string_len && str[i + 1] == 'q' && str[i + 2] == 'r' &&
                 str[i + 3] == 't') {
        temp[point_temp++] = 'q';
        i += 3;
      } else {
        res = 1;
      }
    } else if (str[i] == 't') {
      if (i + 2 < string_len && str[i + 1] == 'a' && str[i + 2] == 'n') {
        temp[point_temp++] = 't';
        i += 2;
      } else {
        res = 1;
      }
    } else if (str[i] == 'l') {
      if (i + 1 < string_len && str[i + 1] == 'n') {
        temp[point_temp++] = 'l';
        i += 1;
      } else if (i + 2 < string_len && str[i + 1] == 'o' && str[i + 2] == 'g') {
        temp[point_temp++] = 'g';
        i += 2;
      } else {
        res = 1;
      }
    } else if (str[i] == 'a') {
      if (i + 3 < string_len && str[i + 1] == 's' && str[i + 2] == 'i' &&
          str[i + 3] == 'n') {
        temp[point_temp++] = 'i';
        i += 3;
      } else if (i + 3 < string_len && str[i + 1] == 'c' && str[i + 2] == 'o' &&
                 str[i + 3] == 's') {
        temp[point_temp++] = 'o';
        i += 3;
      } else if (i + 3 < string_len && str[i + 1] == 't' && str[i + 2] == 'a' &&
                 str[i + 3] == 'n') {
        temp[point_temp++] = 'a';
        i += 3;
      } else {
        res = 1;
      }
    } else if (str[i] == 'm') {
      if (i + 2 < string_len && str[i + 1] == 'o' && str[i + 2] == 'd') {
        temp[point_temp++] = 'm';
        i += 2;
      } else {
        res = 1;
      }
    } else if (strchr("0123456789x.+-*^/()", str[i])) {
      temp[point_temp++] = str[i];
    } else {
      res = 1;
    }
  }
  return res;
}

Node *make_polish(char *str, int *error) {
  Node *stack = NULL, *result = NULL;
  for (int i = 0; i < (int)strlen(str); ++i) {
    Node *new_node = init_node();
    if (strchr("+-", str[i]) && (i == 0 || strchr("(+-*/^", str[i - 1]))) {
      if (str[i] == '-') {
        new_node->operation = '~';
        new_node->priority = get_priority('~');
      } else {
        new_node->operation = '&';
        new_node->priority = get_priority('&');
      }
      stack = push(stack, new_node);
    } else if (is_number(str[i])) {
      int j = 0;
      char buff[255];
      while (i < (int)strlen(str) && strchr("0123456789.", str[i])) {
        buff[j++] = str[i++];
      }
      buff[j] = '\0';
      double a = atof(buff);
      new_node->num = a;
      result = push(result, new_node);
      i--;
    } else if (str[i] == '(') {
      new_node->operation = '(';
      new_node->priority = get_priority('(');
      stack = push(stack, new_node);
    } else if (str[i] != ')' && str[i] != 'x') {
      new_node->operation = str[i];
      new_node->priority = get_priority(str[i]);
      while (stack && new_node->priority < stack->priority &&
             stack->operation != '(') {
        result = push(result, stack);
        stack = pop(stack, NULL);
      }
      stack = push(stack, new_node);
    } else if (str[i] == 'x') {
      new_node->x = 'x';
      result = push(result, new_node);
    } else if (str[i] == ')') {
      while (stack && stack->operation != '(') {
        result = push(result, stack);
        stack = pop(stack, NULL);
      }
      if (!stack || stack->operation != '(') {
        *error = 1;
        break;
      }
      stack = pop(stack, NULL);
    }
  }
  while (stack) {
    result = push(result, stack);
    stack = pop(stack, NULL);
  }
  Node *first_res = result;
  while (first_res->prev != NULL) {
    first_res = first_res->prev;
  }
  return first_res;
}

double make_unary_operation(char operation, double num) {
  double res = num;
  if (operation == 'c') {
    res = cos(num);
  } else if (operation == 's') {
    res = sin(num);
  } else if (operation == 't') {
    res = tan(num);
  } else if (operation == 'l') {
    res = log(num);
  } else if (operation == 'g') {
    res = log10(num);
  } else if (operation == 'q') {
    res = sqrt(num);
  } else if (operation == 'i') {
    res = asin(num);
  } else if (operation == 'o') {
    res = acos(num);
  } else if (operation == 'a') {
    res = atan(num);
  } else if (operation == '~') {
    res = -num;
  }

  return res;
}

double make_bin_operation(char operation, double num1, double num2) {
  double res = 0;
  if (operation == '+') {
    res = num1 + num2;
  } else if (operation == '-') {
    res = num1 - num2;
  } else if (operation == '/') {
    res = num1 / num2;
  } else if (operation == '*') {
    res = num1 * num2;
  } else if (operation == 'm') {
    res = fmod(num1, num2);
  } else if (operation == '^') {
    res = pow(num1, num2);
  }

  return res;
}

double calc_polish(Node *first, int *error) {
  Node *stack = NULL;
  while (first) {
    if (first->operation) {
      if (strchr("cstlgqioa~&", first->operation)) {
        if (stack) {
          stack->num = make_unary_operation(first->operation, stack->num);
        } else {
          *error = 1;
          break;
        }
      } else if (strchr("+-/*^m", first->operation)) {
        if (stack && stack->prev) {
          stack->prev->num = make_bin_operation(first->operation,
                                                stack->prev->num, stack->num);
          stack = pop(stack, NULL);
        } else {
          *error = 1;
          break;
        }
      }
    } else {
      Node *new_node = init_node();
      new_node->num = first->num;
      stack = push(stack, new_node);
    }
    first = first->next;
  }
  if (!stack->prev) {
    *error = 1;
  }
  double result = stack->num;
  destruct_from_last(stack);
  return result;
}

double calc_polish_x(Node *first, double x, int *error) {
  Node *stack = NULL;
  while (first) {
    if (first->operation) {
      if (strchr("cstlgqioa~&", first->operation)) {
        if (stack) {
          stack->num = make_unary_operation(first->operation, stack->num);
        } else {
          *error = 1;
          break;
        }
      } else if (strchr("+-/*^m", first->operation)) {
        if (stack && stack->prev) {
          stack->prev->num = make_bin_operation(first->operation,
                                                stack->prev->num, stack->num);
          stack = pop(stack, NULL);
        } else {
          *error = 1;
          break;
        }
      }
    } else {
      Node *new_node = init_node();
      if (first->x) {
        new_node->num = x;
      } else {
        new_node->num = first->num;
      }
      stack = push(stack, new_node);
    }
    first = first->next;
  }
  if (!stack->prev) {
    *error = 1;
  }
  double result = stack->num;
  destruct_from_last(stack);
  return result;
}

int check_x(char *display) {
  int result = 0;
  for (int i = 0; i < (int)strlen(display); ++i) {
    if (display[i] == 'x') {
      result = 1;
    }
  }
  return result;
}

double get_answer(char *display, double x) {
  char *temp = calloc(sizeof(char), 255);
  int start = make_string_simple(display, temp);
  Node *res = make_polish(temp, &start);
  double result = 0;
  if (check_x(display)) {
    result = calc_polish_x(res, x, &start);
  } else {
    result = calc_polish(res, &start);
  }
  free(temp);
  destruct_from_first(res);
  return result;
}
