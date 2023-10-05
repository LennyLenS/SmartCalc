#ifndef VALIDATOR_H
#define VALIDATOR_H

int check_push_num(char *display, char *button);
int check_push_point(char *display);
int check_push_func(char *display);
int check_push_operation(char *display, char *button);
int check_push_delete(char *display);
int check_push_right_bracket(char *display);
int check_push_left_bracket(char *display);
int check_correct(char *display);
int isX(char *display);
int check_range(double xMin, double xMax, double yMin, double yMax);

#endif  // VALIDATOR_H
