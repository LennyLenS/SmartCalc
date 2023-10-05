#include <stdio.h>

#include "polish.h"

int main() {
  char *temp = calloc(sizeof(char), 255);
  int start = make_string_simple("3mod2", temp);
  Node *res = make_polish(temp, &start);
  printf("%d\n", start);
  // while(res){
  //     printf("%c %Lf\n", res->operation, res->num);
  //     res = res->next;
  // }
  printf("%Lf\n", calc_polish(res, &start));
  printf("%d", start);
}