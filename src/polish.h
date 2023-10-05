#ifndef POLISH_H
#define POLISH_H

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int priority;
  double num;
  char operation;
  char x;

  struct Node *next;
  struct Node *prev;

} Node;

Node *init_node();
void destruct_from_last(Node *last);
void destruct_from_first(Node *first);
void copy_value(Node *from, Node *to);
Node *push(Node *last, Node *value);
Node *pop(Node *last, Node *to);
int make_string_simple(char *str, char *temp);
Node *make_polish(char *str, int *error);
double calc_polish(Node *first, int *error);
double get_answer(char *display, double x);

#endif  // POLISH_H
