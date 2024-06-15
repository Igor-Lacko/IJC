//error.c
//riesenie IJC DU 1, priklad b (vyuzite aj v priklade a)
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra 
//definicie chybovych funkcii error_exit a warning, vyuzitych vo vacsine suborov v DU 1
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void warning(const char *fmt,...){
    va_list args;
    va_start(args,fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt,...){
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}