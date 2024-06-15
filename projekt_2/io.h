//io.h, IJC DU2, priklad b)
//Autor: Igor Lacko, FIT (xlackoi00)
//rozhranie modulu io.c s funkciou read_word
#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <ctype.h>

int read_word(char *s, int max, FILE *f);
extern int warning;
#endif
