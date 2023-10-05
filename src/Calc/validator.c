#include "validator.h"
#include <string.h>
#include <stdio.h>

int check_push_num(char *display, char *button){
    int display_len = strlen(display);
    int result = 0;
    if(display_len > 255){
        result = 4;
    }else if(button[0] == '0'){
        if(display_len == 0 || (display_len == 1 && display[display_len - 1] == '0')){
            result = 1;
        }else if(display[display_len - 1] == '0'){
            if(display_len >= 2 && !strchr("1234567890.", display[display_len - 2])){
                result = 3;
            }else{
                result = 2;
            }
        }else if(!strchr("x)nf", display[display_len - 1])){
            result = 2;
        }else{
            result = 3;
        }
    }else if(display_len == 0 || (display_len == 1 && display[display_len - 1] == '0')){
        result = 1;
    }else if(button[0] == 'x'){
        if(!strchr("1234567890.)nf", display[display_len - 1])){
            result = 2;
        }else{
            result = 3;
        }
    }else if(!strchr("x)nf", display[display_len - 1])){
        result = 2;
    }else{
        result = 3;
    }

    return result;
}


int check_push_point(char *display){
    int result = 3, len = strlen(display);
    if(len > 255){
        result = 4;
    }else if(len > 0 && strchr("1234567890", display[len - 1])){
        int pos = len - 1;
        while(pos >= 0 && strchr("1234567890", display[pos])){
            pos--;
        }
        if(pos >= 0 && display[pos] == '.'){
            result = 3;
        }else{
            result = 2;
        }
    }else{
        result = 3;
    }

    return result;
}


int check_push_func(char *display){
    int len = strlen(display);
    int result = 0;
    if(len > 255){
        result = 4;
    }else if(len == 0 || (len == 1 && display[len - 1] == '0')){
        result = 1;
    }else if(strchr("+=*/d^(", display[len - 1])){
        result = 2;
    }else{
        result = 3;
    }

    return result;
}

int check_push_operation(char *display, char *button){
    int len = strlen(display);
    int result = 0;
    if(len > 255){
        result = 4;
    }else if(button[0] == '-' || button[0] == '+'){
        if(len == 0){
            result = 1;
        }else{
            result = 2;
        }
    }else if(len == 0){
        result = 3;
    }else if(strchr("0123456789)x", display[len - 1])){
        result = 2;
    }else{
        result = 3;
    }

    return result;
}

int check_push_delete(char *display){
    int result = 0;
    int len = strlen(display);
    if(len == 0){
        result = 0;
    }else if(strchr("1234567890.+-*/^)x", display[len - 1])){
        result = 1;
    }else if(display[len - 1] == 'd'){
        result = 3;
    }else if(display[len - 1] == '('){
        if(len == 1 || (len > 1 && strchr("*/(-+", display[len - 2]))){
            result = 1;
        }else if(display[len - 2] == 't'){
            result = 5;
        }else if(display[len - 3] == 'i'){
            if(len >= 5 && display[len - 5] == 'a'){
                result = 5;
            }else{
                result = 4;
            }
        }else if(display[len - 3] == 'a'){
            if(len >= 5 && display[len - 5] == 'a'){
                result = 5;
            }else{
                result = 4;
            }
        }else if(display[len - 3] == 'o'){
            if(len >= 5 && display[len - 5] == 'a'){
                result = 5;
            }else{
                result = 4;
            }
        }else{
            result = 3;
        }
    }

    return result;
}

int check_push_left_bracket(char *display){
    int len = strlen(display);
    int result = 0;
    if(len > 255){
        result = 4;
    }else if(len == 0 || (len == 1 && display[len - 1] == '0')){
        result = 1;
    }else if(strchr("1234567890.x)", display[len - 1])){
        result = 3;
    }else{
        result = 2;
    }
    return result;
}

int check_brackets(char *display){
    int lb = 0;
    for(int i = 0; i < (int)strlen(display); ++i){
        if(display[i] == '('){
            lb++;
        }else if(display[i] == ')'){
            lb--;
        }
    }
    return lb;
}

int check_push_right_bracket(char *display){
    int len = strlen(display);
    int result = 0;
    if(len > 255){
        result = 4;
    }else if(len == 0 || (len == 1 && display[len - 1] == '0')){
        result = 3;
    }else if(strchr("1234567890x)", display[len - 1]) && check_brackets(display) > 0){
        result = 2;
    }else{
        result = 3;
    }

    return result;
}

int check_correct(char *display){
    int len = strlen(display);
    int result = 0;
    if(len > 255){
        result = 4;
    }else if(len == 0){
        result = 3;
    }else if(check_brackets(display) == 0 && strchr("0123456789x)", display[len - 1])){
        result = 2;
    }else{
        result = 3;
    }

    return result;
}

int isX(char *display) {
  int result = 0;
  for (int i = 0; i < (int)strlen(display); ++i) {
    if (display[i] == 'x') {
      result = 1;
    }
  }
  return result;
}

int check_range(double xMin, double xMax, double yMin, double yMax) {
    int err = 0;
    if (xMin > 1000000 || xMin < -1000000) err += 1;
    if (xMax > 1000000 || xMax < -1000000) err += 1;
    if (yMin > 1000000 || yMin < -1000000) err += 1;
    if (yMax > 1000000 || yMax < -1000000) err += 1;
    return err;
  }
