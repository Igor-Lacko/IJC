//htab_free.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//uvolni hashovaciu tabulku 
#include "htab_private.h"

//destruktor tabulky
void htab_free(htab_t *t){
    htab_clear(t);
    free(t);
}